#pragma once
#include "ofxDatGui.h"
#include "Settings.h"
#include "Mask.h"
#include "MyFile.h"
#include "EditShape.h"

class DatGui
{
public:
	static ofxDatGuiToggle* crosshairToggle;
	static ofxDatGuiColorPicker* crosshairColor;
	static int brightness;
	static bool showAbout;
	static bool showHelp;
	static bool showShortcuts;
	static void init();
	static ofRectangle getRect();
	static ofxDatGui* myOfxDatGui;

private:
	static void onButtonEvent(ofxDatGuiButtonEvent);
	static void onSliderEvent(ofxDatGuiSliderEvent);
	static void onToggleEvent(ofxDatGuiToggleEvent);
	static void applyWindowSettings();
};