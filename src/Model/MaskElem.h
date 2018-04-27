#pragma once

#include "../ofMain.h"
#include "MyPoint.h"
#include "../Controller/RenderHelper.h"
#include <vector>

class MaskElem 
{
public:
	MaskElem();
	MaskElem(const MaskElem&);
	ofPolyline shape;
	ofFbo texture;
	ofColor infoColor;
	bool refresh = true;

	vector<MyPoint> points;
	ofColor color = ofColor(255);
	bool isMask = false;
	float blurAmnt = 0;

	ofTexture getTexture();
	void update();
	void drawOutline(bool);
	void drawPoints(vector<vector<int>>);
	void drawInfo(string, bool);
};