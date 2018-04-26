#include "DatGui.h"
#include "DatGuiTheme.h"

ofxDatGui* DatGui::myOfxDatGui;
ofxDatGuiToggle*  DatGui::crosshairToggle;
ofxDatGuiColorPicker*  DatGui::crosshairColor;
bool DatGui::showAbout = false;
bool DatGui::showHelp = false;
bool DatGui::showShortcuts = false;
int DatGui::brightness = 0;

void DatGui::init()
{
	myOfxDatGui = new ofxDatGui(ofxDatGuiAnchor::TOP_LEFT);
	myOfxDatGui->setWidth(300);
	myOfxDatGui->setTheme(new DatGuiTheme());
	myOfxDatGui->addHeader(">> Zorro<<");

	ofxDatGuiFolder* fileFolder = myOfxDatGui->addFolder("File", ofColor::burlyWood);
	fileFolder->addButton("New");
	fileFolder->addButton("Open");
	fileFolder->addButton("Save");
	fileFolder->addButton("SaveAs");
	fileFolder->addButton("Exit");

	ofxDatGuiFolder* addRemoveFolder = myOfxDatGui->addFolder("Add/Remove", ofColor::darkBlue);
	addRemoveFolder->addButton("Add Rect");
	addRemoveFolder->addButton("Add Circle");
	addRemoveFolder->addButton("Copy Shape");
	addRemoveFolder->addButton("Remove Shape");
	addRemoveFolder->addButton("Add Point");
	addRemoveFolder->addButton("Remove Point");
	addRemoveFolder->addButton("Linear/Spline");

	ofxDatGuiFolder* shapeFolder = myOfxDatGui->addFolder("Shape", ofColor::mediumSpringGreen);
	shapeFolder->addButton("White");
	shapeFolder->addButton("Black");
	shapeFolder->addButton("Mask");
	shapeFolder->addSlider("Blur", 0, 500, 0);

	ofxDatGuiFolder* drawFolder = myOfxDatGui->addFolder("Draw", ofColor::mediumPurple);
	drawFolder->addSlider("BG", 0, 1, 0);
	drawFolder->addToggle("Outlines");
	drawFolder->addToggle("Layers");
	crosshairToggle = (ofxDatGuiToggle*)drawFolder->addToggle("Crosshair");
	crosshairColor = drawFolder->addColorPicker("Color");

	ofxDatGuiFolder* setupFolder = myOfxDatGui->addFolder("Window", ofColor::chocolate);
	setupFolder->addTextInput("x_Pos", "");
	setupFolder->addTextInput("y_Pos", "");
	setupFolder->addTextInput("width", "");
	setupFolder->addTextInput("height", "");
	setupFolder->addButton("Apply");

	ofxDatGuiFolder* helpFolder = myOfxDatGui->addFolder("Help", ofColor::honeyDew);
	helpFolder->addButton("Info");
	helpFolder->addButton("Shortcuts");
	helpFolder->addButton("About");
	

	myOfxDatGui->onButtonEvent(&DatGui::onButtonEvent);
	myOfxDatGui->onSliderEvent(&DatGui::onSliderEvent);
	myOfxDatGui->onToggleEvent(&DatGui::onToggleEvent);

	vector<int> vals = Settings::load();
	myOfxDatGui->getTextInput("width")->setText(ofToString(vals[0]));
	myOfxDatGui->getTextInput("height")->setText(ofToString(vals[1]));
	myOfxDatGui->getTextInput("x_Pos")->setText(ofToString(vals[2]));
	myOfxDatGui->getTextInput("y_Pos")->setText(ofToString(vals[3]));

	crosshairColor->setColor(255, 255, 0);

	applyWindowSettings();
}

void DatGui::onSliderEvent(ofxDatGuiSliderEvent e)
{
	if (e.target->is("Blur") && Mask::selShape > -1)
	{
		Mask::elems[Mask::selShape].blurAmnt = e.target->getValue();
		Mask::elems[Mask::selShape].refresh = true;
	}
	else if (e.target->is("BG"))
		brightness = e.target->getValue() * 255;
}

