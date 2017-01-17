
#include "transferer_factory.h"

#define MAX_CREATORS 10

typedef struct _transferer_factory_t {
	const transferer_desc_t* creators[MAX_CREATORS];
}transferer_factory_t;

static transferer_factory_t s_factory;

bool_t transferer_factory_register(const transferer_desc_t* transferer_desc) {
	return_value_if_fail(transferer_desc != NULL, FALSE);
	for(size_t i = 0; i < MAX_CREATORS; i++) {
		if(!s_factory.creators[i]) {
			s_factory.creators[i] = transferer_desc;

			return TRUE;
		}
	}
	
	return FALSE;
}

bool_t transferer_factory_unregister(const transferer_desc_t* transferer_desc) {
	return_value_if_fail(transferer_desc != NULL, FALSE);
	for(size_t i = 0; i < MAX_CREATORS; i++) {
		if(transferer_desc == s_factory.creators[i]) {
			s_factory.creators[i] = NULL;

			return TRUE;
		}
	}
	
	return FALSE;

}

transferer_t* transferer_factory_create(const char* url) {
	return_value_if_fail(url != NULL, FALSE);
	for(size_t i = 0; i < MAX_CREATORS; i++) {
		const transferer_desc_t* iter = s_factory.creators[i];
		if(iter) {
			transferer_t* transferer = iter->create(url);
			if(transferer) {
				return transferer;
			}
		}else{
			break;
		}
	}
	
	return NULL;
}

bool_t transferer_factory_foreach(visit_func_t visit, void* ctx) {
	return_value_if_fail(visit != NULL, FALSE);
	for(size_t i = 0; i < MAX_CREATORS; i++) {
		const transferer_desc_t* iter = s_factory.creators[i];
		if(iter) {
			if(visit(ctx, iter)) {
				return TRUE;
			}
		}else{
			break;
		}
	}

	return FALSE;
}
