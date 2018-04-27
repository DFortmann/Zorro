#pragma once
#include "ofMain.h"

class MyPoint {
public:
	ofVec2f pos, cp1, cp2;
	bool isCurve = false;

	MyPoint(ofVec2f);
	MyPoint(ofVec2f, ofVec2f, ofVec2f);

	void makeCurve(ofVec2f, ofVec2f);
	void translate(ofVec2f);
};