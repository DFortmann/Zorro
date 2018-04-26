#pragma once
#include "ofMain.h"

class AboutText {
public:
	static void init();
	static void drawAbout();
	static void drawHelp();
	static void drawShortcuts();

private:
	static ofTrueTypeFont textFont, headerFont, bigHeaderFont;
};