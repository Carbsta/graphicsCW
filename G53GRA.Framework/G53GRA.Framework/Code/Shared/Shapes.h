#pragma once

#ifdef __APPLE__ // if OS X
#include <glut/glut.h> // include freeglut libraries
#else // if Windows
#include <gl/glut.h> // include freeglut libraries
#endif

#define _USE_MATH_DEFINES
#include <cmath>
#include "VectorMath.h"

// A collection of methods for drawing common shapes with options for texturing.

void drawCone(float res, GLuint texid = -1);
void drawFrustum(float lr, float ur, float res, GLuint texid = -1);
void drawSmoothFrustum(float lr, float ur, GLuint texid = -1);
void drawSquareFrustum(float ls, float us, GLuint texid = -1);

/* Calculates the surface normal for a triangle defined by p1, p2, p3
Sets vector n to result*/
void surfaceNorm(const float* p1, const float* p2, const float* p3, float* n);