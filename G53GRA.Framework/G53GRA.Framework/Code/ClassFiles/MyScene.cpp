#include "../HeaderFiles/MyScene.h"

MyScene::MyScene(int argc, char** argv, const char *title, const int& windowWidth, const int& windowHeight)
	: Scene(argc, argv, title, windowWidth, windowHeight)
{

}

void MyScene::Initialise()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	GLuint masktex = GetTexture("Textures/KorokMask1.bmp");
	DisplayableObject* mask = new KorokMask(masktex);
	mask->size(50);
	AddObjectToScene(mask);
	
}

void MyScene::Projection()
{
	GLdouble aspect = static_cast<GLdouble>(windowWidth) / static_cast<GLdouble>(windowHeight);
	gluPerspective(60.0, aspect, 1.0, 1000.0);
}

void MyScene::setGlobalLight()
{
    // Set lighting effect colours and positional parameter
    float ambient[] = { .2f, .2f, .2f, 1.f };      // ambient light (20% white)
    float diffuse[] = { .5f, .5f, .5f, 1.f };      // diffuse light (50% white)
    float specular[] = { 1.f, 1.f, 1.f, 1.f };      // specular light (100% white)
    float position[] = { 1.f, .5f, 1.f, 0.f };      // directional light (w = 0)
    // Attach properties to single light source (GL_LIGHT0)
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);      // set ambient parameter of light source
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);      // set diffuse parameter of light source
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular);    // set specular parameter of light source
    glLightfv(GL_LIGHT0, GL_POSITION, position);    // set direction vector of light source
    // Enable this lighting effects
    glEnable(GL_LIGHTING);  // enable scene lighting (required to enable a light source)
    glEnable(GL_LIGHT0);    // enable light source with attached parameters (GL_LIGHT0)    
}

void MyScene::Draw()
{
	// Clear colour and depth buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// Update based on window details (also sets initial projection properties)
	Reshape(windowWidth, windowHeight);
	// Reset MODELVIEW matrix
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	// Setup viewing properties
	camera.SetupCamera();

	//recalulate global lighting for static lights
	setGlobalLight();

	// Display all objects in the Scene
	for (DisplayableObject* obj : objects)
		obj->Display();

	// Zealous reset of MODELVIEW matrix
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	// Dump silent GL errors into console output
	CheckGLError();
}
