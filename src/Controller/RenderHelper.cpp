#include "RenderHelper.h"

ofFbo RenderHelper::blurFbo1 = ofFbo();
ofFbo RenderHelper::blurFbo2 = ofFbo();
ofShader RenderHelper::maskShader = ofShader();
ofFbo::Settings RenderHelper::blurSettings = ofFbo::Settings();
ofShader RenderHelper::blurShaderX = ofShader();
ofShader RenderHelper::blurShaderY = ofShader();
ofPoint RenderHelper::windowSize = ofPoint(1280,720);

void RenderHelper::init(int w, int h)
{	
	if (!maskShader.isLoaded())
		maskShader.load("shader/mask");

	if (!blurShaderX.isLoaded())
		blurShaderX.load("shader/shaderBlurX");
	
	if (!blurShaderY.isLoaded())
		blurShaderY.load("shader/shaderBlurY");
	
	ofFbo::Settings s;
	s.width = ofGetWidth();
	s.height = ofGetHeight();
	s.internalformat = GL_RGBA;
	s.textureTarget = GL_TEXTURE_RECTANGLE_ARB;
	s.maxFilter = GL_LINEAR; GL_NEAREST;
	s.numSamples = 0;
	s.numColorbuffers = 1;
	s.useDepth = false;
	s.useStencil = false;

	blurFbo1.allocate(s);
	blurFbo2.allocate(s);
}


ofColor RenderHelper::getRandomColor()
{
	switch (int(ofRandom(255)) % 5)
	{
	case 0:
		return ofColor::green;
		break;

	case 1:
		return ofColor::burlyWood;
		break;

	case 2:
		return ofColor::blue;
		break;

	case 3:
		return ofColor::blueSteel;
		break;

	default:
		return ofColor::brown;
	}
}