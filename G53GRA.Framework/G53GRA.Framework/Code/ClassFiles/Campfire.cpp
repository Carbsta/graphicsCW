#include "../HeaderFiles/Campfire.h"

Campfire::Campfire()
{
}

Campfire::Campfire(GLuint _logTex, GLuint _flameSheet)
{
		logTex = _logTex;
		if (logTex != -1) toTexLog = true;
		flameSheet = _flameSheet;
		if (flameSheet != -1) animateFlame = true;
}

void Campfire::Display()
{
	glPushMatrix();

	// Project from Object Space to World Space
	glTranslatef(pos[0], pos[1], pos[2]);   // position
	glScalef(scale[0], scale[1], scale[2]); // scale
	glRotatef(rotation[1], 0.f, 1.f, 0.f);  // set orientation (Y)
	glRotatef(rotation[2], 0.f, 0.f, 1.f);  // set orientation (Z)
	glRotatef(rotation[0], 1.f, 0.f, 0.f);  // set orientation (X)

	glPushMatrix();
	glTranslatef(-1.f, -0.1f, 0.f);
	glScalef(1.f, 0.1f, 1.f);
	glutSolidSphere(1.f, 12, 12);
	glPopMatrix();

	drawLog();
	drawFlame();
	glRotatef(90.f, 0.f, 1.f, 0.f);
	glPushMatrix();
		glTranslatef(1.f, 0.f, -1.f);
		drawLog();
		drawFlame();
	glPopMatrix();
	glRotatef(90.f, 0.f, 1.f, 0.f);
	glPushMatrix();
		glTranslatef(2.f, 0.f, 0.f);
		drawFlame();
	glPopMatrix();
	glRotatef(90.f, 0.f, 1.f, 0.f);
	glPushMatrix();
		glTranslatef(1.f, 0.f, 1.f);
		drawFlame();
	glPopMatrix();


	glPopMatrix();
}

void Campfire::Update(const double& deltaTime)
{
	aT = fmod(aT + deltaTime, animationTime);
	flickerTimer = fmod(flickerTimer + deltaTime + (1/(rand()%100 + 1)), 2.f);

	spreadFrame = floor(spreadWidth * aT / animationTime);
	
	texCoords[0] = spreadFrame / spreadWidth;
	texCoords[1] = 0;
	texCoords[2] = (spreadFrame + 1) / spreadWidth;
	texCoords[3] = 0;
	texCoords[4] = (spreadFrame + 1) / spreadWidth;
	texCoords[5] = 1;
	texCoords[6] = spreadFrame / spreadWidth;
	texCoords[7] = 1;


	glPushMatrix();

	glTranslatef(pos[0], pos[1], pos[2]);               // Position
	glScalef(scale[0], scale[1], scale[2]);             // Scale
	glRotatef(rotation[1], 0.f, 1.f, 0.f);              // Set orientation (Y)
	glRotatef(rotation[2], 0.f, 0.f, 1.f);              // Set orientation (Z)
	glRotatef(rotation[0], 1.f, 0.f, 0.f);              // Set orientation (X)

	glEnable(GL_LIGHTING);

	glLightfv(GL_LIGHT1, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT1, GL_SPECULAR, specular);

	glLightfv(GL_LIGHT1, GL_POSITION, lposition);

	glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 1.f);
	glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 0.1f);
	glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 0.f);

	if (flickerTimer <= 1.4f) {
		glEnable(GL_LIGHT1);
		flicker = false;
	}
	else {
		glDisable(GL_LIGHT1);
		flicker = true;
	}
	

	glPopMatrix();
}

void Campfire::drawLog()
{
	glPushMatrix();

	glRotatef(90.f, 0.f, 0.f, 1.f);
	glScalef(0.1f, 2.f, 0.1f);
	drawFrustum(1.f, 1.f, 0.2 * M_PI, logTex);

	glPopMatrix();
}

void Campfire::drawFlame()
{
	if (!flicker) {
		glPushMatrix();
		glPushAttrib(GL_ALL_ATTRIB_BITS);

		glDisable(GL_LIGHTING);
		glColor4f(1.f, 1.f, 1.f, 1.f); // fill is invisible, only texture rendered.

		glTranslatef(-1.f, 0.f, 0.f);

		if (animateFlame) {
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, flameSheet);
		}

		glBegin(GL_QUADS);

		glNormal3f(0.f, 0.f, 1.f);

		if (animateFlame) glTexCoord2f(texCoords[0], texCoords[1]);
		glVertex3f(-1.f, 0.f, 0.f);

		if (animateFlame) glTexCoord2f(texCoords[2], texCoords[3]);
		glVertex3f(1.f, 0.f, 0.f);

		if (animateFlame) glTexCoord2f(texCoords[4], texCoords[5]);
		glVertex3f(1.f, 2.f, 0.f);

		if (animateFlame) glTexCoord2f(texCoords[6], texCoords[7]);
		glVertex3f(-1.f, 2.f, 0.f);

		glEnd();

		if (animateFlame) glDisable(GL_TEXTURE_2D);

		glEnable(GL_LIGHTING);
		glPopAttrib();
		glPopMatrix();
	}
}