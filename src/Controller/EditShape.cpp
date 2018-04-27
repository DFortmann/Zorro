#include "EditShape.h"

void EditShape::move(ofVec2f dir) {
	if (Mask::selShape > -1) {
		MaskElem& elem = Mask::elems[Mask::selShape];

		if (Mask::selPoints.size() > 0) {
			for (vector<vector<int>>::iterator it = Mask::selPoints.begin(); it != Mask::selPoints.end(); ++it) {
				MyPoint& point = elem.points[(*it)[0]];
				if ((*it)[1] == 1)
					point.cp1 += dir;
				else if ((*it)[1] == 2)
					point.cp2 += dir;
				else point.pos += dir;
			}
		}
		else {
			for (vector<MyPoint>::iterator it = elem.points.begin(); it != elem.points.end(); ++it)
				it->translate(dir);
		}
		elem.update();
	}
}

void EditShape::scale(bool up, bool shift) {
	if (Mask::selShape > -1) {
		MaskElem& elem = Mask::elems[Mask::selShape];
		ofPoint middle = elem.shape.getCentroid2D();
		float scaleFactor = shift ? 0.005 : 0.05;
		for (vector<MyPoint>::iterator it = elem.points.begin(); it != elem.points.end(); ++it) {
			ofVec2f dist = (*it).pos - middle;
			if (up) (*it).pos += dist * scaleFactor;
			else (*it).pos -= dist * scaleFactor;
			if ((*it).isCurve) {
				dist = (*it).cp1 - middle;
				if (up) (*it).cp1 += dist * scaleFactor;
				else (*it).cp1 -= dist * scaleFactor;

				dist = (*it).cp2 - middle;
				if (up) (*it).cp2 += dist * scaleFactor;
				else (*it).cp2 -= dist * scaleFactor;
			}
		}
		elem.update();
	}
}

void EditShape::addPoint() {
	if (Mask::selShape > -1 && Mask::selPoints.size() > 0) {
		MaskElem& elem = Mask::elems[Mask::selShape];
		int selPoint = Mask::selPoints[0][0];
		MyPoint point = elem.points[selPoint];

		int index = selPoint + 1;
		if (index > elem.points.size() - 1) index = 0;
		MyPoint nextPoint = elem.points[index];

		ofVec2f newPoint = ofVec2f(point.pos);
		newPoint -= nextPoint.pos;
		newPoint *= 0.5;
		newPoint += nextPoint.pos;
		elem.points.insert(elem.points.begin() + index, MyPoint(newPoint));
		elem.update();
	}
}

void EditShape::addRect()
{
	MaskElem elem;
	elem.points.push_back(MyPoint(ofVec2f(ofGetWidth() / 2 - 100, ofGetHeight() / 2 - 100)));
	elem.points.push_back(MyPoint(ofVec2f(ofGetWidth() / 2 + 100, ofGetHeight() / 2 - 100)));
	elem.points.push_back(MyPoint(ofVec2f(ofGetWidth() / 2 + 100, ofGetHeight() / 2 + 100)));
	elem.points.push_back(MyPoint(ofVec2f(ofGetWidth() / 2 - 100, ofGetHeight() / 2 + 100)));
	elem.update();
	Mask::elems.push_back(elem);
	Mask::selShape = Mask::elems.size() - 1;
	Mask::selChange = true;
}

