declare var downloader:any;

export class MainModel {
	public fileName       : string;
	public settingsValues : any;
	public downloadType   : string;
	public downloadTypes  : Array<any>;

	public constructor() {
		this.downloadTypes = [];
		this.downloadType = null;
		this.settingsValues = {};

		downloader.foreachTransfer((name, desc) => {
			this.downloadTypes.push({text:name});
			if(!this.downloadType) {
				this.downloadType = name;
			}
		});

		this.load();
	}

	public get settingsDesc() : any {
		var strDesc = null;	
		downloader.foreachTransfer((name, desc) => {
			if(name == this.downloadType) {
				strDesc = desc;	
			}
		});
		console.log(strDesc);
		return JSON.parse(strDesc);
	}

	public save() {
		var str = JSON.stringify(this.settingsValues);
		localStorage.setItem("settingsValues", str);
		localStorage.setItem("downloadType", this.downloadType);
	}
	
	public load() {
		var downloadType = localStorage.getItem("downloadType");
		if(downloadType) {
			this.downloadType = downloadType;
		}

		var settingsValues = localStorage.getItem("settingsValues");
		if(settingsValues) {
			try {
				this.settingsValues = JSON.parse(settingsValues);
			}catch(e) {
				localStorage.removeItem("settingsValues");
			}
		}
	}

	public get settingsValue() : any {
		var settingsDesc = this.settingsDesc;
		var data = this.settingsValues[this.downloadType] || {};

		settingsDesc.map(iter => {
			var path = iter.path;

			if(data[path] === undefined || iter.type.indexOf("readonly") >= 0) {
				if(iter.defValue !== undefined) {
					data[path] = iter.defValue;
				}else{
					data[path] = "";
				}
			}
		});

		return data;
	}
	
	public set settingsValue(value:any) {
		this.settingsValues[this.downloadType] = value;
		
		this.save();
	}

	public getProgress() {
		return downloader.getProgress();
	}

	public genURL() : string {
		var settingsValue = this.settingsValue;
		var url = this.downloadType + "://localhost/" + this.fileName + "?";
		for(var key in settingsValue) {
			var value = settingsValue[key];
			url += key + "=" + value + "&";
		}

		return url;
	}

	public startTransfer(callback:Function) {
		var url = this.genURL();
		if(url) {
			downloader.startTransfer(url, callback);
		}
	}

	public static create() : MainModel {
		return new MainModel();
	}
}

