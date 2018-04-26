#pragma once
#include "ofxDatGui.h"

class DatGuiTheme : public ofxDatGuiTheme
{

public:

	DatGuiTheme()
	{
		font.size = 12;
		init();
	}
};