void EditShape::addCircle() {
	MaskElem elem;
	float c = 0.551915024494 * 100;

	ofVec2f p00 = ofVec2f(ofGetWidth() / 2, ofGetHeight() / 2 + 100);
	ofVec2f p01 = ofVec2f(ofGetWidth() / 2 + c, ofGetHeight() / 2 + 100);
	ofVec2f p02 = ofVec2f(ofGetWidth() / 2 + 100, ofGetHeight() / 2 + c);

	ofVec2f p10 = ofVec2f(ofGetWidth() / 2 + 100, ofGetHeight() / 2);
	ofVec2f p11 = ofVec2f(ofGetWidth() / 2 + 100, ofGetHeight() / 2 - c);
	ofVec2f p12 = ofVec2f(ofGetWidth() / 2 + c, ofGetHeight() / 2 - 100);

	ofVec2f p20 = ofVec2f(ofGetWidth() / 2, ofGetHeight() / 2 - 100);
	ofVec2f p21 = ofVec2f(ofGetWidth() / 2 - c, ofGetHeight() / 2 - 100);
	ofVec2f p22 = ofVec2f(ofGetWidth() / 2 - 100, ofGetHeight() / 2 - c);

	ofVec2f p30 = ofVec2f(ofGetWidth() / 2 - 100, ofGetHeight() / 2);
	ofVec2f p31 = ofVec2f(ofGetWidth() / 2 - 100, ofGetHeight() / 2 + c);
	ofVec2f p32 = ofVec2f(ofGetWidth() / 2 - c, ofGetHeight() / 2 + 100);

	elem.points.push_back(MyPoint(p30, p32, p31));
	elem.points.push_back(MyPoint(p20, p22, p21));
	elem.points.push_back(MyPoint(p10, p12, p11));
	elem.points.push_back(MyPoint(p00, p02, p01));

	elem.update();
	Mask::elems.push_back(elem);
	Mask::selShape = Mask::elems.size() - 1;
	Mask::selChange = true;
}

void EditShape::copyShape()
{
	if (Mask::selShape > -1)
	{
		Mask::elems.push_back(MaskElem(Mask::elems[Mask::selShape]));
		Mask::selShape = Mask::elems.size() - 1;
		Mask::selChange = true;
	}
}

void EditShape::removePoint() {
	if (Mask::selShape > -1 && Mask::selPoints.size() > 0) {
		MaskElem& elem = Mask::elems[Mask::selShape];
		if (elem.points.size() > 3) {
			int selPoint = Mask::selPoints[0][0];
			elem.points.erase(elem.points.begin() + selPoint);
			elem.update();
			Mask::selPoints.clear();
		}
	}
}

void EditShape::removeShape()
{
	if (Mask::selShape > -1) {
		Mask::elems.erase(Mask::elems.begin() + Mask::selShape);
		Mask::selShape = -1;
		Mask::selChange = true;
	}
}

void EditShape::toggleSpline()
{

	if (Mask::selShape > -1 && Mask::selPoints.size() > 0) {
		int selPoint = Mask::selPoints[0][0];
		MaskElem& elem = Mask::elems[Mask::selShape];
		MyPoint& point = elem.points[selPoint];

		int index = selPoint - 1;
		if (index < 0) index = elem.points.size() - 1;
		MyPoint& lastPoint = elem.points[index];

		if (!point.isCurve) {
			ofVec2f cp1 = ofVec2f(lastPoint.pos);
			cp1 -= point.pos;
			cp1 *= 0.6;
			cp1 += point.pos;

			ofVec2f cp2 = ofVec2f(point.pos);
			cp2 -= lastPoint.pos;
			cp2 *= 0.6;
			cp2 += lastPoint.pos;

			point.makeCurve(cp1, cp2);
		}
		else point.isCurve = false;
		elem.update();
	}
}

void EditShape::moveShapeUp(bool up)
{
	if (Mask::selShape > -1 && Mask::elems.size() > 1)
	{
		int nextIndex;

		if (up)
		{
			nextIndex = Mask::selShape + 1;
			if (nextIndex >= Mask::elems.size()) nextIndex = 0;

		}
		else
		{
			nextIndex = Mask::selShape - 1;
			if (nextIndex < 0) nextIndex = Mask::elems.size() - 1;
		}
		iter_swap(Mask::elems.begin() + Mask::selShape, Mask::elems.begin() + nextIndex);
		Mask::selShape = nextIndex;
	}
}