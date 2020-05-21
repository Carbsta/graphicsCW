#pragma once

#define _USE_MATH_DEFINES
#include "DisplayableObject.h"
#include "Animation.h"
#include "../Shared/Shapes.h"

class Campfire :
	public DisplayableObject,
	public Animation
{
public:
	Campfire();
	Campfire(GLuint log, GLuint flame);
	~Campfire() {};
	void Display();
	void Update(const double& deltaTime);
private:
	void drawLog();
	void drawFlame();
	GLuint logTex = -1;
	GLuint flameSheet = -1;
	bool toTexLog = false;
	bool animateFlame = false;
	float texCoords[8] = { 0.f };
	float spreadFrame = 0.f;
	float spreadWidth = 4.f;
	float animationTime = 0.4f;
	float aT = 0.f;
	float flickerTimer = 0.f;
	bool flicker = false;
	GLfloat ambient[4] = { 0.f, 0.188f, 0.286f, 1.0f }; // dark blue
	GLfloat diffuse[4] = { 0.969f, 0.498f, 0.f, 1.0f }; // bright orange
	GLfloat specular[4] = { 0.988f, 0.749f, 0.286f, 1.0f }; //light yellow
	GLfloat lposition[4] = { -1.0f, 1.0f, 0.0f, 1.0f };
};