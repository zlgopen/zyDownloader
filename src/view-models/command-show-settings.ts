import {MainModel} from "../models/main-model";
import {PagePropsDesc, PropsInfo, ICommand, InteractionRequest} from "qtk";

export class CommandShowSettings implements ICommand {
	protected _model : MainModel;

	constructor(model:MainModel) {
		this._model = model;
	}

	public canExecute() : boolean {
		return !!(this._model.downloadType);
	}

	public execute(args:any) : boolean {
		var model:MainModel = this._model;

		var data = model.settingsValue;
		var propsDesc = PagePropsDesc.create("Settings("+model.downloadType+")" , model.settingsDesc);
		InteractionRequest.props(PropsInfo.create(propsDesc, data, true, 360), function(ret) {
			model.settingsValue = ret.data;
            console.dir(ret);
        });

		return true;
	}

	public static create(model:MainModel) : ICommand {
		return new CommandShowSettings(model);
	}
};
