#pragma once
#include "DisplayableObject.h"
class Stage :
	public DisplayableObject
{
public:
    Stage();
    ~Stage() {};
    void Display();
    void setTextures(GLuint* _texids);
private:
    void drawStage();
    bool toTexture = false;             // Flag to check if textures loaded correctly
    GLuint* texids;                     // Store a copy of the loaded texture binding ids
};

