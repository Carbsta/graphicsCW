#include "../HeaderFiles/MyCamera.h"
#include "VectorMath.h"

MyCamera::MyCamera() : wKey(0), sKey(0), aKey(0), dKey(0), qKey(0), eKey(0), currentButton(0), mouseX(0), mouseY(0)
{
	Reset();
}

void MyCamera::Update(const double& deltaTime)
{
	float speed = 100.0f;

	if (aKey)
		sub(eyePosition, right, speed * deltaTime);

	if (dKey)
		add(eyePosition, right, speed * deltaTime);

	if (wKey)
		add(eyePosition, forward, speed * deltaTime);

	if (sKey)
		sub(eyePosition, forward, speed * deltaTime);

	if (eKey)
		add(eyePosition, up, speed * deltaTime);

	if (qKey)
		sub(eyePosition, up, speed * deltaTime);

	SetupCamera();
}

void MyCamera::HandleMouseDrag(int x, int y)
{
	float rx, ry;
	float sensitivity = 0.01f; // speed of the camera moving

	// work out the difference between where the mouse was last used (mouseX, mouseY) to
	// position the view direction and the current position (x, y) the mouse is in
	rx = static_cast<float>(x - mouseX);
	ry = static_cast<float>(y - mouseY);

	// switch on which button was pressed and only do the update if the left button was pressed
	switch (currentButton)
	{
	case GLUT_LEFT_BUTTON:

		// add on the amount of change in to the left and right view direction of the camera
		if (rx > 0)
			add(vd, right, rx * sensitivity);
		else
			sub(vd, right, rx * -sensitivity);
		// add on the amount of change in to the up and down view direction of the camera
		if (ry > 0)
			sub(vd, up, ry * sensitivity);
		else
			add(vd, up, ry * -sensitivity);

		// normalise the view direction so it is length 1
		norm(vd);

		// use the view direction crossed with the up vector to obtain the corrected right vector
		cross(vd, up, right);

		// normalise the right vector
		norm(right);

		/* update forward with view direction, can move along all three axis */

		forward[0] = vd[0];
		forward[1] = vd[1];
		forward[2] = vd[2];
		norm(forward);
		break;
	case GLUT_RIGHT_BUTTON:
		break;
	case GLUT_MIDDLE_BUTTON:
		break;
	default:
		break;
	}

	mouseX = x;
	mouseY = y;
}

void MyCamera::HandleKey(unsigned char key, int state, int mX, int mY)
{
	switch (key)
	{
	case 'A':
	case 'a':
		aKey = state;
		break;
	case 'D':
	case 'd':
		dKey = state;
		break;
	case 'W':
	case 'w':
		wKey = state;
		break;
	case 'S':
	case 's':
		sKey = state;
		break;
	case 'Q':
	case 'q':
		qKey = state;
		break;
	case 'E':
	case 'e':
		eKey = state;
		break;
	case ' ':
		Reset();
	default:
		break;
	}
}