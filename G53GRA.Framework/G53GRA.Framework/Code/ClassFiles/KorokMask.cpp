#include "../HeaderFiles/KorokMask.h"

KorokMask::KorokMask() {}

KorokMask::KorokMask(GLuint _texid)
{
	texid = _texid;
	if (texid != -1) toTexture = true;
}

KorokMask::~KorokMask() {}

void KorokMask::drawCircleSegment(float r, float start, float end, Segment seg, float res = 0.1 * M_PI)
{
	float t = start;
	float x = r * cos(start);
	float y = r * sin(start);
	float z = 0.f;

	glBegin(GL_TRIANGLE_FAN);

	glNormal3f(0.f, 0.f, 1.0f);

	if (toTexture) glTexCoord2f(uMapping(0, r, seg), vMapping(0, r, seg));
	glVertex3f(0.f, 0.f, 0.f);  // center of the circle

	if (toTexture) glTexCoord2f(uMapping(x, r, seg), vMapping(y, r, seg));
	glVertex3f(x, y, z);

	do
	{
		t += res;
		x = r * cos(t);
		y = r * sin(t);
		if (toTexture) glTexCoord2f(uMapping(x, r, seg), vMapping(y, r, seg));
		glVertex3f(x, y, z);

	} while (t <= end);

	glEnd();
}

void KorokMask::Display() 
{
	//float mat_colour[]
	//	= { 0.376f, 0.627f, 0.251f, 1.f }; // mid green
	//float mat_ambient[]
	//	= { 0.125f, 0.376f, 0.251f, 1.f }; // dark green
	//float mat_specular[]
	//	= { 0.f, 0.f, 0.f, 1.0f }; // no reflectance

	float mat_colour[]                      // colour reflected by diffuse light
		= { 1.f, 1.f, 1.f, 1.f };				// white
	float mat_ambient[]                     // ambient colour
		= { 0.5f, 0.5f, 0.5f, 1.f };			// grey
	float mat_specular[]                        // specular colour
		= { 0.f, 0.f, 0.f, 1.f };               // no reflectance (black)

	glPushMatrix();
	{
		glPushAttrib(GL_ALL_ATTRIB_BITS);
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambient); // set colour for ambient reflectance
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_colour);  // set colour for diffuse reflectance
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular); // set colour for specular reflectance

		// Project from Object Space to World Space
		glTranslatef(pos[0], pos[1], pos[2]);               // Position
		glScalef(scale[0], scale[1], scale[2]);             // Scale
		glRotatef(rotation[1], 0.f, 1.f, 0.f);              // Set orientation (Y)
		glRotatef(rotation[2], 0.f, 0.f, 1.f);              // Set orientation (Z)
		glRotatef(rotation[0], 1.f, 0.f, 0.f);              // Set orientation (X)

		drawMask();

		glPopAttrib();
	}
	glPopMatrix();
}

void KorokMask::drawMask()
{
	float radius_left_up = 1.f;
	float radius_right_up = 0.95f;
	float radius_left_side = 2.f;
	float radius_right_side = radius_left_side * radius_right_up;

	if (toTexture)
	{
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texid);
	}

	drawCircleSegment(radius_left_up, 0.f, M_PI, KorokMask::Segment::A);
	glPushMatrix();
	{
		glTranslatef(radius_left_up + radius_right_up, radius_right_side - radius_left_side, 0.f);
		drawCircleSegment(radius_right_up, 0.f, M_PI, KorokMask::Segment::B);
	}
	glPopMatrix();
	glPushMatrix();
	{
		glTranslatef(radius_left_up, 0.f, 0.f);
		drawCircleSegment(radius_left_side, M_PI, 1.5 * M_PI, KorokMask::Segment::C);
		
	};
	glPopMatrix();
	glPushMatrix();
	{
		glTranslatef(radius_left_up, radius_right_side - radius_left_side, 0.f);
		drawCircleSegment(radius_right_side, 1.5 * M_PI, 2 * M_PI, KorokMask::Segment::D);
	};
	glPopMatrix();
	
	if (toTexture) glDisable(GL_TEXTURE_2D);

}

float KorokMask::uMapping(float x, float r, Segment seg)
{
	float u = x / r;
	switch (seg)
	{
	case KorokMask::Segment::A:
		// scale to the range 0 - 0.5
		u = (u + 1.f) / 4;
		break;
	case KorokMask::Segment::B:
		// scale to the range 0.5 - 1.0
		u = (u + 3.f) / 4;
		break;
	case KorokMask::Segment::C:
		// scale to the range 0.0 - 1.0
		u = (u + 1.f) / 2;
		break;
	case KorokMask::Segment::D:
		// scale to the range 0.0 - 1.0
		u = ((u + 1.f) / 2);
		break;
	}
	return u;
}

float KorokMask::vMapping(float y, float r, Segment seg)
{
	float v = y / r;
	switch (seg)
	{
	case KorokMask::Segment::A:
		// scale to the range 0.5 - 1.0
		v = ((v + 3.f) / 4) - 0.25;
		break;
	case KorokMask::Segment::B:
		// scale to the range 0.25 - 0.75
		v = v * 0.95;
		v = ((v + 3.f) / 4) - 0.275;
		break;
	case KorokMask::Segment::C:
		// scale to the range 0.0 - 1.0
		v = (v + 1.f) / 2;
		break;
	case KorokMask::Segment::D:
		// scale to the range 0.0 - 1.0
		v = v * 0.95;
		v = ((v + 1.f) / 2) - 0.025;
		break;
	default:
		break;
	}
	return v;
}