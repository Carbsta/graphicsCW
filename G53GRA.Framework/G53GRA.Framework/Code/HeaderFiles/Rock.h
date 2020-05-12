#pragma once
#include "DisplayableObject.h"
class Rock :
	public DisplayableObject
{
public:
	Rock();
	Rock(GLuint _texid);
	~Rock() {};
	void Display();
private:
	GLuint texid;
	bool toTexture = false;
};

