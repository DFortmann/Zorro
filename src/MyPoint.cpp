#include "MyPoint.h"

MyPoint::MyPoint(ofVec2f _pos) {
	pos = _pos;
}

MyPoint::MyPoint(ofVec2f _pos, ofVec2f _cp1, ofVec2f _cp2) {
	pos = _pos;
	cp1 = _cp1;
	cp2 = _cp2;
	isCurve = true;
}

void MyPoint::makeCurve(ofVec2f _cp1, ofVec2f _cp2) {
	cp1 = _cp1;
	cp2 = _cp2;
	isCurve = true;
}

void MyPoint::translate(ofVec2f dir) {
	pos += dir;
	if (isCurve) {
		cp1 += dir;
		cp2 += dir;
	}
}