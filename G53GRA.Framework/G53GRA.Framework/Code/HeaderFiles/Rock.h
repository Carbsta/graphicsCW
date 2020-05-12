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
	enum class Shape { Single, Large };
private:
	Shape shape = Shape::Single;
	void drawSingle();
	void drawLarge();
	GLuint texid;
	bool toTexture = false;
};

