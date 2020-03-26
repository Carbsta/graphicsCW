#pragma once

#define _USE_MATH_DEFINES
#include "DisplayableObject.h"
#include <cmath>

class KorokMask :
	public DisplayableObject
{
public:
	KorokMask();
	KorokMask(GLuint _texId);
	~KorokMask();
	void Display();
private:
	void drawMask();
	/**
	* Draws a circle between start and end.
	* 0 <= start <= end <= 2 * M_PI
	*/
	void drawCircleSegment(float r, float start, float end);
	GLuint texid = -1;
	bool toTexture = false;
};