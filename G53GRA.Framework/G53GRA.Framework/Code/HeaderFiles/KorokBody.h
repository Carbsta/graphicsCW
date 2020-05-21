#pragma once

#define _USE_MATH_DEFINES
#include "DisplayableObject.h"
#include "Animation.h"
#include "../Shared/Shapes.h"

class KorokBody :
	public DisplayableObject,
	public Animation
{
public:
	KorokBody();
	~KorokBody();
	void Display();
	void Update(const double& deltaTime);
	void setArmSpeed(float _armSpeed);
private:
	void drawKorok();
	void drawLegs();
	void drawBody();
	void drawArms();
	void drawNose();
	void drawHorns();
	float res;
	float mat_colour[4] = { 0.784f, 0.808f, 0.627f, 1.f };
	float mat_ambient[4] = { 0.325f, 0.471f, 0.298f, 1.f };
	float mat_specular[4] = { 0.f, 0.f, 0.f, 1.f };
	float mat_colour_dark[4] = { 0.698f, 0.725f, 0.553f, 1.f };
	float mat_ambient_dark[4] = { 0.294f, 0.412f, 0.278f, 1.f };
	float mat_specular_dark[4] = { 0.f, 0.f, 0.f, 1.f };
	float aT = 0.f;
	int armDistance = 5;
	float armSpeed = 2.f;
	float lArmRot = 0.f;
	float rArmRot = 0.f;
};