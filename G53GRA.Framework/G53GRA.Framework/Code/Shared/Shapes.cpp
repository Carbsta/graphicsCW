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

void drawSmoothFrustum(float lr, float ur, GLuint texid)
{
	float t = 0.f;
	float lx = lr * cos(t);
	float lz = lr * sin(t);
	float ux = ur * cos(t);
	float uz = ur * sin(t);
	float count = 0.0;
	bool toTexture = true;

	const float res = 0.1f * M_PI;
	const int faceNumber = (2 * M_PI) / 0.1f * M_PI;

	GLfloat v[faceNumber * 2 * 3] = {0.f}; //twice as many vertexes as faces, assuming vertexes are shared
	GLfloat n[faceNumber * 2 * 3] = { 0.f }; //as many normals as vertexes for smooth shading
	GLfloat tex[faceNumber * 2 * 2] = { 0.f }; // each vertex needs an s and t coordinate
	GLubyte i[faceNumber * 4] = { 0 }; //each quad needs four vertexes

	/* set the index values, this defines which vertex belongs to each face
	i[] = {0 1 2 3
	       3 2 4 5
		   5 4 6 7
		   7 6 8 9
		   ... 1 0}*/
	i[0] = 0;
	i[1] = 1;
	i[2] = 2;
	i[3] = 3;

	int v0 = 3;
	int v1 = 2;
	int v2 = 4;
	int v3 = 5;
	for (int f = 1; f < faceNumber; f++) {
		i[f * 4] = v0;
		i[(f * 4) + 1] = v1;
		i[(f * 4) + 2] = v2;
		i[(f * 4) + 3] = v3;
		v0 = v0 + 2;
		v1 = v1 + 2;
		v2 = v2 + 2;
		v3 = v3 + 2;
	}
	// correct the last vertex pair
	i[(faceNumber * 4) - 2] = 1;
	i[(faceNumber * 4) - 1] = 0;

	// Define the first two vertexes in the quad strip
	v[0] = lx;
	v[1] = 0.f;
	v[2] = lz;

	v[3] = ux;
	v[4] = 1.f;
	v[5] = uz;

	tex[0] = tex[2] = t / (2 * M_PI);
	tex[1] = 0.f;
	tex[3] = 1.f;

	int index = 2;
	int itex = 4;
	do // loop for the rest of the vertexes, two at a time, plus normals
	{
		t += res;
		lx = lr * cos(t);
		lz = lr * sin(t);
		ux = ur * cos(t);
		uz = ur * sin(t);

		v[i[index] * 3] = ux;
		v[(i[index] * 3) + 1] = 1.f;
		v[(i[index] * 3) + 2] = uz;

		tex[itex] = t / (2 * M_PI);
		tex[itex + 1] = 1.f;

		index++;
		itex = itex + 2;

		v[i[index] * 3] = lx;
		v[(i[index] * 3) + 1] = 0.f;
		v[(i[index] * 3) + 2] = lz;

		tex[itex] = t / (2 * M_PI);
		tex[itex + 1] = 0.f;

		index++;
		itex = itex + 2;

		// update normals
		float fn[3] = { 0.f };
		// face normal of the current face - using one triangle
		surfaceNorm(&v[i[index - 1] * 3], &v[i[index - 2] * 3], &v[i[index-3] * 3], fn);

		//add this to each vertex normal in the current face
		add(&n[i[index - 3] * 3], fn);
		add(&n[i[index - 2] * 3], fn);
		add(&n[i[index - 1] * 3], fn);
		add(&n[i[index] * 3], fn);
		// automatic normalisation is enabled so don't need to worry about normalising them.

		

	} while (t <= (2 * M_PI) + res);

	// enable and specify pointers to vertex arrays
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);

	glNormalPointer(GL_FLOAT, 0, n);
	glVertexPointer(3, GL_FLOAT, 0, v);

	if (toTexture) {
		glEnable(GL_TEXTURE_2D);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glTexCoordPointer(2, GL_FLOAT, 0, tex);
		glBindTexture(GL_TEXTURE_2D, texid);
	}
	
	//glDrawElements(GL_QUAD_STRIP, faceNumber * 2, GL_UNSIGNED_BYTE, i);
	glDrawArrays(GL_QUAD_STRIP, 0, faceNumber * 2);

	if (toTexture) {
		glDisable(GL_TEXTURE_2D);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	}

	glDisableClientState(GL_VERTEX_ARRAY);  // disable vertex arrays
	glDisableClientState(GL_NORMAL_ARRAY);
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
	norm(n);
}