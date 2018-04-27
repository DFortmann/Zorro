#pragma once

#include "ofMain.h"
#include "Model/Mask.h"
#include "Controller/SelectShape.h"
#include "Controller/EditShape.h"
#include "Controller/File/MyFile.h"
#include "View/AboutText.h"
#include "View/DatGui.h"


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
