import {KeyEvent, Events, ViewModel, DelegateCommand} from "qtk";
import {DelegateValueConverter, DelegateFilter, DelegateComparator, ValidationResult} from "qtk";

import {MainModel} from "../models/main-model";
import {CommandChooseFile} from "./command-choose-file";
import {CommandShowSettings} from "./command-show-settings";
import {CommandStartDownload} from "./command-start-download";

export class MainViewModel extends ViewModel {
	public get model() : MainModel {
		return this.data;
	}

	constructor(data:any) {
		super(data);

		this.registerCommand("showSettings", CommandShowSettings.create(this.model));
		this.registerCommand("chooseFile", CommandChooseFile.create(this.model));
		this.registerCommand("startDownload", CommandStartDownload.create(this.model));
	}

	public static create(data:any): MainViewModel {
		return new MainViewModel(data);
	}
}
