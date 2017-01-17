import {Application}    from "qtk";
import {initLocales}    from "./locales"
import {MainModel}      from "./models/main-model";
import {MainWindow}     from "./views/main-window"
import {MainViewModel}  from "./view-models/main-view-model";

var themeDataURL    = "assets/theme/default/theme.js";
var appThemeDataURL = "assets/theme/default/theme.js";

export class App extends Application {
	public onReady() {
		initLocales();
		var viewModel  = MainViewModel.create(MainModel.create());
		var mainWindow = MainWindow.create({app:this, viewModel:viewModel}).maximize();
	}
	
	public static run() : App {
		var app = new App("Downloader");
		var assetsURLs = [themeDataURL, appThemeDataURL];

		app.preload(assetsURLs, function() {
			app.init({sysThemeDataURL:themeDataURL, appThemeDataURL:appThemeDataURL});
			app.run();
		});

		return app;
	}
};
