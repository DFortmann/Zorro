#include "AboutText.h"

ofTrueTypeFont AboutText::textFont = ofTrueTypeFont();
ofTrueTypeFont AboutText::headerFont = ofTrueTypeFont();
ofTrueTypeFont AboutText::bigHeaderFont = ofTrueTypeFont();

void AboutText::init() {
	textFont.load("font-verdana.ttf", 14);
	headerFont.load("font-verdana.ttf", 20);
	bigHeaderFont.load("font-verdana.ttf", 36);
}

void AboutText::drawAbout() {
	ofBackground(0);
	ofSetColor(255);

	string bigHeadString = "Zorro v0.2";
	ofRectangle bigHeadRect = bigHeaderFont.getStringBoundingBox(bigHeadString, 0, 0);
	bigHeaderFont.drawString(bigHeadString, ofGetWidth() / 2 - bigHeadRect.width / 2, 100);

	string headString = "Created by David Fortmann in May 2017.";
	ofRectangle headRect = headerFont.getStringBoundingBox(headString, 0, 0);
	headerFont.drawString(headString, ofGetWidth() / 2 - headRect.width / 2, 150 + bigHeadRect.height);

	vector<string> bodyText;
	bodyText.push_back("This app was written with openframeworks (openframeworks.cc).");
	bodyText.push_back(" ");
	bodyText.push_back("Using the great addon:");
	bodyText.push_back("ofxDatGui from Stephen Braitsch (http://braitsch.io)");
	bodyText.push_back(" ");
	bodyText.push_back("If you have any questions or want to give feedback, please contact me:");
	bodyText.push_back("David Fortmann (http://davidfortmann.ch)");
	bodyText.push_back("Mail: info@davidfortmann.ch");
	bodyText.push_back(" ");
	bodyText.push_back(" ");
	bodyText.push_back("This software is released under the MIT License.");

	float xPos = 170 + bigHeadRect.height + headRect.height;

	for (vector<string>::iterator it = bodyText.begin(); it != bodyText.end(); ++it) {
			ofRectangle bodyRect = textFont.getStringBoundingBox((*it), 0, 0);
			textFont.drawString((*it), ofGetWidth() / 2 - bodyRect.width / 2, xPos);
			xPos += bodyRect.height + 16;
		}
}

void AboutText::drawHelp() {
	ofBackground(0);
	ofSetColor(255);

	string bigHeadString = "Zorro v0.2";
	ofRectangle bigHeadRect = bigHeaderFont.getStringBoundingBox(bigHeadString, 0, 0);
	bigHeaderFont.drawString(bigHeadString, ofGetWidth() / 2 - bigHeadRect.width / 2, 100);

	string headString = "Info:";
	ofRectangle headRect = headerFont.getStringBoundingBox(headString, 0, 0);
	headerFont.drawString(headString, ofGetWidth() / 2 - headRect.width / 2, 150 + bigHeadRect.height);

	vector<string> bodyText;
	bodyText.push_back("This app lets you create smooth vector masks for projections.");
	bodyText.push_back(" ");
	bodyText.push_back("The easiest way to use it, is to mirror your desktop onto the projector.");
	bodyText.push_back("In the \"Window\" menu you can set the window position and size to make it fullscreen.");
	bodyText.push_back("These settings are stored in \"data/settings.xml\".");
	bodyText.push_back("Just delete this file, if you want to reset the window position.");
	bodyText.push_back(" ");
	bodyText.push_back("To create a mask open the \"Add/Remove\" menu and choose a shape to start with.");
	bodyText.push_back("You can add a point to the shape by selecting an existing point and click on the \"Add Point\" button.");
	bodyText.push_back("To remove a point make sure the right one is selected and click the \"Remove Point\" button.");
	bodyText.push_back("If you want to create a curve, select a point and click the \"Linear/Bezier\" button.");
	bodyText.push_back(" ");
	bodyText.push_back("You can move a shape or single points with the mouse or the arrow keys.");
	bodyText.push_back("Multiple points can be selected by holding down the shift key.");
	bodyText.push_back("With the scroll wheel you can resize a shape.");
	bodyText.push_back(" ");
	bodyText.push_back("Use the \"Blur\" menu to blur the selected shape.");
	bodyText.push_back("Add as many shapes to your mask as you need.");
	bodyText.push_back(" ");

	bodyText.push_back(" ");
	bodyText.push_back("If the menu is in your way, you can drag it by the title \">>Zorro<<\" to another position.");
	bodyText.push_back(" ");
	bodyText.push_back("Have fun.");

	float xPos = 170 + bigHeadRect.height + headRect.height;

	for (vector<string>::iterator it = bodyText.begin(); it != bodyText.end(); ++it) {
		ofRectangle bodyRect = textFont.getStringBoundingBox((*it), 0, 0);
		textFont.drawString((*it), ofGetWidth() / 2 - bodyRect.width / 2, xPos);
		xPos += bodyRect.height + 16;
	}
}


void AboutText::drawShortcuts() {
	ofBackground(0);
	ofSetColor(255);

	string bigHeadString = "Zorro v0.2";
	ofRectangle bigHeadRect = bigHeaderFont.getStringBoundingBox(bigHeadString, 0, 0);
	bigHeaderFont.drawString(bigHeadString, ofGetWidth() / 2 - bigHeadRect.width / 2, 100);

	string headString = "Shortcuts:";
	ofRectangle headRect = headerFont.getStringBoundingBox(headString, 0, 0);
	headerFont.drawString(headString, ofGetWidth() / 2 - headRect.width / 2, 150 + bigHeadRect.height);

	vector<string> bodyText;
	bodyText.push_back("Arrow Keys - Move selected shape or selected point.");
	bodyText.push_back(" ");
	bodyText.push_back("Ctrl + Arrow Keys - Select previous/next point.");
	bodyText.push_back(" ");
	bodyText.push_back("Ctrl + Shift + Arrow Keys - Add next point to selection.");
	bodyText.push_back(" ");
	bodyText.push_back("Shift Key - Finer controls.");
	bodyText.push_back(" ");
	bodyText.push_back("F1/F2 - Select previous/next shape.");
	bodyText.push_back(" ");
	bodyText.push_back("F3/F4 - Move shape a layer down or up.");
	bodyText.push_back(" ");

	float xPos = 170 + bigHeadRect.height + headRect.height;

	for (vector<string>::iterator it = bodyText.begin(); it != bodyText.end(); ++it) {
		ofRectangle bodyRect = textFont.getStringBoundingBox((*it), 0, 0);
		textFont.drawString((*it), ofGetWidth() / 2 - bodyRect.width / 2, xPos);
		xPos += bodyRect.height + 16;
	}
}