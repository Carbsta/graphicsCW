#pragma once

#include "../Framework/Engine/Scene.h"
#include "../HeaderFiles/KorokMask.h"
#include "../HeaderFiles/KorokBody.h"

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
};