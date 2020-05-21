#pragma once

#define _USE_MATH_DEFINES
#include "DisplayableObject.h"
#include "Animation.h"
#include "../HeaderFiles/Korok.h"
#include "../HeaderFiles/Tree.h"
#include "../HeaderFiles/Rock.h"
#include "../HeaderFiles/Campfire.h"
#include "../Shared/Shapes.h"

class Island :
	public DisplayableObject,
	public Animation
{
public:
	Island();
	Island(GLuint* _texids);
	~Island();
	void Display();
	void Update(const double& deltaTime);
private:
	Korok* korok1;
	Korok* korok2;
	Korok* korok3;
	Tree* tree1;
	Tree* tree2;
	Rock* rock;
	Rock* rock2;
	Campfire* campfire;
	GLuint sideTex, topTex = -1;
	void drawIsland();
	void configure();
};

