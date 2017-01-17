import {Image, ListItem, ListLayouterParam, TitleComboBox} from "qtk"
import {WindowNormal, ImageDrawType, SimpleLayouter, SimpleLayouterParam} from "qtk"
import {IViewModel, ViewModel, ListView, Edit, Group, RadioButton, Button, Rect, Label} from "qtk";

export class MainWindow extends WindowNormal {
	protected viewModel : IViewModel;

	protected onInit() {
		super.onInit();

		this.childrenLayouter = SimpleLayouter.create();
	
		var listView = ListView.create({dragToScroll:false, slideToScroll:false, itemH:60});
		listView.layoutParam = this.createChildLayoutParam({x:"center", y:"middle", w:"360px", h:"280px"});
		this.addChild(listView);

		var logo = Image.create({value:"assets/icons/@density/logo.png"});
		logo.drawType = ImageDrawType.ICON;
		logo.layoutParam = this.createChildLayoutParam({x:"0", y:"0", w:"240px", h:"80"});
		this.addChild(logo);

		function addItem(titleValue, bindingRule, h?:number) {
			var item = ListItem.create({styleType:"widget.tansparent"});
			if(h) {
				item.layoutParam = ListLayouterParam.create({h:h});
			}
			listView.addChild(item, true);
			item.childrenLayouter = SimpleLayouter.create();
			item.addChild(titleValue);
			if(titleValue.valueWidget) {
				titleValue.valueWidget.dataBindingRule = bindingRule;
			}else{
				titleValue.dataBindingRule = bindingRule;
			}
			return titleValue;
		}
		
		addItem(TitleComboBox.create({title:"Download Type", titleW:"100",valueW:"60%", 
				layoutParam : SimpleLayouterParam.create({h:"40"})}), 
				{value: {path:"downloadType"},options: {path:"downloadTypes"}});

		addItem(Button.create({text:"Change Settings",layoutParam : SimpleLayouterParam.create({h:"80%"})}), 
				{"click" : {command:"showSettings"}});
		
		addItem(Button.create({text:"Choose File", layoutParam : SimpleLayouterParam.create({h:"80%"})}), 
				{"click" : {command:"chooseFile"}});
		
		addItem(Button.create({text:"Start Download", layoutParam : SimpleLayouterParam.create({h:"80%"})}), 
				{"click" : {command:"startDownload"}});

		this.bindData(this.viewModel);
	}

	public static create(options:any) : MainWindow {
		var win = new MainWindow();
		win.reset("main-window", options);
		win.open();

		return win;
	}
}