void DatGui::onToggleEvent(ofxDatGuiToggleEvent e)
{
	if (e.target->is("Outlines"))
		Mask::drawOutlines = e.checked;
	
	else if (e.target->is("Layers"))
		Mask::drawLayers = e.target->getChecked();
}


void DatGui::onButtonEvent(ofxDatGuiButtonEvent e)
{
	if (e.target->is("New"))
	{
		Mask::elems.clear();
		Mask::selShape = -1;
		Mask::selChange = true;
		MyFile::path = "";
	}
	else if (e.target->is("Open"))
	{
		vector<MaskElem> elems = MyFile::read();
		if (elems.size() > 0)
		{
			Mask::selShape = -1;
			Mask::elems = elems;
			Mask::selChange = true;
		}
	}
	else if (e.target->is("Save"))
		Mask::save(MyFile::save(Mask::elems));
	
	else if (e.target->is("SaveAs"))
		Mask::save(MyFile::saveAs(Mask::elems));
	
	else if (e.target->is("Exit")) ofExit();
	else if (e.target->is("Add Rect"))		EditShape::addRect();
	else if (e.target->is("Add Circle"))	EditShape::addCircle();
	else if (e.target->is("Copy Shape"))	EditShape::copyShape();
	else if (e.target->is("Add Point"))		EditShape::addPoint();
	else if (e.target->is("Remove Point"))	EditShape::removePoint();
	else if (e.target->is("Remove Shape"))	EditShape::removeShape();
	else if (e.target->is("Linear/Spline")) EditShape::toggleSpline();
	else if (e.target->is("White") && Mask::selShape > -1)
	{
		MaskElem& elem = Mask::elems[Mask::selShape];
		elem.color = ofColor(255,255);
		elem.isMask = false;
		elem.refresh = true;
	}
	else if (e.target->is("Black") && Mask::selShape > -1)
	{
		MaskElem& elem = Mask::elems[Mask::selShape];
		elem.color = ofColor(0, 255);
		elem.isMask = false;
		elem.refresh = true;
	}
	else if (e.target->is("Mask") && Mask::selShape > -1)
	{
		MaskElem& elem = Mask::elems[Mask::selShape];
		elem.color = ofColor(255);
		elem.isMask = true;
		elem.refresh = true;
	}
	else if (e.target->is("Apply")) applyWindowSettings();
	else if (e.target->is("About")) showAbout = true;
	else if (e.target->is("Info"))  showHelp = true;
	else if (e.target->is("Shortcuts")) showShortcuts = true;
}

void DatGui::applyWindowSettings()
{
	string xPosString = myOfxDatGui->getTextInput("x_Pos")->getText();
	int xPos = ofToInt(xPosString);
	myOfxDatGui->getTextInput("x_Pos")->setText(ofToString(xPos));

	string yPosString = myOfxDatGui->getTextInput("y_Pos")->getText();
	int yPos = ofToInt(yPosString);
	myOfxDatGui->getTextInput("y_Pos")->setText(ofToString(yPos));

	ofSetWindowPosition(xPos, yPos);

	string widthString = myOfxDatGui->getTextInput("width")->getText();
	int width = ofToInt(widthString);
	myOfxDatGui->getTextInput("width")->setText(ofToString(widthString));

	string heightString = myOfxDatGui->getTextInput("height")->getText();
	int height = ofToInt(heightString);
	myOfxDatGui->getTextInput("height")->setText(ofToString(heightString));

	if (width > 0 && height > 0)
	{
		RenderHelper::windowSize = ofPoint(width, height);

		if (width == ofGetScreenWidth() && height == ofGetScreenHeight()) 
			ofSetWindowShape(width, height+1);
		else ofSetWindowShape(width, height);
	}

	Mask::init(width, height);
}

ofRectangle DatGui::getRect()
{
	return ofRectangle(myOfxDatGui->getPosition(), myOfxDatGui->getWidth(), myOfxDatGui->getHeight());
}