import {MainModel} from "../models/main-model";
import {StringTable, ProgressInfo, ICommand, InteractionRequest, ChoiceInfo} from "qtk";

export class CommandStartDownload implements ICommand {
	protected _model : MainModel;

	constructor(model:MainModel) {
		this._model = model;
	}

	public canExecute() : boolean {
		var model:MainModel = this._model;
		return (!!model.downloadType) && (!!model.fileName);
	}

	public execute(args:any) : boolean {
		var model:MainModel = this._model;
	
		function download(updateProgressBar) {
			var done = false;
			model.startTransfer(function(msg, log) {
				done = true;
				updateProgressBar(1);
				console.log(msg);
				console.log(log);
				if(msg === "failed") {
					alert(StringTable.tr("Download Failed: ") + StringTable.tr(log));
					updateProgressBar(0);
				}
			});

			function updateProgress() {
				if(!done) {
					var progress = model.getProgress();
					if(progress >= 1) {
						progress = 0.99;
					}
					updateProgressBar(progress);
					console.log("progress=" + progress);
					setTimeout(updateProgress, 200);
				}
			}

			updateProgress();
		}
		
		var info = ProgressInfo.create("Downloading...", download, 360);
        InteractionRequest.progress(info, function(ret) {
        	console.dir(ret);
        });

		return true;
	}

	public static create(model:MainModel) : ICommand {
		return new CommandStartDownload(model);
	}
}

