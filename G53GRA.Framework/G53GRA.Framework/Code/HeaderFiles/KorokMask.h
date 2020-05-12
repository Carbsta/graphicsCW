#pragma once

#define _USE_MATH_DEFINES
#include "DisplayableObject.h"
#include <cmath>

class KorokMask :
	public DisplayableObject
{
public:
	KorokMask();
	KorokMask(GLuint _front, GLuint _back);
	~KorokMask();
	void Display();
	//enum class Segment { A, B, C, D };
private:
	//void drawMask();
	/**
	* Draws a circle between start and end.
	* 0 <= start <= end <= 2 * M_PI
	*/
	//void drawCircleSegment(float r, float start, float end, Segment seg, float res);
	//float uMapping(float x, float r, Segment seg);
	//float vMapping(float y, float r, Segment seg);
	GLuint front = -1;
	bool toFront = false;
	GLuint back = -1;
	bool toBack = false;
};