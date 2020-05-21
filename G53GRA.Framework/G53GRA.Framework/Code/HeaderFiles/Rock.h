#pragma once
#include "DisplayableObject.h"
#include "../Shared/Shapes.h"
class Rock :
	public DisplayableObject
{
public:
	Rock();
	Rock(GLuint _texid);
	~Rock() {};
	void Display();
	enum class Shape { Single, Large };
	void setShape(Shape s);
private:
	Shape shape = Shape::Single;
	void drawSingle();
	void drawLarge();
	GLuint texid = -1;
	bool toTexture = false;
};

