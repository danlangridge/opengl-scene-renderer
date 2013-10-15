#include <Vector.h>
#include <PFholder.h>

#include <GameContext.h>

static const GLfloat change = 0.f;

static const GLfloat CLIPPING_DEPTH_MIN = 100;
static const GLfloat CLIPPING_DEPTH_MAX = 2000;
static const GLfloat CENTER = (CLIPPING_DEPTH_MAX-CLIPPING_DEPTH_MIN)/2;
static const GLfloat DEPTH_MIN = -CENTER; 
static const GLfloat DEPTH_MAX = +CENTER;

static const int SCREEN_WIDTH = 640;
static const int SCREEN_HEIGHT = 480;
static const int SCREEN_FPS = 60;

static float rotatei = 0, rotatej = 0, rotatek = 0, rotatea = 0;

static GLfloat gCameraX = 0.f;
static GLfloat gCameraY = 0.f;
static GLfloat gCameraZ = 0.f;
static Vector Camera;

static PFholder* holder = new PFholder[4];

static GameContext gameContext;

static const int NUM_SPRITES = 50;

void runMainLoop(int val);
