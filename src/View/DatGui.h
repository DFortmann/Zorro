#pragma once
#include "../ofxDatGui.h"
#include "../Controller/File/Settings.h"
#include "../Model/Mask.h"
#include "../Controller/File/MyFile.h"
#include "../Controller/EditShape.h"

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