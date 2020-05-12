#include "../HeaderFiles/MyScene.h"

Texture Scene::texture = Texture();		// Initialise Texture handler
Camera Scene::camera = Camera();        // Initialise Camera object

MyScene::MyScene(int argc, char** argv, const char *title, const int& windowWidth, const int& windowHeight)
	: Scene(argc, argv, title, windowWidth, windowHeight)
{

}

void MyScene::Initialise()
{

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	GLuint* textures = new GLuint[4];
	textures[0] = GetTexture("Textures/KorokMask1.bmp");
	textures[1] = GetTexture("Textures/KorokMask1Back.bmp");
	textures[2] = GetTexture("Textures/Bark.bmp");
	textures[3] = GetTexture("Textures/Leaves.bmp");
	Island* island = new Island(textures);
	AddObjectToScene(island);

	//GLuint fronttex = GetTexture("Textures/KorokMask1.bmp");
	//GLuint backtex = GetTexture("Textures/KorokMask1Back.bmp");
	//GLuint barktex = GetTexture("Textures/Bark.bmp");

	//DisplayableObject* ko = new Korok(fronttex, backtex, barktex);
	//ko->size(20);
	//AddObjectToScene(ko);

	//DisplayableObject* ko2 = new Korok(fronttex, backtex, barktex);
	//ko2->size(20.f, 30.f, 20.f);
	//ko2->position(100.f, 0.f, 0.f);
	//AddObjectToScene(ko2);

	//GLuint leaftex = GetTexture("Textures/Leaves.bmp");
	//Tree* test = new Tree(leaftex, barktex);
	//test->size(50);
	//test->position(-50.f, 0.f, 50.f);
	//test->setNumIter(2);
	////test->setReplaceString('f', "ff-[-& f + ff + < + fl] + [+>f--f&-fl]");
	//AddObjectToScene(test);
	
	stage = new Stage();
	GLuint* skybox = new GLuint[6];
	skybox[0] = GetTexture("Textures/skybox_left.bmp");
	skybox[1] = GetTexture("Textures/skybox_right.bmp");
	skybox[2] = GetTexture("Textures/skybox_front.bmp");
	skybox[3] = GetTexture("Textures/skybox_back.bmp");
	skybox[4] = GetTexture("Textures/skybox_down.bmp");
	skybox[5] = GetTexture("Textures/skybox_up.bmp");
	stage->setTextures(skybox);
	AddObjectToScene(stage);

	//DisplayableObject* mask = new KorokMask(masktex);
	//mask->position(-18.f, 55.f, 25.f);
	//mask->size(20);
	//AddObjectToScene(mask);
	
}

void MyScene::Projection()
{
	//GLdouble aspect = static_cast<GLdouble>(windowWidth) / static_cast<GLdouble>(windowHeight);
	gluPerspective(60.0, (GLdouble)windowWidth / (GLdouble)windowHeight, 1.0, ((windowHeight / 2.f) / tan(M_PI / 8.f)) * 5.f);
}

void MyScene::setGlobalLight()
{
    // Set lighting effect colours and positional parameter
    float ambient[] = { .2f, .2f, .2f, 1.f };      // ambient light (20% white)
    float diffuse[] = { 1.f, 1.f, 1.f, 1.f };      // diffuse light (100% white)
    float specular[] = { 0.2f, 0.2f, 0.2f, 1.f };      // specular light (100% white)
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

	float x, y, z;
	camera.GetEyePosition(x, y, z);
	stage->position(x, y-((static_cast<float>(Scene::GetWindowHeight()) / 2.f) / tan(M_PI / 8.f) / 2), z);
	stage->size((GetWindowHeight() / 2.f) / tan(M_PI / 8.f));

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

void MyScene::Reshape(int w, int h)
{
	// update window properties
	windowWidth = w;
	windowHeight = h;
	// Reset projection matrix
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	// Generate new projection transform based on updated window properties
	Projection();
	
	// Revert to MODELVIEW (for viewing)
	glMatrixMode(GL_MODELVIEW);

	// Update viewport for new window dimensions
	camera.SetViewport();
	
}