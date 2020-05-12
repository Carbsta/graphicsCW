#include "../HeaderFiles/Island.h"

Island::Island()
{
	korok1 = new Korok();
	korok2 = new Korok();
	korok3 = new Korok();
	tree1 = new Tree();
	tree2 = new Tree();
	configure();
}

Island::Island(GLuint* _texids)
{
	korok1 = new Korok(_texids[0], _texids[1], _texids[2]);
	korok2 = new Korok(_texids[0], _texids[1], _texids[2]);
	korok3 = new Korok(_texids[0], _texids[1], _texids[2]);
	tree1 = new Tree(_texids[3], _texids[2]);
	tree2 = new Tree(_texids[3], _texids[2]);
	configure();
}

Island::~Island() 
{
	delete korok1;
	delete korok2;
	delete korok3;
	delete tree1;
	delete tree2;
}

void Island::configure()
{
	korok1->size(20);
	korok1->position(0.f, 4.f, 0.f);
	korok2->size(20.f, 30.f, 20.f);
	korok2->position(100.f, 4.f, 0.f);
	korok3->size(20);
	korok3->position(50.f, 4.f, 100.f);
	tree1->size(50);
	tree1->position(-50.f, 0.f, 50.f);
	tree2->size(40);
	tree2->position(150.f, 0.f, -50.f);
	tree2->setNumIter(2);
	tree2->setReplaceString('f', "ff-[-& f + ff + < + fl] + [+>f--f&-fl]");
}

void Island::Display()
{
	glPushMatrix();
	glPushAttrib(GL_ALL_ATTRIB_BITS);

	// Position objects in world space
	glTranslatef(pos[0], pos[1], pos[2]);               // Position
	glScalef(scale[0], scale[1], scale[2]);             // Scale
	glRotatef(rotation[1], 0.f, 1.f, 0.f);              // Set orientation (Y)
	glRotatef(rotation[2], 0.f, 0.f, 1.f);              // Set orientation (Z)
	glRotatef(rotation[0], 1.f, 0.f, 0.f);              // Set orientation (X)

	drawIsland();
	korok1->Display();
	korok2->Display();
	korok3->Display();
	tree1->Display();
	tree2->Display();

	glPopAttrib();
	glPopMatrix();
	
}

void Island::drawIsland()
{
	glPushMatrix();
	
	glScalef(250.f, 250.f, 250.f);

	glPushMatrix();
	glScalef(1.f, 0.01f, 1.f);
	drawCone(0.1f * M_PI);
	glPopMatrix();

	glRotatef(180.f, 1.f, 0.f, 0.f);
	drawFrustum(1.f, 0.5f, 0.1f * M_PI);

	glPopMatrix();
}