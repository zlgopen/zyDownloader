import {MainModel} from "../models/main-model";
import {ICommand, InteractionRequest, ChoiceInfo} from "qtk";

export class CommandChooseFile implements ICommand {
	protected _model : MainModel;

	constructor(model:MainModel) {
		this._model = model;
	}

	public canExecute() : boolean {
		return true;
	}

	public execute(args:any) : boolean {
		var model:MainModel = this._model;
		var input:any = document.createElement("input");

		input.type = "file";
		input.multiple = false;
		input.onchange = function(e) {
			if(input.files && this.files.length) {
				var file = input.files[0];
				console.dir(file);
				model.fileName = file.path;
			}
		}

		input.click();

		return true;
	}

	public static create(model:MainModel) : ICommand {
		return new CommandChooseFile(model);
	}
}

