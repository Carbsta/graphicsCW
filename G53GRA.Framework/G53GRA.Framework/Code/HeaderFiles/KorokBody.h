#pragma once

#define _USE_MATH_DEFINES
#include "DisplayableObject.h"
#include <cmath>

class KorokBody :
	public DisplayableObject
{
public:
	KorokBody();
	~KorokBody();
	void Display();
private:
	void drawKorok();
	void drawLegs();
	void drawBody();
	void drawArms();
	void drawNose();
	void drawHorns();
	void drawSegment(float lr, float ur, float res);
	void drawCone(float res);
	float mat_colour[4] = { 0.784f, 0.808f, 0.627f, 1.f };
	float mat_ambient[4] = { 0.325f, 0.471f, 0.298f, 1.f };
	float mat_specular[4] = { 0.f, 0.f, 0.f, 1.f };
	float mat_colour_dark[4] = { 0.698f, 0.725f, 0.553f, 1.f };
	float mat_ambient_dark[4] = { 0.294f, 0.412f, 0.278f, 1.f };
	float mat_specular_dark[4] = { 0.f, 0.f, 0.f, 1.f };
};