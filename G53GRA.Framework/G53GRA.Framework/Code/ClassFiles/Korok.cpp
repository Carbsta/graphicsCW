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
	rotateSpeed = 1.f;
	rotateDistance = 10;
	headSpeed = 2.f;
	headDistance = 2;
	wandDistance = 1;
	wandSpeed = 2.f;
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
	rotateSpeed = 1.f;
	rotateDistance = 10;
	headSpeed = 2.f;
	headDistance = 2;
	wandDistance = 1;
	wandSpeed = 2.f;
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

void Korok::Update(const double& deltaTime)
{
	aT = fmod(aT + deltaTime, 360.f);
	float* or;
	float* po;

	switch (anim)
	{
	case Korok::Anim::Sway:
		or = this->orientation();
		this->orientation(or[0], or[1], rotateDistance * sin(aT * rotateSpeed + offset));
		mask->orientation(0.f, headDistance * sin(aT * headSpeed), headDistance * cos(aT * headSpeed + offset));
		wand->position(-0.7f, 0.7f + 0.05f * wandDistance * cos(aT * wandSpeed + offset), 0.f);

		break;
	case Korok::Anim::Jump:
		
		po = position();
		this->position(po[0], po[1] + 0.1f * jumpHeight * sin(aT * jumpSpeed + offset), po[2]);
		mask->position(0.f, 1.5f + 0.01f * headDistance * cos(aT * headSpeed + offset), 0.5f);
		mask->orientation(headDistance * sin(aT * headSpeed), 0.f, headDistance * cos(aT * headSpeed + offset));
		wand->position(-0.7f, 0.7f + 0.05f * wandDistance * sin(aT * wandSpeed + offset), 0.f);
		wand->orientation(2 * wandDistance * sin(aT * wandSpeed + offset), 0.f, 0.f);

		break;
	default:
		break;
	}

	body->Update(deltaTime);

}

void Korok::setAnim(Anim _anim)
{
	Anim oldAnim = anim;
	anim = _anim;
	if (anim == Anim::Jump && anim != oldAnim) {
		jumpSpeed = 10.f;
		headSpeed = 10.f;
		headDistance = 1;
		wandDistance = 1;
		wandSpeed = 10.f;
		this->position(pos[0], pos[1] + jumpHeight, pos[2]);
		body->setArmSpeed(10.f);
	}
	else if (anim == Anim::Sway && anim != oldAnim) {
		rotateSpeed = 1.f;
		rotateDistance = 10;
		headSpeed = 2.f;
		headDistance = 2;
		wandDistance = 1;
		wandSpeed = 2.f;
		this->position(pos[0], pos[1] - jumpHeight, pos[2]);
		body->setArmSpeed(2.f);
	}
}

void Korok::setOffset(float _offset)
{
	offset = _offset;
}
