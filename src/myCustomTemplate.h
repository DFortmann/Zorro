#pragma once
#include "ofxDatGui.h"

class myCustomTemplate : public ofxDatGuiTemplate
{
public:
	myCustomTemplate() {
		// row characteristics //
		row.width = 200;
		row.height = 30;
		row.padding = 4;
		row.spacing = 2;
		row.stripeWidth = 4;
		// font characteristics //
		font.file = "font-verdana.ttf";
		font.size = 8;
		font.highlightPadding = 4;
		// gui / component colors //
		row.color.bkgd = ofColor::fromHex(0x1A1A1A);
		row.color.label = ofColor::fromHex(0xEEEEEE);
		row.color.mouseOver = ofColor::fromHex(0x777777);
		row.color.mouseDown = ofColor::fromHex(0x222222);
		row.color.inputArea = ofColor::fromHex(0x303030);
		// after everything is setup initialize the template // 
		init();
	}
};
