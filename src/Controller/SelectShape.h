#pragma once

#include "../Model/Mask.h"
#include <vector>

class SelectShape {

public:
	static void leftMouseButton(ofVec2f, bool);
	static void selectShape(ofVec2f);
	//static void SelectShape::selectShape(int);
	static void SelectNextShape(bool);
	static vector<int> selectPoints(MaskElem&, ofVec2f);
	static void SelectNextPoint(bool,bool);
	};