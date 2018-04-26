#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")   

#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main() {
	ofGLFWWindowSettings settings;
	settings.setGLVersion(3, 2);
	settings.setPosition(ofVec2f(200, 200));
	settings.width = 1280;
	settings.height = 720;
	settings.decorated = false;
	ofCreateWindow(settings);
	ofRunApp(new ofApp());
}