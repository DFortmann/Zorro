#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
	ofSetEscapeQuitsApp(false);
	DatGui::init();
	AboutText::init();
	ofEnableAlphaBlending();
	glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
	ofSetVerticalSync(true);
	ofSetFrameRate(60);
}

//--------------------------------------------------------------
void ofApp::update()
{
}

//--------------------------------------------------------------
void ofApp::draw()
{
	ofBackground(DatGui::brightness);
	if (DatGui::showAbout) AboutText::drawAbout();
	else if (DatGui::showHelp) AboutText::drawHelp();
	else if (DatGui::showShortcuts) AboutText::drawShortcuts();
	else
	{
		Mask::draw();

		if (DatGui::crosshairToggle->getChecked())
		{
			ofSetColor(DatGui::crosshairColor->getColor());
			ofDrawLine(ofPoint(0, mouseY), ofPoint(ofGetWidth(), mouseY));
			ofDrawLine(ofPoint(mouseX, 0), ofPoint(mouseX, ofGetHeight()));
			ofSetColor(255);
		}
	}

	/*
	ofSetColor(255, 0, 0);
	string fps = ofToString(ofGetFrameRate());
	ofDrawBitmapString(fps, RenderHelper::windowSize.x - 100, 20);
	ofSetColor(255);
	*/
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
	bool ctrlDown = ((GetKeyState(VK_CONTROL) & 0x80) > 0);
	bool shiftDown = ((GetKeyState(VK_SHIFT) & 0x80) > 0);

	switch (key) 
	{
	case OF_KEY_LEFT:
		if (ctrlDown)
			SelectShape::SelectNextPoint(false, shiftDown);
		else if(shiftDown)
			EditShape::move(ofVec2f(-0.5, 0));
		else
			EditShape::move(ofVec2f(-1, 0));
		break;
	
	case OF_KEY_RIGHT:
		if (ctrlDown)
			SelectShape::SelectNextPoint(true, shiftDown);
		else if(shiftDown)
			EditShape::move(ofVec2f(0.5, 0));
		else
			EditShape::move(ofVec2f(1, 0));
		break;
	
	case OF_KEY_UP:
		if (ctrlDown)
			SelectShape::SelectNextPoint(false, shiftDown);
		else if(shiftDown)
			EditShape::move(ofVec2f(0, -0.5));
		else
			EditShape::move(ofVec2f(0, -1));
		break;
	
	case OF_KEY_DOWN:
		if (ctrlDown)
			SelectShape::SelectNextPoint(true, shiftDown);
		else if (shiftDown)
			EditShape::move(ofVec2f(0, 0.5));
		else
			EditShape::move(ofVec2f(0, 1));
		break;
	
	case OF_KEY_F1:
		SelectShape::SelectNextShape(false);
		break;
	
	case OF_KEY_F2:
		SelectShape::SelectNextShape(true);
		break;
	
	case OF_KEY_F3:
		EditShape::moveShapeUp(false);
		break;
	
	case OF_KEY_F4:
		EditShape::moveShapeUp(true);
		break;
	}
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button)
{
	if (dragMenu != true && button == OF_MOUSE_BUTTON_LEFT) 
	{
		ofVec2f deltaMouse = ofVec2f(x, y);
		deltaMouse -= mouseClickPos;
		EditShape::move(deltaMouse);
		mouseClickPos = ofVec2f(mouseX, mouseY);
	}
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button)
{
	if (DatGui::showAbout) DatGui::showAbout = false;
	else if (DatGui::showHelp) DatGui::showHelp = false;
	else if (DatGui::showShortcuts) DatGui::showShortcuts = false;
	else 
	{
		if (!DatGui::getRect().inside(ofPoint(x, y))) 
			SelectShape::leftMouseButton(ofVec2f(x, y), ofGetKeyPressed(OF_KEY_SHIFT));
		
		else dragMenu = true;
	}
	mouseClickPos = ofVec2f(x, y);
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button)
{
	dragMenu = false;
	mouseClickPos = ofVec2f(x, y);
}

//--------------------------------------------------------------
void ofApp::mouseScrolled(int x, int y, float scrollX, float scrollY)
{
	EditShape::scale(scrollY == 1, ((GetKeyState(VK_SHIFT) & 0x80) > 0));
}


//--------------------------------------------------------------
void ofApp::exit()
{
	vector<int> vals;
	vals.push_back(RenderHelper::windowSize.x);
	vals.push_back(RenderHelper::windowSize.y);
	vals.push_back(ofGetWindowPositionX());
	vals.push_back(ofGetWindowPositionY());
	Settings::save(vals);
}
