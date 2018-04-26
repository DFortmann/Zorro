#pragma once
#include "ofMain.h"
#include "ofxFboBlur.h"
#include "MaskElem.h"

class Blur {

	ofxFboBlur gpuBlur;

public:
	void init(int,int);
	void draw(MaskElem&);
};