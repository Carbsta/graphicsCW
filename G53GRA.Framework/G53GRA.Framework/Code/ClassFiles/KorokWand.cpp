#include "../HeaderFiles/KorokWand.h"

KorokWand::KorokWand() {}

KorokWand::~KorokWand() {}

KorokWand::KorokWand(GLuint _texid)
{
	texid = _texid;
	if (texid != -1) toTexture = true;
}

void KorokWand::Display()
{
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

		drawStick();
		drawFruit();

		glPopAttrib();
	}
	glPopMatrix();
}

void KorokWand::drawStick()
{
	GLfloat splane[] = { 1.0f, 0.0f, 0.0f, 0.0f };
	GLfloat tplane[] = { 0.0f, 1.0f, 0.0f, 0.0f };
	if (toTexture) {
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texid);
		glEnable(GL_TEXTURE_GEN_S);
		glEnable(GL_TEXTURE_GEN_T);
		glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
		glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
		glTexGenfv(GL_S, GL_OBJECT_PLANE, splane);
		glTexGenfv(GL_T, GL_OBJECT_PLANE, tplane);
	}
	glPushMatrix();
	{
		
		glScalef(0.25f, 0.25f, 0.25f);
		glPushMatrix(); 
		{
			glScalef(0.1f, 1.f, 0.1f);
			glutSolidCube(1.f);
		}
		glPopMatrix();

		glTranslatef(0.f, 1.f, 0.f);

		glPushMatrix();
		{
			glTranslatef(0.1f, -0.28f, 0.f);
			glRotatef(-21.801f, 0.f, 0.f, 1.f);
			glScalef(0.1f, 0.5f, 0.1f);
			glutSolidCube(1.f);
		}
		glPopMatrix();

		glTranslatef(0.f, 0.4f, 0.f);

		glPushMatrix();
		{
			glTranslatef(0.1f, -0.28f, 0.f);
			glRotatef(21.801f, 0.f, 0.f, 1.f);
			glScalef(0.1f, 0.6f, 0.1f);
			glutSolidCube(1.f);
		}
		glPopMatrix();

		glTranslatef(0.f, 0.9f, 0.f);

		glScalef(0.1f, 2.f, 0.1f);
		glutSolidCube(1.f);
	}
	glPopMatrix();
	if (toTexture) {
		glDisable(GL_TEXTURE_GEN_S);
		glDisable(GL_TEXTURE_GEN_T);
		glDisable(GL_TEXTURE_2D);
	}
}

void KorokWand::drawFruit()
{
	float mat_colour[]                      // colour reflected by diffuse light
		= { 0.745f, 0.133f, 0.149f, 1.f };				// red
	float mat_ambient[]                     // ambient colour
		= { 0.388f, 0.067f, 0.063f, 1.f };			// darker red
	float mat_specular[]                    // specular colour
		= { 1.f, 0.996f, 1.f, 1.f };				// near white
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambient); // set colour for ambient reflectance
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_colour);  // set colour for diffuse reflectance
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular); // set colour for specular reflectance
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 50.f); // shiny berries

	glPushMatrix();
	{
		glTranslatef(-0.05f, 0.8f, 0.f);
		glScalef(0.05f, 0.05f, 0.05f);
		glutSolidSphere(1.f, 10, 10);
	}
	glPopMatrix();

	glPushMatrix();
	{
		glTranslatef(0.f, 0.6f, 0.05f);
		glScalef(0.05f, 0.05f, 0.05f);
		glutSolidSphere(1.f, 10, 10);
	}
	glPopMatrix();

	glPushMatrix();
	{
		glTranslatef(0.05f, 0.7f, 0.f);
		glScalef(0.05f, 0.05f, 0.05f);
		glutSolidSphere(1.f, 10, 10);
	}
	glPopMatrix();

	glPushMatrix();
	{
		glTranslatef(0.05f, 0.3f, -0.05f);
		glScalef(0.05f, 0.05f, 0.05f);
		glutSolidSphere(1.f, 10, 10);
	}
	glPopMatrix();
	glPopAttrib();
}