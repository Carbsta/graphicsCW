#include "../HeaderFiles/Korok.h"

Korok::Korok()
{
	wand = new KorokWand();
	wand->position(-0.7f, 0.7f, 0.f);
	wand->orientation(0.f, 0.f, 20.f);
	mask = new KorokMask();
	mask->position(0.f, 1.5f, 0.5f);
	mask->size(0.7);
	body = new KorokBody();
}

Korok::Korok(GLuint mt, GLuint mbt, GLuint wt)
{
	wand = new KorokWand(wt);
	wand->position(-0.7f, 0.7f, 0.f);
	wand->orientation(0.f, 0.f, 20.f);
	mask = new KorokMask(mt, mbt);
	mask->position(0.f, 1.5f, 0.5f);
	mask->size(0.7);
	body = new KorokBody();
}

Korok::Korok(KorokWand* w, KorokMask* m, KorokBody* b) : wand{ w }, mask{ m }, body{ b } {}

Korok::~Korok() {
	wand->~KorokWand();
	mask->~KorokMask();
	body->~KorokBody();
}

void Korok::Display()
{
	glPushMatrix();
	{

		// Project from Object Space to World Space
		glTranslatef(pos[0], pos[1], pos[2]);               // Position
		glScalef(scale[0], scale[1], scale[2]);             // Scale
		glRotatef(rotation[1], 0.f, 1.f, 0.f);              // Set orientation (Y)
		glRotatef(rotation[2], 0.f, 0.f, 1.f);              // Set orientation (Z)
		glRotatef(rotation[0], 1.f, 0.f, 0.f);              // Set orientation (X)

		body->Display();
		mask->Display();
		wand->Display();

	}
	glPopMatrix();
}