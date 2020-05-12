#include "../HeaderFiles/Stage.h"

Stage::Stage(){}

void Stage::setTextures(GLuint* _texids)
{
    texids = _texids;                       // Store texture references in pointer array
    toTexture = true;                       // Assume all loaded correctly
    for (int i = 0; i < 6; i++)             // Check if any textures failed to load (NULL)    
        if (texids[i] == -1) toTexture = false;   // If one texture failed, do not display any
    //printf("%d\n", toTexture);
}

void Stage::Display()
{
    glPushMatrix();
    glPushAttrib(GL_ALL_ATTRIB_BITS);

    // Position objects in world space
    glTranslatef(pos[0], pos[1], pos[2]);               // Position
    glScalef(scale[0], scale[1], scale[2]);             // Scale
    glRotatef(rotation[1], 0.f, 1.f, 0.f);              // Set orientation (Y)
    glRotatef(rotation[2], 0.f, 0.f, 1.f);              // Set orientation (Z)
    glRotatef(rotation[0], 1.f, 0.f, 0.f);              // Set orientation (X)

    drawStage();

    glPopAttrib();
    glPopMatrix();
}

void Stage::drawStage()
{
    glDisable(GL_LIGHTING);
    glColor4f(1.f, 1.f, 1.f, 1.f); // fill is invisible, only texture rendered.
    if (toTexture) glEnable(GL_TEXTURE_2D);


    if (toTexture) glBindTexture(GL_TEXTURE_2D, texids[0]); // skybox_left.bmp
    glBegin(GL_QUADS);
    // LEFT SIDE
    if (toTexture) glTexCoord2f(1.f, 1.f);  // (u,v) = (1,1)
    glVertex3f(-1.f, 1.f, -1.f);
    if (toTexture) glTexCoord2f(0.f, 1.f);  // (u,v) = (0,1)
    glVertex3f(-1.f, 1.f, 1.f);
    if (toTexture) glTexCoord2f(0.f, 0.f);  // (u,v) = (0,0)
    glVertex3f(-1.f, 0.f, 1.f);
    if (toTexture) glTexCoord2f(1.f, 0.f);  // (u,v) = (1,0)
    glVertex3f(-1.f, 0.f, -1.f);
    glEnd();

    if (toTexture) glBindTexture(GL_TEXTURE_2D, texids[1]); // skybox_right.bmp
    glBegin(GL_QUADS);
    // RIGHT SIDE
    if (toTexture) glTexCoord2f(1.f, 1.f);  // (u,v) = (1,1)
    glVertex3f(1.f, 1.f, 1.f);
    if (toTexture) glTexCoord2f(0.f, 1.f);  // (u,v) = (0,1)
    glVertex3f(1.f, 1.f, -1.f);
    if (toTexture) glTexCoord2f(0.f, 0.f);  // (u,v) = (0,0)
    glVertex3f(1.f, 0.f, -1.f);
    if (toTexture) glTexCoord2f(1.f, 0.f);  // (u,v) = (1,0)
    glVertex3f(1.f, 0.f, 1.f);
    glEnd();

    if (toTexture) glBindTexture(GL_TEXTURE_2D, texids[2]); // skybox_front.bmp
    glBegin(GL_QUADS);
    //  FAR SIDE
    if (toTexture) glTexCoord2f(1.f, 1.f);  // (u,v) = (1,1)
    glVertex3f(1.f, 1.f, -1.f);
    if (toTexture) glTexCoord2f(0.f, 1.f);  // (u,v) = (0,1)
    glVertex3f(-1.f, 1.f, -1.f);
    if (toTexture) glTexCoord2f(0.f, 0.f);  // (u,v) = (0,0)
    glVertex3f(-1.f, 0.f, -1.f);
    if (toTexture) glTexCoord2f(1.f, 0.f);  // (u,v) = (1,0)
    glVertex3f(1.f, 0.f, -1.f);
    glEnd();

    if (toTexture) glBindTexture(GL_TEXTURE_2D, texids[3]); // skybox_back.bmp
    glBegin(GL_QUADS);
    // NEAR SIDE
    if (toTexture) glTexCoord2f(1.f, 1.f);  // (u,v) = (1,1)
    glVertex3f(-1.f, 1.f, 1.f);
    if (toTexture) glTexCoord2f(0.f, 1.f);  // (u,v) = (0,1)
    glVertex3f(1.f, 1.f, 1.f);
    if (toTexture) glTexCoord2f(0.f, 0.f);  // (u,v) = (0,0)
    glVertex3f(1.f, 0.f, 1.f);
    if (toTexture) glTexCoord2f(1.f, 0.f);  // (u,v) = (1,0)
    glVertex3f(-1.f, 0.f, 1.f);
    glEnd();

    if (toTexture) glBindTexture(GL_TEXTURE_2D, texids[4]); // skybox_down.bmp
    glBegin(GL_QUADS);
    // BOTTOM SIDE
    if (toTexture) glTexCoord2f(0.f, 0.f);  // (u,v) = (0,0)
    glVertex3f(-1.f, 0.f, 1.f);
    if (toTexture) glTexCoord2f(1.f, 0.f);  // (u,v) = (1,0)
    glVertex3f(1.f, 0.f, 1.f);
    if (toTexture) glTexCoord2f(1.f, 1.f);  // (u,v) = (1,1)
    glVertex3f(1.f, 0.f, -1.f);
    if (toTexture) glTexCoord2f(0.f, 1.f);  // (u,v) = (0,1)
    glVertex3f(-1.f, 0.f, -1.f);
    glEnd();

    if (toTexture) glBindTexture(GL_TEXTURE_2D, texids[5]); // skybox_up.bmp
    glBegin(GL_QUADS);
    // TOP SIDE
    if (toTexture) glTexCoord2f(1.f, 1.f);  // (u,v) = (1,1)
    glVertex3f(1.f, 1.f, 1.f);
    if (toTexture) glTexCoord2f(0.f, 1.f);  // (u,v) = (0,1)
    glVertex3f(-1.f, 1.f, 1.f);
    if (toTexture) glTexCoord2f(0.f, 0.f);  // (u,v) = (0,0)
    glVertex3f(-1.f, 1.f, -1.f);
    if (toTexture) glTexCoord2f(1.f, 0.f);  // (u,v) = (1,0)
    glVertex3f(1.f, 1.f, -1.f);
    glEnd();

    if (toTexture) glDisable(GL_TEXTURE_2D);        //disable texturing until reenabled
    glEnable(GL_LIGHTING);                          // renable lighting after drawing skybox
}