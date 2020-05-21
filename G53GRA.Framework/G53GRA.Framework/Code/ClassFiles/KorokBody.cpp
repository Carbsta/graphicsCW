#include "../HeaderFiles/KorokBody.h"

KorokBody::KorokBody() {}

KorokBody::~KorokBody() {}

void KorokBody::Display()
{
	res = 0.5 * M_PI;
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

		drawKorok();

		glPopAttrib();
	}
	glPopMatrix();
}

void KorokBody::Update(const double& deltaTime)
{

	aT = fmod(aT + deltaTime, 360.f);

	lArmRot = armDistance * sin(aT * armSpeed);
	rArmRot = armDistance * cos(aT * armSpeed);


}

void KorokBody::setArmSpeed(float _armSpeed)
{
	armSpeed = _armSpeed;
}

void KorokBody::drawKorok() 
{
	drawLegs();
	drawBody();
	drawArms();
	drawNose();
	drawHorns();
}

void KorokBody::drawLegs()
{
	glPushMatrix();
	{
		glTranslatef(-0.15f, 0.f, 0.f);
		glRotatef(180.f, 0.f, 0.f, 1.f);
		glScalef(0.15f, 0.15f, 0.15f);
		drawCone(res);
	};
	glPopMatrix();
	glPushMatrix();
	{
		glTranslatef(0.15f, 0.f, 0.f);
		glRotatef(180.f, 0.f, 0.f, 1.f);
		glScalef(0.15f, 0.15f, 0.15f);
		drawCone(res);
	};
	glPopMatrix();
}

void KorokBody::drawArms()
{
	glPushMatrix();
	{
		glTranslatef(-0.4f, 0.66f, 0.f);
		glRotatef(90.f + lArmRot, 0.f, 0.f, 1.f);
		glScalef(0.15f, 0.3f, 0.15f);
		drawCone(res);
	}
	glPopMatrix();
	glPushMatrix();
	{
		glTranslatef(0.4f, 0.66f, 0.f);
		glRotatef(-90.f + rArmRot, 0.f, 0.f, 1.f);
		glScalef(0.15f, 0.3f, 0.15f);
		drawCone(res);

	}
	glPopMatrix();
}

void KorokBody::drawNose()
{
	glPushMatrix();
	{
		glTranslatef(0.f, 1.2f, 0.4f);
		glRotatef(90.f, 1.f, 0.f, 0.f);
		glScalef(0.05f, 0.25f, 0.05f);
		drawCone(res);
	}
	glPopMatrix();
}

void KorokBody::drawHorns()
{
	glPushMatrix();
	{
		//glTranslatef(-0.25f, 2.1f, 0.0f);
		glTranslatef(0.25f, 1.5f, 0.0f);
		glRotatef(-33.f, 0.f, 0.f, 1.f);
		glPushMatrix();
		{
			glTranslatef(-0.04f, 0.4f, 0.f);
			glRotatef(100.f, 0.f, 0.f, 1.f);
			glScalef(0.02f, 0.1f, 0.02f);
			drawCone(res);
		}
		glPopMatrix();
		glScalef(0.15f, 0.6f, 0.2f);
		drawCone(res);
	}
	glPopMatrix();
	glPushMatrix();
	{
		//glTranslatef(-0.25f, 2.1f, 0.0f);
		glTranslatef(-0.25f, 1.5f, 0.0f);
		glRotatef(50.f, 0.f, 0.f, 1.f);
		glScalef(0.15f, 0.6f, 0.2f);
		drawCone(res);
	}
	glPopMatrix();
}

void KorokBody::drawBody()
{
	glPushMatrix();
	{
		glRotatef(180.f, 0.f, 0.f, 1.f);
		glScalef(0.3f, 0.01f, 0.3f);
		drawCone(res);
	}
	glPopMatrix();
	glPushMatrix();
	{
		glScalef(0.5f, 1.f, 0.5f);
		glPushMatrix();
		{
			glScalef(1.f, 0.1f, 1.f);
			drawFrustum(0.6f, 0.9f, res);
			//glTranslatef(0.f, -0.66f, 0.f);
			//drawSmoothFrustum(0.666f, 1.f, res);
		};
		glPopMatrix();

		glTranslatef(0.f, 0.1f, 0.f);
		glPushMatrix();
		{
			glScalef(1.f, 0.1f, 1.f);
			drawFrustum(0.9f, 1.f, res);
		};
		glPopMatrix();

		glTranslatef(0.f, 0.1f, 0.f);
		glPushMatrix();
		{
			glScalef(1.f, 0.2f, 1.f);
			drawFrustum(1.0f, 1.0f, res);
		};
		glPopMatrix();

		glTranslatef(0.f, 0.2f, 0.f);
		glPushMatrix();
		{
			glScalef(1.f, 0.5f, 1.f);
			drawFrustum(1.0f, 0.8f, res);
		};
		glPopMatrix();

		glTranslatef(0.f, 0.5f, 0.f);
		glPushMatrix();
		{
			glScalef(1.f, 0.2f, 1.f);
			drawFrustum(0.8f, 0.8f, res);
		};
		glPopMatrix();

		glTranslatef(0.f, 0.2f, 0.f);
		glPushMatrix();
		{
			glScalef(1.f, 0.4f, 1.f);
			drawFrustum(0.8f, 0.9f, res);
		};
		glPopMatrix();

		glTranslatef(0.f, 0.4f, 0.f);
		glPushMatrix();
		{
			glScalef(1.f, 0.1f, 1.f);
			drawFrustum(0.9f, 0.8f, res);
		};
		glPopMatrix();

		glTranslatef(0.f, 0.1f, 0.f);
		glPushMatrix();
		{
			glScalef(1.f, 0.05f, 1.f);
			drawFrustum(0.8f, 0.7f, res);
		};
		glPopMatrix();

		glTranslatef(0.f, 0.05f, 0.f);
		glPushMatrix();
		{
			glScalef(1.f, 0.05f, 1.f);
			drawFrustum(0.7f, 0.4f, res);
		};
		glPopMatrix();

	};
	glPopMatrix();
	glPushMatrix();
	{
		glTranslatef(0.f, 1.7f, 0.f);
		glScalef(0.2f, 0.01f, 0.2f);
		drawCone(res);
	}
	glPopMatrix();
	
}



