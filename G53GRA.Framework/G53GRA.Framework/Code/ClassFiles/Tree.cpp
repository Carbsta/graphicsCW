#include "../HeaderFiles/Tree.h"

Tree::Tree() {}

Tree::Tree(GLuint _leafid, GLuint _barkid)
{
	leaf = _leafid;
	if (leaf != -1) toLeaf = true;
	bark = _barkid;
	if (bark != -1) toBark = true;
}

Tree::~Tree() {}

void Tree::Display()
{
	glPushMatrix();

	// Project from Object Space to World Space
	glTranslatef(pos[0], pos[1], pos[2]);   // position
	glScalef(scale[0], scale[1], scale[2]); // scale
	glRotatef(rotation[1], 0.f, 1.f, 0.f);  // set orientation (Y)
	glRotatef(rotation[2], 0.f, 0.f, 1.f);  // set orientation (Z)
	glRotatef(rotation[0], 1.f, 0.f, 0.f);  // set orientation (X)

	char curr;

	for (unsigned int i = 0; i < sequence.size(); i++)
	{
		curr = sequence[i];             // for each char in sequence
		switch (curr) {                  // check current char command
		case 'f':                   // draw branch, move forward
			branch();
			break;
		case 'l':
			leaves();
			break;
		case '+':                   // yaw clockwise
			glRotatef(-angle, 0.f, 0.f, 1.f);
			break;
		case '-':                   // yaw counter-clockwise
			glRotatef(angle, 0.f, 0.f, 1.f);
			break;
		case '^':                   // pitch clockwise
			glRotatef(-angle, 1.f, 0.f, 0.f);
			break;
		case '&':                   // pitch counter-clockwise
			glRotatef(angle, 1.f, 0.f, 0.f);
			break;
		case '<':                   // roll clockwise
			glRotatef(-angle, 0.f, 1.f, 0.f);
			break;
		case '>':                   //roll counter-clockwise
			glRotatef(angle, 0.f, 1.f, 0.f);
			break;
		case '|':                   // roll upside-down
			glRotatef(180.f, 0.f, 1.f, 0.f);
			break;
		case '[': // "Save"
			glPushMatrix();
			break;
		case ']': // "Restore"
			glPopMatrix();
			break;
		}
	}

	glPopMatrix();
}

void Tree::addReplaceString(char flag, string str)
{
	flags.push_back(flag);                          // Add char to flags
	change.push_back(str);                          // Add string to change
	getSequence();                                  // Recompute sequence
}

void Tree::setReplaceString(char flag, string str)
{
	flags.erase(flags.begin(), flags.end());        // Empty flags
	change.erase(change.begin(), change.end());     // Empty change
	flags.push_back(flag);                          // Add char to flags
	change.push_back(str);                          // Add string to change
	getSequence();                                  // Recompute sequence
}

void Tree::setNumIter(unsigned int num)
{
	iter = num;
}

void Tree::setInitString(string str)
{
	init = str;
}

void Tree::getSequence()
{
	int gen = 0, j = 0;
	string next;
	bool changed;
	sequence = init;
	char curr;
	while (gen < iter) {                     // Iterative scheme
		next = "";                          // Start with blank
		for (unsigned int i = 0; i < sequence.size(); i++) {
			curr = sequence[i];             // For each letter in the sequence
			changed = false;
			j = 0;
			for (vector<char>::iterator it = flags.begin(); it != flags.end(); ++it, j++) {
				if (curr == *it) {           // Iterate through vector of 'flags'
					next += change[j];      // Replace flag with corresponding change string
					changed = true;
					break;
				}
			}
			if (!changed)                   // If current char does not match a flag
				next += curr;               // ... add it to sequence string
		}
		sequence = next;                    // Update sequence string
		gen++;                              // Recurse
	}
}

