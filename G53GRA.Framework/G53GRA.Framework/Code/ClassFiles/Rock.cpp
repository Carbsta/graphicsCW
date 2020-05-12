#include "../HeaderFiles/Rock.h"

Rock::Rock() {}

Rock::Rock(GLuint _texid)
{
	texid = _texid;
	if (texid != -1) toTexture = true;
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

	glPopAttrib();
	glPopMatrix();
}