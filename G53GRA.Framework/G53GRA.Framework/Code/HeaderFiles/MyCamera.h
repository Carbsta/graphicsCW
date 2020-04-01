#pragma once

#include "../Utility/Camera.h"

class MyCamera : public Camera
{
public:
	MyCamera();
	virtual ~MyCamera() {};
	void HandleMouseDrag(int x, int y);
	void HandleKey(unsigned char key, int state, int mX, int mY);
	void Update(const double& deltaTime);
private:
	int wKey, aKey, sKey, dKey, qKey, eKey;
	int currentButton;
	GLint mouseX, mouseY;
};