#include "SelectShape.h"

void SelectShape::leftMouseButton(ofVec2f mousePos, bool shift) 
{
	if (Mask::selShape > -1) 
	{
		MaskElem& elem = Mask::elems[Mask::selShape];
		vector<int> selPoints = selectPoints(elem, mousePos);

		if (selPoints[0] == -1 && !elem.shape.inside(mousePos))
			selectShape(mousePos);

		else if (selPoints[0] == -1)
			Mask::selPoints.clear();

		else if (shift) 
		{
			if (std::find(Mask::selPoints.begin(), Mask::selPoints.end(), selPoints) == Mask::selPoints.end())
				Mask::selPoints.push_back(selPoints);
			else 
			{
				int index = std::find(Mask::selPoints.begin(), Mask::selPoints.end(), selPoints) - Mask::selPoints.begin();
				Mask::selPoints.erase(Mask::selPoints.begin() + index);
			}
		}
		else if (std::find(Mask::selPoints.begin(), Mask::selPoints.end(), selPoints) == Mask::selPoints.end()) 
		{
			Mask::selPoints.clear();
			Mask::selPoints.push_back(selPoints);
		}
	}
	else selectShape(mousePos);
}

void SelectShape::selectShape(ofVec2f mousePos) 
{
	int x = -1;

	for (int i = 0; i < Mask::elems.size(); ++i)
		if (Mask::elems[i].shape.inside(mousePos)) 
		{
			x = i;
			break;
		}

	if (x != Mask::selShape) 
	{
		if(Mask::selShape > -1)
			Mask::elems[Mask::selShape].refresh = true;
		
		if (x > -1)
			Mask::elems[x].refresh = true;
		
		Mask::selShape = x;
		Mask::selChange = true;
	}
	Mask::selPoints.clear();
}

void SelectShape::SelectNextShape(bool clockwise)
{
	int i = Mask::selShape;
	if (Mask::elems.size() > 0)
	{
		if (i > -1)
		{
			if (clockwise)
			{
				if (i + 1 >= Mask::elems.size()) Mask::selShape = 0;
				else Mask::selShape = i + 1;
			}
			else
			{
				if (i - 1 < 0) Mask::selShape = Mask::elems.size() - 1;
				else Mask::selShape = i - 1;
			}
		}
		else Mask::selShape = 0;

		Mask::selChange = true;
	}
}

vector<int> SelectShape::selectPoints(MaskElem& elem, ofVec2f mousePos) 
{
	vector<int> selPoints;
	selPoints.push_back(-1);
	selPoints.push_back(0);

	for (int i = 0; i < elem.points.size(); ++i) 
	{
		MyPoint point = elem.points[i];
		if (mousePos.distance(point.pos) < 10) selPoints[0] = i;
		else  if (point.isCurve) 
		{
			if (mousePos.distance(point.cp1) < 10) 
			{
				selPoints[0] = i;
				selPoints[1] = 1;
			}
			else if (mousePos.distance(point.cp2) < 10) 
			{
				selPoints[0] = i;
				selPoints[1] = 2;
			}
		}
	}

	return selPoints;
}

void SelectShape::SelectNextPoint(bool clockwise, bool shift)
{
	if (Mask::selShape > -1)
	{
		if(Mask::selPoints.size() > 0)
		{
			MaskElem& elem = Mask::elems[Mask::selShape];

			vector<int> selPoint = Mask::selPoints[Mask::selPoints.size() - 1];

			if (clockwise)
			{
				selPoint[0] = selPoint[0] + 1;
				if (selPoint[0] >= elem.points.size()) selPoint[0] = 0;
			}
			else
			{
				selPoint[0] = selPoint[0] - 1;
				if (selPoint[0] < 0) selPoint[0] = elem.points.size() - 1;
			}
			selPoint[1] = 0;
			if(!shift) Mask::selPoints.clear();
			Mask::selPoints.push_back(selPoint);
		}
		else
		{
			vector<int> selPoint;
			selPoint.push_back(0);
			selPoint.push_back(0);
			Mask::selPoints.push_back(selPoint);
		}
	}
}
