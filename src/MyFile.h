#pragma once
#include "ofxXmlSettings.h"
#include "MaskElem.h"
#include "DatGui.h"

class MyFile {
public:
	static vector<MaskElem> read();
	static string saveAs(vector<MaskElem>&);
	static string save(vector<MaskElem>&);
	static ofxXmlSettings getXml(vector<MaskElem>&);
	static string path;
};