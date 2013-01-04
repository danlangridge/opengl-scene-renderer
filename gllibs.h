#ifndef GLLIBS_H
#define GLLIBS_H

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

void runMainLoop(int val);

#endif