void Tree::branch()
{

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

	glScalef(0.9f, 0.9f, 0.9f);

	/*float lr = 0.15f;
	float ur = 0.135f;
	float t = 0.f;
	float lx = lr * cos(t);
	float lz = lr * sin(t);
	float ux = ur * cos(t);
	float uz = ur * sin(t);
	float count = 0.0;
	float res = 0.1 * M_PI;

	if (toBark)
	{
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, bark);

	}

	glBegin(GL_TRIANGLE_STRIP);

	if (toBark) glTexCoord2f(t / (2 * M_PI), 0.f);
	glNormal3f(lx, 0.f, lz);
	glVertex3f(lx, 0.f, lz);

	do
	{
		t += res;
		lx = lr * cos(t);
		lz = lr * sin(t);
		ux = ur * cos(t);
		uz = ur * sin(t);

		if (toBark) glTexCoord2f(t / (2 * M_PI), 1.f);
		glNormal3f(ux, 0.f, uz);
		glVertex3f(ux, 1.f, uz);

		if (toBark) glTexCoord2f(t / (2 * M_PI), 0.f);
		glNormal3f(lx, 0.f, lz);
		glVertex3f(lx, 0.f, lz);

	} while (t <= (2 * M_PI) + res);

	glEnd();*/
	drawFrustum(0.15f, 0.135f, 0.1 * M_PI, bark);

	glTranslatef(0.f, 1.f, 0.f);            // translate to top of branch

	// Projection plane
	GLfloat splane[] = { 1.0f, 0.0f, 0.0f, 0.0f };
	GLfloat tplane[] = { 0.0f, 1.0f, 0.0f, 0.0f };
	if (toBark) {
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, bark);
		glEnable(GL_TEXTURE_GEN_S);
		glEnable(GL_TEXTURE_GEN_T);
		glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
		glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
		glTexGenfv(GL_S, GL_OBJECT_PLANE, splane);
		glTexGenfv(GL_T, GL_OBJECT_PLANE, tplane);
	}

	glutSolidSphere(0.135f, 10, 10);

	if (toBark) {
		glDisable(GL_TEXTURE_GEN_S);
		glDisable(GL_TEXTURE_GEN_T);
	}
	
	//glPopAttrib();

	if (toBark) glDisable(GL_TEXTURE_2D); // disable texturing again

	glPopAttrib();
}

void Tree::leaves()
{
	glPushAttrib(GL_ALL_ATTRIB_BITS);

	glScalef(3.f, 3.f, 3.f);
	glPushMatrix();
	if (toLeaf)
	{
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, leaf);
	}

	glBegin(GL_QUADS);
	glNormal3f(0.f, 0.f, 1.f);

	if (toLeaf) glTexCoord2f(0.f, 0.f);
	glVertex3f(-1.f, -1.f, 0.f);

	if (toLeaf) glTexCoord2f(1.f, 0.f);
	glVertex3f(1.f, -1.f, 0.f);

	if (toLeaf) glTexCoord2f(1.f, 1.f);
	glVertex3f(1.f, 1.f, 0.f);

	if (toLeaf) glTexCoord2f(0.f, 1.f);
	glVertex3f(-1.f, 1.f, 0.f);

	glEnd();

	glRotatef(180.f, 0.f, 1.0f, 0.f);

	glBegin(GL_QUADS);
	glNormal3f(0.f, 0.f, 1.f);

	if (toLeaf) glTexCoord2f(0.f, 0.f);
	glVertex3f(-1.f, -1.f, 0.f);

	if (toLeaf) glTexCoord2f(1.f, 0.f);
	glVertex3f(1.f, -1.f, 0.f);

	if (toLeaf) glTexCoord2f(1.f, 1.f);
	glVertex3f(1.f, 1.f, 0.f);

	if (toLeaf) glTexCoord2f(0.f, 1.f);
	glVertex3f(-1.f, 1.f, 0.f);

	glEnd();

	if (toLeaf) glDisable(GL_TEXTURE_2D);

	glPopMatrix();
	glPopAttrib();
}