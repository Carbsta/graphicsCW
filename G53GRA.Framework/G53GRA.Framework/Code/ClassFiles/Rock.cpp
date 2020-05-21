#include "../HeaderFiles/Rock.h"

Rock::Rock() {}

Rock::Rock(GLuint _texid)
{
	texid = _texid;
	if (texid != -1) toTexture = true;
}

void Rock::setShape(Shape s)
{
	shape = s;
}

void Rock::Display()
{
	glPushMatrix();

	// Project from Object Space to World Space
	glTranslatef(pos[0], pos[1], pos[2]);   // position
	glScalef(scale[0], scale[1], scale[2]); // scale
	glRotatef(rotation[1], 0.f, 1.f, 0.f);  // set orientation (Y)
	glRotatef(rotation[2], 0.f, 0.f, 1.f);  // set orientation (Z)
	glRotatef(rotation[0], 1.f, 0.f, 0.f);  // set orientation (X)

	float mat_colour[]                      // colour reflected by diffuse light
		= { 1.f, 1.f, 1.f, 1.f };				// white
	float mat_ambient[]                     // ambient colour
		= { 0.5f, 0.5f, 0.5f, 1.f };			// grey
	float mat_spec[]                        // specular colour
		= { 0.f, 0.f, 0.f, 1.f };               // no reflectance (black)

	glPushAttrib(GL_ALL_ATTRIB_BITS); // save current style attributes
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambient); // set colour for ambient reflectance
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_colour);  // set colour for diffuse reflectance
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_spec);   // set colour for specular reflectance

	switch (shape) {
		case Shape::Single:
			drawSingle();
			break;
		case Shape::Large:
			drawLarge();
			break;
	}

	glPopAttrib();
	glPopMatrix();
}

void Rock::drawSingle() {
	drawSquareFrustum(1.f, 0.8f, texid);
}

void Rock::drawLarge() {
	//glScalef(2.f, 2.f, 2.f);
	drawSingle();
	glTranslatef(-0.3f, 0.f, -1.f);
	glScalef(1.2f, 1.2f, 1.2f);
	drawSingle();
	glTranslatef(1.f, 0.f, -0.2f);
	glScalef(1.5f, 1.5f, 1.5f);
	drawSingle();
}