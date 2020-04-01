#include "../HeaderFiles/KorokBody.h"

KorokBody::KorokBody() {}

KorokBody::KorokBody(GLuint _texid) {
	texid = _texid;
	if (texid != -1) toTexture = true;
}

KorokBody::~KorokBody() {}

void KorokBody::Display()
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

		glTranslatef(0.f, -0.2f, 0.f);
		drawKorok();

		glPopAttrib();
	}
	glPopMatrix();
}

void KorokBody::drawSegment(float lr, float ur, float res = 0.1 * M_PI)
{
	float t = 0.f;
	float lx = lr * cos(t);
	float lz = lr * sin(t);
	float ly = 0.f;
	float ux = ur * cos(t);
	float uz = ur * sin(t);
	float uy = 1.f;

	glBegin(GL_TRIANGLE_STRIP);

	glNormal3f(lx, 0.f, lz);
	glVertex3f(lx, ly, lz);

	do
	{
		t += res;
		lx = lr * cos(t);
		lz = lr * sin(t);
		ux = ur * cos(t);
		uz = ur * sin(t);

		glNormal3f(ux, 0.f, uz);
		glVertex3f(ux, uy, uz);

		glNormal3f(lx, 0.f, lz);
		glVertex3f(lx, ly, lz);

	} while (t <= (2 * M_PI) + res);

	glEnd();
}

void KorokBody::drawCone(float res = 0.1 * M_PI)
{
	float t = 0.f;
	float r = 1.f;
	float x = r * cos(t);
	float y = 0.0f;
	float z = r * sin(t);

	glBegin(GL_TRIANGLE_FAN);

	glNormal3f(0.f, -1.f, 0.0f);

	glVertex3f(0.f, -1.f, 0.f);  // base of the cone

	glNormal3f(x, 0.f, z);
	glVertex3f(x, y, z);

	do
	{
		t += res;
		x = r * cos(t);
		z = r * sin(t);

		glNormal3f(x, 0.f, z);
		glVertex3f(x, y, z);

	} while (t <= 2 * M_PI);

	glEnd();
}

void KorokBody::drawKorok() 
{
	drawLegs();
	drawBody();
	drawArms();
	drawNose();
}

void KorokBody::drawLegs()
{
	glPushMatrix();
	{
		glTranslatef(-0.15f, 0.f, 0.f);
		glScalef(0.15f, 0.15f, 0.15f);
		drawCone();
	};
	glPopMatrix();
	glPushMatrix();
	{
		glTranslatef(0.15f, 0.f, 0.f);
		glScalef(0.15f, 0.15f, 0.15f);
		drawCone();
	};
	glPopMatrix();
}

void KorokBody::drawArms()
{
	glPushMatrix();
	{
		glTranslatef(-0.4f, 0.66f, 0.f);
		glRotatef(-90.f, 0.f, 0.f, 1.f);
		glScalef(0.15f, 0.3f, 0.15f);
		drawCone();
	}
	glPopMatrix();
	glPushMatrix();
	{
		glTranslatef(0.4f, 0.66f, 0.f);
		glRotatef(90.f, 0.f, 0.f, 1.f);
		glScalef(0.15f, 0.3f, 0.15f);
		drawCone();
	}
	glPopMatrix();
}

void KorokBody::drawNose()
{
	glPushMatrix();
	{
		glTranslatef(0.f, 1.f, 0.4f);
		glRotatef(-90.f, 1.f, 0.f, 0.f);
		glScalef(0.05f, 0.25f, 0.05f);
		drawCone();
	}
	glPopMatrix();
}

void KorokBody::drawBody()
{
	glPushMatrix();
	{
		glScalef(0.3f, 0.01f, 0.3f);
		drawCone();
	}
	glPopMatrix();
	glPushMatrix();
	{
		glScalef(0.5f, 1.f, 0.5f);
		glPushMatrix();
		{
			glScalef(1.f, 0.1f, 1.f);
			drawSegment(0.6f, 0.9f);
		};
		glPopMatrix();

		glTranslatef(0.f, 0.1f, 0.f);
		glPushMatrix();
		{
			glScalef(1.f, 0.1f, 1.f);
			drawSegment(0.9f, 1.f);
		};
		glPopMatrix();

		glTranslatef(0.f, 0.1f, 0.f);
		glPushMatrix();
		{
			glScalef(1.f, 0.2f, 1.f);
			drawSegment(1.0f, 1.0f);
		};
		glPopMatrix();

		glTranslatef(0.f, 0.2f, 0.f);
		glPushMatrix();
		{
			glScalef(1.f, 0.5f, 1.f);
			drawSegment(1.0f, 0.8f);
		};
		glPopMatrix();

		glTranslatef(0.f, 0.5f, 0.f);
		glPushMatrix();
		{
			glScalef(1.f, 0.2f, 1.f);
			drawSegment(0.8f, 0.8f);
		};
		glPopMatrix();

		glTranslatef(0.f, 0.2f, 0.f);
		glPushMatrix();
		{
			glScalef(1.f, 0.4f, 1.f);
			drawSegment(0.8f, 0.9f);
		};
		glPopMatrix();

		glTranslatef(0.f, 0.4f, 0.f);
		glPushMatrix();
		{
			glScalef(1.f, 0.1f, 1.f);
			drawSegment(0.9f, 0.8f);
		};
		glPopMatrix();

		glTranslatef(0.f, 0.1f, 0.f);
		glPushMatrix();
		{
			glScalef(1.f, 0.05f, 1.f);
			drawSegment(0.8f, 0.7f);
		};
		glPopMatrix();

		glTranslatef(0.f, 0.05f, 0.f);
		glPushMatrix();
		{
			glScalef(1.f, 0.05f, 1.f);
			drawSegment(0.7f, 0.4f);
		};
		glPopMatrix();

	};
	glPopMatrix();
	glPushMatrix();
	{
		glTranslatef(0.f, 1.7f, 0.f);
		glScalef(0.2f, 0.01f, 0.2f);
		glRotatef(180.f, 1.f, 0.f, 0.f);
		drawCone();
	}
	glPopMatrix();
	
}



