#pragma once

#include "SOIL.h"

#include <GL/glew.h>

#include <GL/freeglut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glext.h>

#include <string.h>
#include <sstream>
#include <stdio.h>
#include <cmath>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_FPS = 60;

static GLfloat gCameraX = 0.f;
static GLfloat gCameraY = 0.f;
static GLfloat gCameraZ = 0.f;

void runMainLoop(int val);

