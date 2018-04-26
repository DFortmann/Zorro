#pragma once

#include "ofMain.h"
#include "Mask.h"
#include "SelectShape.h"
#include "EditShape.h"
#include "MyFile.h"
#include "AboutText.h"
#include "DatGui.h"


class ofApp : public ofBaseApp{
public:
	void setup();
	void update();
	void draw();
	void exit();

	void keyPressed(int key);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseScrolled(int x, int y, float scrollX, float scrollY);
	bool dragMenu = false;
		
	ofVec2f mouseClickPos;
};
