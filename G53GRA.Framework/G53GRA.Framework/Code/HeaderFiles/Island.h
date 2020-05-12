#pragma once

#define _USE_MATH_DEFINES
#include "DisplayableObject.h"
#include "../HeaderFiles/Korok.h"
#include "../HeaderFiles/Tree.h"
#include "../Shared/Shapes.h"

class Island :
	public DisplayableObject
{
public:
	Island();
	Island(GLuint* _texids);
	~Island();
	void Display();
private:
	Korok* korok1;
	Korok* korok2;
	Korok* korok3;
	Tree* tree1;
	Tree* tree2;
	void drawIsland();
	void configure();
};

