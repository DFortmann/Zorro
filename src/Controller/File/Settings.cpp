#include "Settings.h"

ofxXmlSettings Settings::myOfxXmlettings = ofxXmlSettings();

void Settings::save(vector<int> vals) {
	if (vals.size() >= 4) {
		myOfxXmlettings.clear();
		myOfxXmlettings.setValue("settings:width", vals[0]);
		myOfxXmlettings.setValue("settings:height", vals[1]);
		myOfxXmlettings.setValue("settings:x_Pos", vals[2]);
		myOfxXmlettings.setValue("settings:y_Pos", vals[3]);
		myOfxXmlettings.saveFile("settings.xml");
	}
}

vector<int> Settings::load() {
	vector<int> vals;
	if (myOfxXmlettings.loadFile("settings.xml")) {
		vals.push_back(myOfxXmlettings.getValue("settings:width", 1280));
		vals.push_back(myOfxXmlettings.getValue("settings:height", 720));
		vals.push_back(myOfxXmlettings.getValue("settings:x_Pos", 200));
		vals.push_back(myOfxXmlettings.getValue("settings:y_Pos", 200));
		return vals;
	}
	else return vector<int>{1280, 720, 200, 200};
}