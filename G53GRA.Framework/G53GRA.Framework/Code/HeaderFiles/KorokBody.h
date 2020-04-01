#pragma once

#define _USE_MATH_DEFINES
#include "DisplayableObject.h"
#include <cmath>

class KorokBody :
	public DisplayableObject
{
public:
	KorokBody();
	KorokBody(GLuint _texid);
	~KorokBody();
	void Display();
private:
	GLuint texid = -1;
	bool toTexture = false;
	void drawKorok();
	void drawLegs();
	void drawBody();
	void drawArms();
	void drawNose();
	void drawSegment(float lr, float ur, float res);
	void drawCone(float res);
};