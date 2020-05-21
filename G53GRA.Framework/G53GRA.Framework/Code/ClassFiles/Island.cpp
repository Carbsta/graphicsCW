#include "../HeaderFiles/Island.h"

Island::Island()
{
	korok1 = new Korok();
	korok2 = new Korok();
	korok3 = new Korok();
	tree1 = new Tree();
	tree2 = new Tree();
	rock = new Rock();
	rock2 = new Rock();
	campfire = new Campfire();
	configure();
}

Island::Island(GLuint* _texids)
{
	korok1 = new Korok(_texids[0], _texids[1], _texids[2]);
	korok2 = new Korok(_texids[0], _texids[1], _texids[2]);
	korok3 = new Korok(_texids[0], _texids[1], _texids[2]);
	tree1 = new Tree(_texids[3], _texids[2]);
	tree2 = new Tree(_texids[3], _texids[2]);
	rock = new Rock(_texids[4]);
	rock2 = new Rock(_texids[4]);
	campfire = new Campfire(_texids[2], _texids[5]);
	sideTex = _texids[6];
	topTex = _texids[7];
	configure();
}

Island::~Island() 
{
	delete korok1;
	delete korok2;
	delete korok3;
	delete tree1;
	delete tree2;
	delete rock;
	delete rock2;
	delete campfire;
}

void Island::configure()
{
	korok1->size(20);
	korok1->position(-30.f, 4.f, 70.f);

	korok2->size(20.f, 30.f, 20.f);
	korok2->position(10.f, 38.f, 0.f);
	korok2->orientation(0.f, -20.f, 0.f);
	korok2->setAnim(Korok::Anim::Jump);

	korok3->size(20);
	korok3->position(0.f, 4.f, 100.f);
	korok3->orientation(0.f, -45.f, 0.f);
	korok3->setOffset(10.f);

	rock->position(10.f, 0.f, 0.f);
	rock->size(20);
	rock->orientation(30.f, 20.f, 0.f);
	rock->setShape(Rock::Shape::Large);

	rock2->position(-100.f, 0.f, 110.f);
	rock2->size(20);
	rock2->orientation(0.f, 75.f, 0.f);
	rock2->setShape(Rock::Shape::Large);

	campfire->position(-20.f, 4.f, 100.f);
	campfire->size(10);

	tree1->size(50);
	tree1->position(-50.f, 0.f, 50.f);

	tree2->size(40);
	tree2->position(150.f, 0.f, -50.f);
	tree2->setNumIter(2);
	tree2->setReplaceString('f', "ff-[-& f + ff + < + fl] + [+>f--f&-fl]");
}

void Island::Update(const double& deltaTime) {
	campfire->Update(deltaTime);
	korok1->Update(deltaTime);
	korok2->Update(deltaTime);
	korok3->Update(deltaTime);
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
	rock->Display();
	rock2->Display();
	campfire->Display();

	glPopAttrib();
	glPopMatrix();
	
}

void Island::drawIsland()
{
	glPushMatrix();
	
	glScalef(250.f, 250.f, 250.f);

	glPushMatrix();
	glScalef(1.f, 0.01f, 1.f);
	glTranslatef(0.f, 1.f, 0.f);
	glRotatef(180.f, 1.f, 0.f, 0.f);
	drawSmoothFrustum(0.01f, 1.f, 0.01f * M_PI, topTex);
	glPopMatrix();

	//glRotatef(180.f, 1.f, 0.f, 0.f);
	glTranslatef(0.f, -1.f, 0.f);
	drawSmoothFrustum(0.5f, 1.f, 0.01f * M_PI, sideTex);

	glPopMatrix();
}