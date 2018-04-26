#pragma once
#include "Mask.h"

class EditShape {

public:
	static void move(ofVec2f);
	static void scale(bool, bool);
	static void addRect();
	static void addCircle();
	static void copyShape();
	static void addPoint();
	static void removePoint();
	static void removeShape();
	static void toggleSpline();
	static void moveShapeUp(bool);
};