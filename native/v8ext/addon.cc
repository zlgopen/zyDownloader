#include <nan.h>
#include "types_def.h"
#include "transferer_tcp.h"
#include "transferer_serial.h"
#include "transferer_factory.h"
#include "transferer_tftp_server.h"

#include <stdio.h>

using v8::Handle;
using v8::Object;
using Nan::New;
using Nan::Set;
using Nan::GetFunction;

using v8::Local;
using v8::Number;
using v8::Value;
using v8::String;
using v8::Function;
using v8::FunctionTemplate;
using Nan::AsyncQueueWorker;
using Nan::AsyncWorker;
using Nan::Callback;
using Nan::HandleScope;
using Nan::New;
using Nan::Null;

class TransferWorker : public AsyncWorker {
public:
	TransferWorker(Callback *callback, const char* url)
	: AsyncWorker(callback), mURL(std::string(url)){
		mMsg = "";
	}
	~TransferWorker() {}

	void Execute () {
		const char* url = mURL.c_str();

		transferer_t* transferer = transferer_factory_create(url);
		if(transferer) {
			TransferWorker::transferer = transferer;
			const char* msg = NULL;
			if(transferer_start(transferer, &msg)){
				mResult = "success";
			}else{
				mResult = "failed";
				mMsg = msg;
			}
			transferer_destroy(transferer);
			TransferWorker::transferer = NULL;
		}else{
			mResult = "failed";
			printf("create transferer failed.");
		}
	}

	void HandleOKCallback () {
		HandleScope scope;
		const char* msg = mResult.c_str();
		const char* log = mMsg.c_str();

		Local<Value> argv[] = {
			New<v8::String>(msg).ToLocalChecked(),
			New<v8::String>(log).ToLocalChecked()
		};

		callback->Call(2, argv);
	}
 public:
 	static transferer_t* transferer;
 private:
	std::string mURL;
	std::string mMsg;
	std::string mResult;
};

transferer_t* TransferWorker::transferer = NULL;

static bool_t visit_transferers(void* ctx, transferer_desc_t* desc) {
	HandleScope scope;
	Callback* callback = (Callback*)ctx;
	Local<Value> argv[] = {
		New<v8::String>(desc->name).ToLocalChecked(),
		New<v8::String>(desc->get_props_desc()).ToLocalChecked()
	};

	callback->Call(2, argv);
	
	return FALSE;
}

NAN_METHOD(foreachTransfer) {
	Callback *callback = new Callback(info[0].As<Function>());

	transferer_factory_foreach((visit_func_t)visit_transferers, callback);
}

NAN_METHOD(startTransfer) {
	v8::String::Utf8Value url(info[0]);
	Callback *callback = new Callback(info[1].As<Function>());
	fflush(stdout);

	AsyncQueueWorker(new TransferWorker(callback, *url));
}

NAN_METHOD(getProgress) {
	double ret = 0;
	if(TransferWorker::transferer) {
		double sent_size = (double)transferer_get_sent_size(TransferWorker::transferer);
		double total_size = (double)transferer_get_total_size(TransferWorker::transferer);
		ret = total_size > 0 ? sent_size/total_size : 0;
		printf("progress=%lf %lf/%lf\n", ret, sent_size, total_size);
	}
	fflush(stdout);
	info.GetReturnValue().Set(ret);
}

/////////////////////////////////////////////////////////////////

static void registerTransfers() {
//	transferer_tcp_register_creator_desc();
	transferer_serial_register_creator_desc();
	transferer_tftp_server_register_creator_desc();

	return;
}

NAN_MODULE_INIT(InitAll) {
	freopen("stdout.txt", "w+", stdout);
	freopen("stderr.txt", "w+", stderr);
	printf("build date: %s %s\n", __DATE__, __TIME__);
	fflush(stdout);

	registerTransfers();
	
	Set(target, New<String>("foreachTransfer").ToLocalChecked(),
		GetFunction(New<FunctionTemplate>(foreachTransfer)).ToLocalChecked());
	
	Set(target, New<String>("startTransfer").ToLocalChecked(),
		GetFunction(New<FunctionTemplate>(startTransfer)).ToLocalChecked());

	Set(target, New<String>("getProgress").ToLocalChecked(),
		GetFunction(New<FunctionTemplate>(getProgress)).ToLocalChecked());
}

NODE_MODULE(downloader, InitAll)

