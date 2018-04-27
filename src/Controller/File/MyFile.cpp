#include "MyFile.h"

string MyFile::path = "";

vector<MaskElem> MyFile::read() {
	vector<MaskElem> elems;
	ofFileDialogResult res = ofSystemLoadDialog("Open Mask", false);

	if (res.bSuccess) {
		ofxXmlSettings shapes;
		 path = ofFilePath::removeExt(res.filePath);
		
		if (shapes.loadFile(string(path).append(".xml"))) {

			shapes.addTag("settings");
			shapes.pushTag("settings");
			float bright = shapes.getValue("bgColor", 0.0f);
			DatGui::myOfxDatGui->getSlider("BG", "Draw")->setValue(bright);
			DatGui::brightness = bright * 255;
			shapes.popTag();

			shapes.pushTag("shapes");

			for (int i = 0; i < shapes.getNumTags("shape"); ++i) {
				shapes.pushTag("shape", i);
				MaskElem elem;

				elem.blurAmnt = shapes.getValue("blurAmnt", 0.0f);
				elem.color = ofColor(shapes.getValue("color", 255));
				elem.isMask = shapes.getValue("isMask", 0) == 1;

				for (int j = 0; j < shapes.getNumTags("point"); ++j) {
					shapes.pushTag("point", j);

					ofVec2f ctrlPoint0;
					ctrlPoint0[0] = shapes.getValue("posX", 0);
					ctrlPoint0[1] = shapes.getValue("posY", 0);

					if (shapes.tagExists("cp1X")) {
						ofVec2f ctrlPoint1;
						ctrlPoint1[0] = shapes.getValue("cp1X", 0);
						ctrlPoint1[1] = shapes.getValue("cp1Y", 0);

						ofVec2f ctrlPoint2;
						ctrlPoint2[0] = shapes.getValue("cp2X", 0);
						ctrlPoint2[1] = shapes.getValue("cp2Y", 0);

						elem.points.push_back(MyPoint(ctrlPoint0, ctrlPoint1, ctrlPoint2));
					}
					else elem.points.push_back(MyPoint(ctrlPoint0));

					shapes.popTag();
				}
				shapes.popTag();
				elem.update();
				elems.push_back(elem);
			}
			shapes.popTag();
		}
	}
	return elems;
}

string MyFile::saveAs(vector<MaskElem>& elems) {
	ofFileDialogResult res = ofSystemSaveDialog("Mask.xml", "Save Mask");

	if (res.bSuccess) {
		path = ofFilePath::removeExt(res.filePath);
		ofxXmlSettings shapes = getXml(elems);
		shapes.saveFile(string(path).append(".xml"));
		return string(path).append(".png");
	}
	return  "";
}

string MyFile::save(vector<MaskElem>& elems) {
	if (path.empty()) 
		return saveAs(elems);
	else {
		ofxXmlSettings shapes = getXml(elems);
		shapes.saveFile(string(path).append(".xml"));
		return string(path).append(".png");
	}
}

ofxXmlSettings MyFile::getXml(vector<MaskElem>& elems) {
	ofxXmlSettings shapes;
	shapes.addTag("settings");
	shapes.pushTag("settings");
	shapes.addValue("bgColor", DatGui::myOfxDatGui->getSlider("BG", "Draw")->getValue());
	shapes.popTag();

	shapes.addTag("shapes");
	shapes.pushTag("shapes");

	for (int i = 0; i < elems.size(); ++i) {
		shapes.addTag("shape");
		shapes.pushTag("shape", i);
		shapes.addValue("blurAmnt", elems[i].blurAmnt);
		shapes.addValue("color", elems[i].color.r);
		shapes.addValue("isMask", elems[i].isMask);

		for (int j = 0; j < elems[i].points.size(); ++j) {
			shapes.addTag("point");
			shapes.pushTag("point", j);

			MyPoint point = elems[i].points[j];
			shapes.addValue("posX", point.pos[0]);
			shapes.addValue("posY", point.pos[1]);

			if (point.isCurve) {
				shapes.addValue("cp1X", point.cp1[0]);
				shapes.addValue("cp1Y", point.cp1[1]);
				shapes.addValue("cp2X", point.cp2[0]);
				shapes.addValue("cp2Y", point.cp2[1]);
			}
			shapes.popTag();
		}
		shapes.popTag();
	}
	shapes.popTag();

	return shapes;
}