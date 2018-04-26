#include "Blur.h"

void Blur::init(int width, int height) {
	ofFbo::Settings s;
	s.width = width;
	s.height = height;
	s.internalformat = GL_RGBA;
	s.textureTarget = GL_TEXTURE_RECTANGLE_ARB;
	s.maxFilter = GL_LINEAR; GL_NEAREST;
	s.numSamples = 4;
	s.numColorbuffers = 1;
	s.useDepth = false;
	s.useStencil = false;
	gpuBlur.setup(s, false);
	gpuBlur.blurPasses = 4;
	gpuBlur.numBlurOverlays = 1;
	gpuBlur.blurOverlayGain = 255;
}


void Blur::draw(MaskElem& elem) {
	if (elem.blurAmnt > 0) {
		gpuBlur.blurOffset = elem.blurAmnt;
		gpuBlur.beginDrawScene();
		ofClear(0);
		elem.drawShape();
		gpuBlur.endDrawScene();
		gpuBlur.performBlur();
		ofEnableBlendMode(OF_BLENDMODE_ALPHA);
		glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA); //pre-multiplied alpha 
		gpuBlur.drawBlurFbo();
	}
	else elem.drawShape();
}