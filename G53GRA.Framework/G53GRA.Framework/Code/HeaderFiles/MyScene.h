#pragma once

#define _USE_MATH_DEFINES
#include "../Framework/Engine/Scene.h"
#include "../HeaderFiles/Island.h"
#include "../HeaderFiles/Stage.h"
#include "../Shared/Shapes.h"

class MyScene :
	public Scene
{
public:
	MyScene(int argc, char** argv, const char *title, const int& windowWidth, const int& windowHeight);
	~MyScene() {};

private:
	void Initialise();
	void Projection();
	void setGlobalLight();
	void Draw();
	void Reshape(int w, int h);
	Stage* stage;
};