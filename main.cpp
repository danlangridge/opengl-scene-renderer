//#include "gllibs.h"
#include "Sprite.h"
#include "PFholder.h"

#define ABS(x)  ((x <= 0) ? -x : x)  

GLfloat change = 0.f;
GLfloat gCameraX = 0.f;
GLfloat gCameraY = 0.f;


Sprite s = Sprite();
PFholder sprites;
PFholder dust;
PFholder steam;
PFholder slag;

const int NUM_SPRITES = 20;


void generateParticles(PFholder &part, float x, float y, float z) {
  Vector grav = Vector(x, y, z);
  ParticleGravity* g = new ParticleGravity(grav);
  for (unsigned i = 0; i < NUM_SPRITES; i++) {
    Sprite* s = new Sprite();
    s->color[0] = ABS(x);
    s->color[1] = ABS(y);
    s->color[2] = ABS(z);
    (s->p).x = (float)i;
    (s->p).y = -(float)i;
    (s->v).x = (float)i;
    (s->v).y = (float)i;
    part.add(s, g);
    } 
}

void output(int x,int y,float r,float g,float b, char string[]) {
  glColor3f (r,g,b);
  glRasterPos2f(x,y);
  int len, i;
  len = (int)strlen(string);
  for (i = 0; i < len; i++) {
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string[i]);
    }
}

void out_position() {
  char* str;
  std::string p;
  std::stringstream out;
  out << "POSITION X: " << gCameraX << " Y: " << gCameraY;
  p = out.str();
  str = (char*)(p.c_str());
  output(-SCREEN_WIDTH / 4.f, -SCREEN_HEIGHT / 4.f,1.f,1.f,0.f, str);
}


bool initGL() {
  glViewport(0.f,0.f,SCREEN_WIDTH,SCREEN_HEIGHT);
 
  s.color[1] = 1;
  s.v.x = 1.f;
  s.a.y = 2.f; 
  
  // Projection Matrix
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0.0, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0, 1.0, -1.0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glPushMatrix();

  glClearColor(0.f,0.f,0.f,1.f);
  glEnable(GL_TEXTURE_2D);
  GLenum error = glGetError();
  if(error != GL_NO_ERROR) { 
    printf("Error initializing OpenGL! %s\n",gluErrorString(error));
    return false;
  }
  
  return true;
}

void boundsCheck(PFholder &part) {
 part.updateForces(1); 
 
 for (std::vector<PFcontainer*>::iterator i = part.PFstorage.begin(); 
      i!= part.PFstorage.end(); i++) {
     (*i)->particle->integrate(1);
  if (((*i)->particle->p).x > SCREEN_WIDTH && ((*i)->particle->v).x > 0) {
     ((*i)->particle->v).x = -((*i)->particle->v).x;
  }
  else if (((*i)->particle->p).x < 0 && ((*i)->particle->v).x < 0) {
     ((*i)->particle->v).x = -((*i)->particle->v).x;
  }
  else if (((*i)->particle->p).y > SCREEN_HEIGHT && ((*i)->particle->v).y > 0) {
     ((*i)->particle->v).y = -((*i)->particle->v).y;
  }
  else if (((*i)->particle->p).y < 0 && ((*i)->particle->v).y < 0) {
     ((*i)->particle->v).y = -((*i)->particle->v).y;
  }
 }

}


void update() {
 boundsCheck(sprites);
 boundsCheck(dust);
 boundsCheck(steam);
 boundsCheck(slag);
}

void pfRender(PFholder &part) {
 for (std::vector<PFcontainer*>::iterator i = part.PFstorage.begin(); 
      i!= part.PFstorage.end(); i++) {
  (*i)->particle->render();
 }
}

void render() {
  glClear(GL_COLOR_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  
  // Go to middle of the screen 
  pfRender(sprites);
  pfRender(dust);
  pfRender(steam);
  pfRender(slag);

  // Generate Pointer 
  glColor3f(255,0,0); 
  glPushMatrix();
  glLoadIdentity();
  glTranslatef(SCREEN_WIDTH/2.f,SCREEN_HEIGHT/2.f,0.f);
      glBegin(GL_QUADS);
        glVertex2f(-2, -2);
        glVertex2f(-2, 2);
        glVertex2f(2, 2);
        glVertex2f(2, -2);
      glEnd();
 glPopMatrix();
 glTranslatef(SCREEN_WIDTH/2.f,SCREEN_HEIGHT/2.f,0.f);
  out_position();
  glPopMatrix();
  glutSwapBuffers();
}

bool loadMedia() {return true;}

void handleKeys(unsigned char key, int x, int y) {
  if (key == 'w') {gCameraY -= 16.f;}
  else if (key == 's') {gCameraY += 16.f;}
  else if (key == 'a') {gCameraX -= 16.f;}
  else if (key == 'd') {gCameraX += 16.f;}
  else if (key == 'g') {s.v.x += 1;}
  else if (key == '`') {exit(1);}
  glMatrixMode(GL_MODELVIEW);
  glPopMatrix();
  glLoadIdentity();
  glTranslatef(-gCameraX,-gCameraY,0.f);
  glPushMatrix();
}


void initAll(int argv, char* argc[]) {
  generateParticles(sprites, 0.0, 1.0, 0.0);
  generateParticles(dust, 1.0, 1.0, 0.0);
  generateParticles(steam, 0, 0.0, -1.0);
  generateParticles(slag, -1.0, 0, 0);
  
  // GLUT INITIALIZATION
  glutInit(&argv,argc);
  glutInitWindowPosition(SCREEN_WIDTH,SCREEN_HEIGHT);
  glutInitWindowSize(SCREEN_WIDTH,SCREEN_HEIGHT);
  glutCreateWindow("My OpenGL based Game");
  glutInitContextVersion(2,1);
  glutInitDisplayMode(GLUT_DOUBLE);

  // INITIALIZE OPENGL AND LOADMEDIA
  if (!initGL()) printf("Cannot initialize OpenGL!");
  if (!loadMedia()) printf("Cannot load media!\n"); 
  
  glutKeyboardFunc(handleKeys);
  glutDisplayFunc(render);
  glutTimerFunc(1000 / SCREEN_FPS,runMainLoop,0);
  glutMainLoop();

}

void runMainLoop(int val) {
  update();
  render();
  glutTimerFunc(1000 / SCREEN_FPS,runMainLoop,val);
}


int main(int argv, char* argc[]) {
  initAll(argv,argc);
  return 0;
}
