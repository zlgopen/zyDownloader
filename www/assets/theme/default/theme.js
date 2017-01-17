window.sysThemeJson = {
	"widget" : {
		"common" : {
			"lineWidth" : 1,
			"fontSize" : 14,
			"textColor" : "black",
			"backGroundColor" : "#FFFFFF"
		},
		"normal" : {},
		"active" : {},
		"over" : {},
		"selected" : {},
		"disable" : {
			"textColor" : "gray"
		}
	},
	"title.line": {
		"extends": "widget",
		"common" : {
			"lineWidth" : 1,
			"lineColor" : "gray"
		}
	},
	"chart-view": {
		"extends": "widget"
	},
	"label": {
		"extends": "widget",
		"common" : {
			"backGroundColor" : null,
			"textAlign" : "left"
		}
	},
	"label.small": {
		"extends": "widget",
		"common" : {
			"fontSize" : 10,
			"backGroundColor" : null,
			"textAlign" : "left"
		}
	},
	"link": {
		"extends": "widget",
		"common" : {
			"textAlign" : "left"
		},
		"over" : {
			"fontItalic" : true
		}
	},
	"label.center": {
		"extends": "widget",
		"common" : {
			"backGroundColor" : null,
			"textAlign" : "center",
			"textBaseline" : "middle"
		}
	},
	"edit": {
		"extends": "widget",
		"common" : {
			"textAlign" : "left",
			"lineColor" : "#cccccc",
			"roundRadius" : 5
		},
		"over" : {
			"lineColor" : "#AAAAAA"
		},
		"active" : {
			"lineColor" : "#AAAAAA"
		}
	},
	"edit.sl": {
		"extends": "edit"
	},
	"edit.ml": {
		"extends": "edit",
		"common" : {
			"textAlign" : "left",
			"textBaseline" : "top",
			"roundRadius" : 5
		}
	},
	"edit.sl.tips": {
		"extends": "edit",
		"common" : {
			"textBaseline" : "middle",
			"textColor" : "#CCCCCC"
		}
	},
	"edit.ml.tips": {
		"extends": "edit",
		"common" : {
			"textBaseline" : "top",
			"textColor" : "#CCCCCC"
		}
	},
	"edit.invalid.tips": {
		"extends": "edit",
		"common" : {
			"textAlign":"center",
			"lineColor":"#606060",
			"textBaseline" : "middle",
			"backGroundColor":"#FEEFAB",
			"textColor" : "Red"
		}
	},
	"button": {
		"extends": "widget",
		"common" : {
			"roundRadius" : 5
		},
		"normal" : {
			"lineColor" : "#A8A8A8",
			"backGroundColor" : ["#F6F6F6","#EEEEEE","#E9E9E9", "#E3E3E3", "#E1E1E1"]
		},
		"over" : {
			"lineColor" : "#A8A8A8",
			"backGroundColor" : ["#F4F4F4","#F0F0F0","#EDEDED", "#E7E7E7", "#E4E4E4"]
		},
		"disable" : {
			"lineColor" : "#D7D7D7",
			"textColor" : "#B1B1B1",
			"backGroundColor" : "#F6F6F6"
		},
		"active" : {
			"lineColor" : "#4D90FC",
			"backGroundColor" : ["#E8E8E8","#E7E7E7","#E4E4E4", "#E0E0E0", "#D8D8D8"]
		}
	},
	"button.ok": {
		"extends": "widget",
		"common" : {
			"roundRadius" : 5
		},
		"normal" : {
			"lineColor" : "#9BC4ED",
			"backGroundColor" : ["#6EB4F7","#53A5F8","#409bF9", "#268BFA", "#1A82FB"]
		},
		"over" : {
			"lineColor" : "#2C82FB",
			"backGroundColor" : ["#6EB4F7","#53A5F8","#409bF9", "#268BFA", "#1A82FB"]
		},
		"disable" : {
			"lineColor" : "#D7D7D7",
			"textColor" : "#B1B1B1",
			"backGroundColor" : "#F6F6F6"
		},
		"active" : {
			"lineColor" : "#2C82FB",
			"backGroundColor" : ["#509AFB","#3F8EF4","#2B7EEC", "#2074E7", "#1469E1"]
		}
	},
	"button.cancel": {
		"extends": "widget",
		"common" : {
			"roundRadius" : 5
		},
		"normal" : {
			"lineColor" : "#D6D6D6",
			"backGroundColor" : "#FFFFFF"
		},
		"over" : {
			"lineColor" : "#2C82FB",
			"backGroundColor" : "#FFFFFF"
		},
		"disable" : {
			"lineColor" : "#D7D7D7",
			"textColor" : "#B1B1B1",
			"backGroundColor" : "#F6F6F6"
		},
		"active" : {
			"lineColor" : "#2C82FB",
			"backGroundColor" : ["#509AFB","#3F8EF4","#2B7EEC", "#2074E7", "#1469E1"]
		}
	},
	"button-blue": {
		"extends": "widget",
		"common" : {
			"roundRadius" : 5
		},
		"normal" : {
			"backGroundColor" : "blue"
		},
		"over" : {
			"backGroundColor" : "green"
		},
		"active" : {
			"backGroundColor" : "red"
		}
	},
	"dialog": {
		"extends": "widget",
		"common" : {
			"backGroundColor" : "#606060"
		}
	},
	"progress-bar": {
		"extends": "widget",
		"common" : {
			"roundRadius" : 5,
			"backGroundColor" : "#606060",
			"foreGroundColor" : "#d0d0d0"
		}
	},
	"slider": {
		"extends": "progress-bar"
	},
	"slider-dragger": {
		"extends": "widget",
		"common" : {
			"roundRadius" : 50,
			"backGroundColor" : "green"
		}
	},
	"scroll-view": {
		"extends": "widget",
		"common" : {
			"lineColor" : "#EEEEEE"
		}
	},
	"grid-view": {
		"extends": "scroll-view"
	},
	"list-view": {
		"extends": "scroll-view"
	},
	"tree-view": {
		"extends": "scroll-view"
	},
	"tree-item": {
		"extends": "widget",
		"common" : {
			"textAlign":"left"
		},
		"normal" : {
			"backGroundColor" : "#FEFEFE"
		},
		"over" : {
			"backGroundColor" : "#EEEEEE"
		},
		"selected" : {
			"backGroundColor" : "#CCCCCC"
		},
		"active" : {
			"backGroundColor" : "#DDDDDD"
		}
	},
	"tree-item.expanded": {
		"extends": "tree-item",
		"common" : {
			"foreGroundImage":"images/@density/expand.png"
		}
	},
	"tree-item.collapsed": {
		"extends": "tree-item",
		"common" : {
			"foreGroundImage":"images/@density/collapse.png"
		}
	},
	"tree-item.leaf": {
		"extends": "tree-item",
		"common" : {
			"foreGroundImage":"images/@density/leaf.png"
		}
	},
	"radio-button": {
		"extends": "widget",
		"common" : {
			"textAlign":"right"
		}
	},
	"radio-button.checked": {
		"extends": "radio-button",
		"common" : {
			"foreGroundImage":"images/@density/radio-button-checked.png"
		}
	},
	"radio-button.unchecked": {
		"extends": "radio-button",
		"common" : {
			"foreGroundImage":"images/@density/radio-button-unchecked.png"
		}
	},
	"check-button": {
		"extends": "widget",
		"common" : {
			"textAlign":"right"
		}
	},
	"check-button.checked": {
		"extends": "check-button",
		"common" : {
			"foreGroundImage":"images/@density/check-button-checked.png"
		}
	},
	"check-button.unchecked": {
		"extends": "check-button",
		"common" : {
			"foreGroundImage":"images/@density/check-button-unchecked.png"
		}
	},
	"list-item": {
		"extends": "widget",
		"common" : {
			"lineColor" : "#DDDDDD",
			"textAlign":"center"
		},
		"normal" : {
			"backGroundColor" : "#FFFFFF"
		},
		"over" : {
			"backGroundColor" : "#EEEEEE"
		},
		"active" : {
			"backGroundColor" : "#DDDDDD"
		}
	},
	"list-item.odd": {
		"extends": "list-item",
		"normal" : {
			"backGroundColor" : "#F0F0F0"
		},
		"over" : {
			"backGroundColor" : "#DDDDDD"
		},
		"active" : {
			"backGroundColor" : "#CCCCCC"
		}
	},
	"list-item.even": {
		"extends": "list-item",
		"normal" : {
			"backGroundColor" : "#FFFFFF"
		},
		"over" : {
			"backGroundColor" : "#DDDDDD"
		},
		"active" : {
			"backGroundColor" : "#CCCCCC"
		}
	},
	"combo-box": {
		"extends": "button",
		"common" : {
			"foreGroundImage" : "images/@density/combo-box.png"
		}
	},
	"combo-box.button": {
		"extends": "button",
		"common" : {
			"foreGroundImage" : "images/@density/combo-box.png"
		}
	},
	"combo-box-item": {
		"extends": "list-item",
		"common" : {
			"textAlign" : "left"
		}
	},
	"combo-box-item.current": {
		"extends": "combo-box-item",
		"common" : {
			"foreGroundImage" : "images/@density/combo-box-item-current.png"
		}
	},
	"combo-box-popup": {
		"extends": "widget",
		"common" : {
			"lineWidth":2,
			"lineColor":"#AAAAAA",
			"backGroundColor" : "#F8F8F8"
		}
	},
	"table-header-item": {
		"extends": "widget",
		"common" : {
			"roundRadius" : 0
		},
		"normal" : {
			"lineColor" : "#A8A8A8",
			"backGroundColor" : ["#F6F6F6","#EEEEEE","#E9E9E9", "#E3E3E3", "#E1E1E1"]
		},
		"over" : {
			"lineColor" : "#A8A8A8",
			"backGroundColor" : ["#F4F4F4","#F0F0F0","#EDEDED", "#E7E7E7", "#E4E4E4"]
		},
		"active" : {
			"lineColor" : "#4D90FC",
			"backGroundColor" : ["#E8E8E8","#E7E7E7","#E4E4E4", "#E0E0E0", "#D8D8D8"]
		}
	},
	"table-client": {
		"extends": "widget",
		"common" : {
			"roundRadius" : 0
		},
		"normal" : {
			"lineColor" : "#A8A8A8"
		},
		"over" : {
			"lineColor" : "#A8A8A8"
		},
		"active" : {
			"lineColor" : "#4D90FC"
		}
	},
	"table-header-item.inc": {
		"extends": "table-header-item",
		"common" : {
			"foreGroundImage" : "images/@density/arrow-up.png"
		}
	},
	"table-header-item.dec": {
		"extends": "table-header-item",
		"common" : {
			"foreGroundImage" : "images/@density/arrow-down.png"
		}
	},
	"table-index-item": {
		"extends": "widget",
		"common" : {
			"roundRadius" : 0
		},
		"normal" : {
			"lineColor" : "#A8A8A8",
			"backGroundColor" : ["#F6F6F6","#EEEEEE","#E9E9E9", "#E3E3E3", "#E1E1E1"]
		},
		"over" : {
			"lineColor" : "#A8A8A8",
			"backGroundColor" : ["#F4F4F4","#F0F0F0","#EDEDED", "#E7E7E7", "#E4E4E4"]
		},
		"active" : {
			"lineColor" : "#4D90FC",
			"backGroundColor" : ["#E8E8E8","#E7E7E7","#E4E4E4", "#E0E0E0", "#D8D8D8"]
		}
	},
	"menu": {
		"extends": "widget",
		"common" : {
			"lineWidth":1,
			"roundRadius":0,
			"lineColor":"#CCCCCC"
		}
	},
	"switch": {
		"extends": "widget",
		"common" : {
			"lineWidth":1,
			"backGroundColor":"green",
			"foreGroundColor":"#EEEEEE",
			"lineColor":"#CCCCCC"
		}
	},
	"widget.transparent": {
		 "normal" : {}
	},
	"tab-button.close": {
		"extends": "button",
		"common" : {
			"backGroundImageDrawType":"ICON"
		},
		 "normal" : {"backGroundImage" : "images/@density/close.normal.png"},
		 "over" : {"backGroundImage" : "images/@density/close.over.png"},
		 "active" : {"backGroundImage" : "images/@density/close.over.png"}
	},
	"tab-button.current": {
		"extends": "widget",
		"common" : {
			"lineColor" : "#4D90FC"
		},
		"normal" : {
			"backGroundColor" : ["#F6F6F6","#EEEEEE","#E9E9E9", "#E3E3E3", "#E1E1E1"]
		},
		"over" : {
			"backGroundColor" : ["#F4F4F4","#F0F0F0","#EDEDED", "#E7E7E7", "#E4E4E4"]
		},
		"active" : {
			"backGroundColor" : ["#E8E8E8","#E7E7E7","#E4E4E4", "#E0E0E0", "#D8D8D8"]
		}
	},
	"tab-button.normal": {
		"extends": "widget",
		"common" : {
			"lineColor" : "#A8A8A8"
		},
		"normal" : {
			"backGroundColor" : ["#F6F6F6","#EEEEEE","#E9E9E9", "#E3E3E3", "#E1E1E1"]
		},
		"over" : {
			"backGroundColor" : ["#F4F4F4","#F0F0F0","#EDEDED", "#E7E7E7", "#E4E4E4"]
		},
		"active" : {
			"backGroundColor" : ["#E8E8E8","#E7E7E7","#E4E4E4", "#E0E0E0", "#D8D8D8"]
		}
	},
	"tab-control": {
		"extends": "widget",
		"common" : {
			"lineWidth":1,
			"lineColor":"#CCCCCC"
		}
	},
	"menu-bar": {
		"extends": "widget",
		"common" : {
			"backGroundColor" : "#E8EbF2"
		}
	},
	"menu-bar-item": {
		"extends": "widget",
		"normal" : {
			"backGroundColor" : null
		},
		"over" : {
			"backGroundColor" : "#3E93F9"
		},
		"active" : {
			"backGroundColor" : "#3E93F9"
		}
	},
	"menu-item": {
		"extends": "list-item",
		"common" : {
			"lineWidth":0,
			"textAlign" : "left",
			"lineColor":"#CCCCCC"
		},
		"normal" : {
			"backGroundColor" : null
		},
		"over" : {
			"backGroundColor" : "#3E93F9"
		},
		"active" : {
			"backGroundColor" : "#3E93F9"
		},
		"disable" : {
			"textColor" : "#CCCCCC",
			"backGroundColor" : null
		}
	},
	"menu-item.space": {
		"extends": "list-item",
		"common" : {
			"lineWidth":0,
			"textAlign" : "left",
			"lineColor":"#CCCCCC",
			"backGroundColor" : null
		}
	},
	"menu-item.checkable": {
		"extends": "menu-item",
		"common" : {
			"foreGroundImage" : "images/@density/menu-item-checked.png"
		}
	},
	"list-item.checkable": {
		"extends": "menu-item",
		"common" : {
			"foreGroundImage" : "images/@density/menu-item-checked.png"
		}
	},
	"menu-item.folder": {
		"extends": "menu-item",
		"common" : {
			"foreGroundImage" : "images/@density/menu-item-more.png"
		}
	},
	"dialog.title-bg": {
		"extends": "widget",
		"common" : {
			"roundType" : "top",
			"roundRadius" : 5,
			"backGroundColor" : ["#F6F6F6","#EEEEEE","#E9E9E9", "#E3E3E3", "#E1E1E1"]
		}
	},
	"dialog.title-text": {
		"extends": "label",
		"common" : {
			"textAlign" : "left"
		}
	},
	"accordion": {
		"extends": "widget",
		"common" : {
			"roundRadius" : 0,
			"lineColor" : "#9D9D9D",
			"backGroundColor" : null
		}
	},
	"property-sheets": {
		"extends": "widget",
		"common" : {
			"roundRadius" : 0,
			"lineColor" : "#9D9D9D",
			"backGroundColor" : null
		}
	},
	"collapsable-title": {
		"extends": "label",
		"common" : {
			"roundRadius" : 0,
			"textAlign" : "left"
		}
	},
	"collapsable-title.expanded": {
		"extends": "collapsable-title",
		"common" : {
			"foreGroundImage":"images/@density/expand.png",
			"backGroundColor" : ["#F6F6F6","#EEEEEE","#E9E9E9", "#E3E3E3", "#E1E1E1"]
		}
	},
	"collapsable-title.collapsed": {
		"extends": "collapsable-title",
		"common" : {
			"foreGroundImage":"images/@density/collapse.png",
			"backGroundColor" : ["#E6E6E6","#DDDDDD","#D9D9D9", "#D3D3D3", "#D1D1D1"]
		}
	},
	"messagebox.content": {
		"extends": "label",
		"common" : {
			"textAlign" : "left",
			"textBaseline" : "middle"
		}
	},
	"messagebox": {
		"extends": "widget",
		"common" : {
			"roundRadius" : 5,
			"backGroundColor" : "#ECECEC",
			"lineColor" : "#9D9D9D"
		}
	},
	"messagebox.toast": {
		"extends": "widget",
		"common" : {
			"roundRadius" : 5,
			"backGroundColor" : "#CCCCCC",
			"lineColor" : null
		}
	},
	"messagebox.alert.icon": {
		"extends": "widget",
		"common" : {
			"backGroundImage" : "images/@density/alert.png",
			"backGroundImageDrawType":"ICON"
		}
	},
	"messagebox.info.icon": {
		"extends": "widget",
		"common" : {
			"backGroundImage" : "images/@density/info.png",
			"backGroundImageDrawType":"ICON"
		}
	},
	"messagebox.question.icon": {
		"extends": "widget",
		"common" : {
			"backGroundImage" : "images/@density/question.png",
			"backGroundImageDrawType":"ICON"
		}
	},
	"messagebox.button.close": {
		"extends": "button",
		"common" : {
			"backGroundImageDrawType":"ICON"
		},
		 "normal" : {"backGroundImage" : "images/@density/close.normal.png"},
		 "over" : {"backGroundImage" : "images/@density/close.over.png"},
		 "active" : {"backGroundImage" : "images/@density/close.over.png"}
	},
	"rich-text": {
		"extends": "widget"
	},
	"rich-text-edit": {
		"extends": "widget"
	},
	"ruler": {
		"extends": "widget",
		"common" : {
			"backGroundColor" : null,
			"textAlign" : "left"
		}
	},
	"vruler": {
		"extends": "ruler"
	},
	"hruler": {
		"extends": "ruler"
	},
	"edit.table": {
		"extends": "edit",
		"common" : {
			"roundRadius" : 0
		}
	},
	"combo-box.table": {
		"extends": "combo-box",
		"common" : {
			"roundRadius" : 0
		},
		"normal" : {
			"lineColor" : null, 
			"backGroundColor" : null
		},
		"over" : {
			"lineColor" : null, 
			"backGroundColor" : null
		},
		"active" : {
			"lineColor" : null, 
			"backGroundColor" : null
		}
	},
	"label.table": {
		"extends": "label",
		"common" : {
			"roundRadius" : 0
		}
	},
	"window-normal": {
		"extends": "widget"
	}
}
