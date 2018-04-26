#include "MaskElem.h"

MaskElem::MaskElem()
{
	infoColor = RenderHelper::getRandomColor();
}

MaskElem::MaskElem(const MaskElem& elem)
{
	points		= elem.points;
	color		= elem.color;
	isMask		= elem.isMask;
	blurAmnt	= elem.blurAmnt;
	infoColor = RenderHelper::getRandomColor();
	
	update();
}

void MaskElem::update()
{
	shape.clear();

	for (int i = 0; i < points.size(); ++i) {
		MyPoint point = points[i];

		if (i == 0) shape.addVertex(point.pos);
		else if (!point.isCurve) shape.addVertex(point.pos);
		else shape.bezierTo(point.cp1, point.cp2, point.pos, 80);

		if (i == points.size() - 1)
		{
			point = points[0];

			if (point.isCurve)
				shape.bezierTo(point.cp1, point.cp2, point.pos, 80);
		}
	}

	shape.close();

	refresh = true;
}

ofTexture MaskElem::getTexture()
{
	if (refresh)
	{
		refresh = false;

		if (!texture.isAllocated() || texture.getWidth() != RenderHelper::windowSize.x || texture.getHeight() != RenderHelper::windowSize.y)
			texture.allocate(RenderHelper::windowSize.x, RenderHelper::windowSize.y, GL_RGBA, 8);

		texture.begin();
		ofClear(color.r, 0);

		ofFill();
		ofSetColor(color);
		ofBeginShape();
		for (int i = 0; i < shape.getVertices().size(); i++)
			ofVertex(shape.getVertices().at(i).x, shape.getVertices().at(i).y);
		ofEndShape(true);

		texture.end();

		if (blurAmnt > 0)
		{
			RenderHelper::blurFbo2.begin();
			ofClear(color.r, 0);
			texture.draw(0, 0);
			RenderHelper::blurFbo2.end();

			ofDisableAlphaBlending();

			for (int i = 0; i < 10; ++i)
			{
				float blurLevel = blurAmnt * (i + 1) / (101);

				RenderHelper::blurFbo1.begin();
				ofClear(color.r, 0);
				RenderHelper::blurShaderX.begin();
				RenderHelper::blurShaderX.setUniform1f("blurAmnt", blurLevel);
				RenderHelper::blurFbo2.draw(0, 0);
				RenderHelper::blurShaderX.end();
				RenderHelper::blurFbo1.end();

				RenderHelper::blurFbo2.begin();
				ofClear(color.r, 0);
				RenderHelper::blurShaderY.begin();
				RenderHelper::blurShaderX.setUniform1f("blurAmnt", blurLevel);
				RenderHelper::blurFbo1.draw(0, 0);
				RenderHelper::blurShaderY.end();
				RenderHelper::blurFbo2.end();
			}

			ofEnableAlphaBlending();
			glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);

			texture.begin();
			ofClear(color.r, 0);
			RenderHelper::blurFbo2.getTextureReference().draw(0, 0);
			texture.end();
		}
	}

	return texture.getTextureReference();
}

void MaskElem::drawOutline(bool selected)
{
	ofNoFill();
	ofSetLineWidth(2);

	if (selected) ofSetColor(ofColor(255, 0, 0));
	else ofSetColor(infoColor);
	ofBeginShape();
	
	for (int i = 0; i < shape.getVertices().size(); i++)
		ofVertex(shape.getVertices().at(i).x, shape.getVertices().at(i).y);
	
	ofEndShape(true);
	ofSetLineWidth(1);
	ofSetColor(255);
}

void MaskElem::drawPoints(vector<vector<int>> selPoints)
{
	ofFill();

	for (int i = 0; i < points.size(); ++i) 
	{
		const MyPoint& point = points[i];
		vector<int> checkPoints;
		checkPoints.push_back(i);
		checkPoints.push_back(0);

		if (find(selPoints.begin(), selPoints.end(), checkPoints) != selPoints.end())
			ofSetColor(0, 255, 0, 255);
		else ofSetColor(0, 0, 255, 255);

		ofDrawRectangle(point.pos[0] - 5, point.pos[1] - 5, 10, 10);

		if (point.isCurve) {
			int index = i - 1;
			if (index < 0) index = points.size() - 1;
			MyPoint lastPoint = points[index];

			ofSetColor(0, 0, 255, 255);
			ofDrawLine(lastPoint.pos[0], lastPoint.pos[1], point.cp1[0], point.cp1[1]);
			checkPoints[1] = 1;

			if (find(selPoints.begin(), selPoints.end(), checkPoints) != selPoints.end())
				ofSetColor(0, 255, 0, 255);
			else ofSetColor(0, 0, 255, 255);

			ofDrawCircle(point.cp1[0], point.cp1[1], 5);

			ofSetColor(0, 0, 255, 255);
			ofDrawLine(point.pos[0], point.pos[1], point.cp2[0], point.cp2[1]);

			checkPoints[1] = 2;

			if (find(selPoints.begin(), selPoints.end(), checkPoints) != selPoints.end())
				ofSetColor(0, 255, 0, 255);
			else ofSetColor(0, 0, 255, 255);

			ofDrawCircle(point.cp2[0], point.cp2[1], 5);
		}
	}
	ofSetColor(255);
}

void MaskElem::drawInfo(string info, bool selected)
{
	if (selected)
		ofSetColor(ofColor(255, 0, 0));
	else ofSetColor(infoColor);

	ofDrawBitmapString(info, shape.getCentroid2D());
	ofSetColor(255);
}
