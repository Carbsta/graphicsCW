#include "Shapes.h"

void drawCone(float res, GLuint texid)
{
	float t = 0.f;
	float r = 1.f;
	float x = r * cos(t);
	float z = r * sin(t);
	bool toTexture = true;

	float p1[3];
	float p2[3];
	float p3[3];
	float n[3];

	if (texid == -1) toTexture = false;

	if (toTexture) {
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texid);
	}

	p1[0] = 0.f;
	p1[1] = 1.f;
	p1[2] = 0.f;

	do
	{
		glBegin(GL_TRIANGLES);
		p3[0] = x;
		p3[1] = 0.f;
		p3[2] = z;

		if (toTexture) glTexCoord2f(t / (2 * M_PI), 0.f);

		t += res;
		x = r * cos(t);
		z = r * sin(t);

		p2[0] = x;
		p2[1] = 0.f;
		p2[2] = z;

		surfaceNorm(p1, p2, p3, n);

		glNormal3fv(n);
		glVertex3fv(p1);

		if (toTexture) glTexCoord2f(t / (2 * M_PI), 1.f);
		glVertex3fv(p2);

		if (toTexture) glTexCoord2f(t / (2 * M_PI), 0.f);
		glVertex3fv(p3);

		glEnd();
	} while (t <= (2 * M_PI) + res);

	

	if (toTexture) glDisable(GL_TEXTURE_2D);
}

//void drawCone(float res, GLuint texid)
//{
//	drawCylinder(1.f, 0.f, res, texid);
//}

void drawFrustum(float lr, float ur, float res, GLuint texid)
{
	float t = 0.f;
	float ot = t;
	float lx = lr * cos(t);
	float lz = lr * sin(t);
	float ux = ur * cos(t);
	float uz = ur * sin(t);
	float count = 0.0;
	bool toTexture = true;

	float p1[3];
	float p2[3];
	float p3[3];
	float p4[3];
	float n[3];

	if (texid == -1) toTexture = false;

	if (toTexture) {
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texid);
	}

	

	do
	{
		glBegin(GL_QUADS);

		p1[0] = lx;
		p1[1] = 0.f;
		p1[2] = lz;

		p2[0] = ux;
		p2[1] = 1.f;
		p2[2] = uz;

		ot = t;
		t += res;
		lx = lr * cos(t);
		lz = lr * sin(t);
		ux = ur * cos(t);
		uz = ur * sin(t);

		p3[0] = ux;
		p3[1] = 1.f;
		p3[2] = uz;

		p4[0] = lx;
		p4[1] = 0.f;
		p4[2] = lz;

		surfaceNorm(p1, p2, p3, n);

		glNormal3fv(n);

		if (toTexture) glTexCoord2f(ot / (2 * M_PI), 0.f);
		glVertex3fv(p1);

		if (toTexture) glTexCoord2f(ot / (2 * M_PI), 1.f);
		glVertex3fv(p2);

		if (toTexture) glTexCoord2f(t / (2 * M_PI), 1.f);
		glVertex3fv(p3);

		if (toTexture) glTexCoord2f(t / (2 * M_PI), 0.f);
		glVertex3fv(p4);

		glEnd();

	} while (t <= (2 * M_PI) + res);

	if (toTexture) glDisable(GL_TEXTURE_2D);
}

//void drawFrustrum(float lr, float ur, float res, GLuint texid)
//{
//	float t = 0.f;
//	float lx = lr * cos(t);
//	float lz = lr * sin(t);
//	float ux = ur * cos(t);
//	float uz = ur * sin(t);
//	float count = 0.0;
//	bool toTexture = true;
//
//	if (texid == -1) toTexture = false;
//
//	if (toTexture) {
//		glEnable(GL_TEXTURE_2D);
//		glBindTexture(GL_TEXTURE_2D, texid);
//	}
//
//	glBegin(GL_TRIANGLE_STRIP);
//
//	if (toTexture) glTexCoord2f(t / (2 * M_PI), 0.f);
//	glNormal3f(lx, 0.f, lz);
//	glVertex3f(lx, 0.f, lz);
//
//	do
//	{
//		t += res;
//		lx = lr * cos(t);
//		lz = lr * sin(t);
//		ux = ur * cos(t);
//		uz = ur * sin(t);
//
//		if (toTexture) glTexCoord2f(t / (2 * M_PI), 1.f);
//		glNormal3f(ux, 0.f, uz);
//		glVertex3f(ux, 1.f, uz);
//
//		if (toTexture) glTexCoord2f(t / (2 * M_PI), 0.f);
//		glNormal3f(lx, 0.f, lz);
//		glVertex3f(lx, 0.f, lz);
//
//	} while (t <= (2 * M_PI) + res);
//
//	glEnd();
//
//	if (toTexture) glDisable(GL_TEXTURE_2D);
//}

