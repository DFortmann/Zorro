#pragma once

#include "MaskElem.h"
#include "../ofMain.h"
#include "../Controller/RenderHelper.h"
#include "../View/DatGui.h"

using namespace std;

class Mask
{
public:
	static vector<MaskElem> elems;
	//first int is vertex, second int marks bezier ctrl point 1 or 2
	static vector<vector<int>> selPoints;

	static bool drawLayers;
	static int selShape;
	static bool selChange;
	static bool drawOutlines;

	static void init(int, int);
	static void draw();
	static void save(string path);

private:
	static ofImage finalImage;
	static void drawShapes();
};
