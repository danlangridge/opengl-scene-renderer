#ifndef GL_LIBS_H
#define GL_LIBS_H

#include "string.h"
#include <sstream>
#include <stdio.h>
#include <GL/freeglut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "SOIL.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_FPS = 60;
GLfloat gCameraX = 0.f;
GLfloat gCameraY = 0.f;

void runMainLoop(int val);

#endif