void drawSquareFrustum(float ls, float us, GLuint texid)
{
	float r = 1.0f;
	float ru = r * us;
	float rl = r * ls;
	float p1[3];
	float p2[3];
	float p3[3];
	float n[3];

	glBegin(GL_TRIANGLES);

	// front face
	// only need to calculate face normal for one of the two tris
	p1[0] = p1[2] = rl;
	p1[1] = -rl;
	p2[0] = p2[1] = p2[2] = p3[1] = p3[2] = ru;
	p3[0] = -ru;

	surfaceNorm(p1, p2, p3, n);

	glNormal3f(n[0], n[1], n[2]);

	glVertex3f(rl, -rl, rl);  // 3
	glVertex3f(ru, ru, ru);   // 2
	glVertex3f(-ru, ru, ru);  // 1

	glVertex3f(rl, -rl, rl);  // 3
	glVertex3f(-ru, ru, ru);  // 1
	glVertex3f(-rl, -rl, rl); // 0

	// back face
	p1[0] = p1[1] = p1[2] = -rl;
	p2[0] = p2[2] = p3[2] = -ru;
	p2[1] = p3[0] = p3[1] = ru;
	surfaceNorm(p1, p2, p3, n);

	glNormal3f(n[0], n[1], n[2]);

	glVertex3f(-rl, -rl, -rl); // 7
	glVertex3f(-ru, ru, -ru);  // 6
	glVertex3f(ru, ru, -ru);   // 5

	glVertex3f(-rl, -rl, -rl); // 7
	glVertex3f(ru, ru, -ru);   // 5
	glVertex3f(rl, -rl, -rl);  // 4

	//top face
	// not at angle so no calculation required
	glNormal3f(0, 1, 0);

	glVertex3f(-ru, ru, ru);   // 1
	glVertex3f(ru, ru, ru);    // 2
	glVertex3f(ru, ru, -ru);   // 5

	glVertex3f(-ru, ru, ru);   // 1
	glVertex3f(ru, ru, -ru);   // 5
	glVertex3f(-ru, ru, -ru);  // 6

	//bottom face
	glNormal3f(0, -1, 0);

	glVertex3f(-rl, -rl, -rl); // 7
	glVertex3f(rl, -rl, -rl);  // 4
	glVertex3f(rl, -rl, rl);   // 3

	glVertex3f(-rl, -rl, -rl); // 7
	glVertex3f(rl, -rl, rl);   // 3
	glVertex3f(-rl, -rl, rl);  // 0

	//left face
	p1[0] = p1[1] = p1[2] = p2[0] = p2[1] = -rl;
	p2[2] = rl;
	p3[0] = -ru;
	p3[1] = p3[2] = ru;

	surfaceNorm(p1, p2, p3, n);

	glNormal3f(n[0], n[1], n[2]);

	glVertex3f(-rl, -rl, -rl); // 7
	glVertex3f(-rl, -rl, rl);  // 0
	glVertex3f(-ru, ru, ru);   // 1

	glVertex3f(-rl, -rl, -rl); // 7
	glVertex3f(-ru, ru, ru);   // 1
	glVertex3f(-ru, ru, -ru);  // 6

	//right face
	p1[0] = p1[2] = p2[0] = rl;
	p2[1] = p2[2] = -rl;
	p3[0] = p3[1] = ru;
	p3[2] = -ru;

	surfaceNorm(p1, p2, p3, n);

	glNormal3f(n[0], n[1], n[2]);

	glVertex3f(rl, -rl, rl);   // 3
	glVertex3f(rl, -rl, -rl);  // 4
	glVertex3f(ru, ru, -ru);   // 5

	glVertex3f(rl, -rl, rl);   // 3
	glVertex3f(ru, ru, -ru);   // 5
	glVertex3f(ru, ru, ru);    // 2

	glEnd();
}

void surfaceNorm(const float* p1, const float* p2, const float* p3, float* n)
{
	float u[3];
	u[0] = p2[0];
	u[1] = p2[1];
	u[2] = p2[2];
	float v[3];
	v[0] = p3[0];
	v[1] = p3[1];
	v[2] = p3[2];

	sub(u, p1);
	sub(v, p1);

	cross(u, v, n);
}