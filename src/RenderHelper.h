#pragma once
#include "ofMain.h"
#include "MaskElem.h"

class RenderHelper
{
public:
	static ofFbo blurFbo1;
	static ofFbo blurFbo2;
	static ofShader maskShader;
	static ofFbo::Settings blurSettings;
	static void init(int, int);
	static ofShader blurShaderX;
	static ofShader blurShaderY;
	static ofColor getRandomColor();
	static ofPoint windowSize;
};