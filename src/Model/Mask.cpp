#include "Mask.h"

vector<MaskElem> Mask::elems		= vector<MaskElem>();
vector<vector<int>> Mask::selPoints = vector<vector<int>>();
int Mask::selShape		 = -1;
bool Mask::selChange	 = true;
bool Mask::drawOutlines	 = false;
bool Mask::drawLayers	 = false;
ofImage Mask::finalImage = ofImage();

void Mask::init(int width, int height)
{
	RenderHelper::init(width, height);
	selChange = true;

	for (int i = 0; i < elems.size(); ++i)
		elems[i].refresh = true;
}

void Mask::draw()
{
	if (selChange)
	{
		selChange = false;

		if (selShape > -1)
			DatGui::myOfxDatGui->getSlider("Blur", "Shape")->setValue(elems[selShape].blurAmnt);

		else
			DatGui::myOfxDatGui->getSlider("Blur", "Shape")->setValue(0);
	}

	drawShapes();

	if (drawOutlines || drawLayers)
		for (int i = 0; i < elems.size(); ++i)
		{
			MaskElem& elem = elems[i];
			if (drawLayers) elem.drawInfo(ofToString(i), i == selShape);
			if (drawOutlines && i != selShape) elem.drawOutline(false);
		}

	if (selShape > -1)
	{
		elems[selShape].drawOutline(true);
		elems[selShape].drawPoints(selPoints);
	}

}

void Mask::save(string path) {
	if (!path.empty())
	{
		ofBackground(DatGui::brightness);
		drawShapes();
		finalImage.grabScreen(0, 0, RenderHelper::windowSize.x, RenderHelper::windowSize.y);
		finalImage.save(path);
	}
}

void Mask::drawShapes()
{
	for (int i = 0; i < elems.size(); ++i)
	{
		ofTexture& tex = elems[i].getTexture();

		if (elems[i].isMask)
		{
			RenderHelper::maskShader.begin();
			RenderHelper::maskShader.setUniform1f("brightness", DatGui::brightness / 255.0);
			tex.draw(0, 0);
			RenderHelper::maskShader.end();
		}
		else tex.draw(0, 0);
	}
}