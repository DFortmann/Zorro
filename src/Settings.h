#pragma once
#include "ofxXmlSettings.h"

class Settings {
public:
	static void save(vector<int>);
	static vector<int> load();

private:
	static ofxXmlSettings myOfxXmlettings;
};