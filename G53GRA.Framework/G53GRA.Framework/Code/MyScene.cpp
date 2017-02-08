#include "MyScene.h"

#include "Planet.h"
#include "Planet2.h"

MyScene::MyScene(int argc, char** argv, const char *title, const int& windowWidth, const int& windowHeight)
	: Scene(argc, argv, title, windowWidth, windowHeight)
{
	// DEMO 3 (Demos/Solar System)
	// create and add a new triangle to the scene
	Planet *sun = new Planet(30.0, 0.0f, 12.0f, 0.0f);
	sun->SetColour(255, 255, 0); //yellow

	Planet *mars = new Planet(6.0, 60.0f, 150.0f, 50.0f);
	mars->SetColour(255, 0, 0); //red

	Planet2 *earth = new Planet2(15.0, 135.0f, 100.0f, 20.0f, 6.0f, 30.0, 100.0f, 8.0f);
	earth->SetColour(0, 0, 255); //earth blue, moon grey

	AddObjectToScene(sun);
	AddObjectToScene(mars);
	AddObjectToScene(earth);
}

void MyScene::Initialise()
{
	glClearColor(static_cast<GLclampf>(0.0f), static_cast<GLclampf>(0.0f), static_cast<GLclampf>(0.0f), static_cast<GLclampf>(1.0f));

}

void MyScene::Projection()
{
	gluPerspective(static_cast<GLdouble>(60.0), static_cast<GLdouble>(windowWidth) / static_cast<GLdouble>(windowHeight),
				   static_cast<GLdouble>(1.0), static_cast<GLdouble>(1000.0));
}
