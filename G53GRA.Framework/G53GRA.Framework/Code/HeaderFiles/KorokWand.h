#pragma once

#include "DisplayableObject.h"

class KorokWand :
	public DisplayableObject
{
public:
	KorokWand();
	KorokWand(GLuint _texid);
	~KorokWand();
	void Display();
private:
	void drawStick();
	void drawBalls();
	GLuint texid = -1;
	bool toTexture = false;
};