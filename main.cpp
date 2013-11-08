
#include <GLContext.h>
#include <statics.h>
#include <Sprite.h>
#include <gl_libs.h>
#include <PFholder.h>
#include <GameContext.h>
#include <KeyInput.h>

#include <fstream>
#include <cstdio>
#include <cstdlib>


#define ABS(x)  ((x <= 0) ? -x : x)  


void generateParticles(PFholder &ph, float x, float y, float z) {
  srand(10);
  Vector grav = Vector(x, y, z);
  ParticleGravity* g = new ParticleGravity(grav);
  for (unsigned i = 0; i < NUM_SPRITES; i++) {
    int temp = rand() % 5 + 5;
    Sprite* s = new Sprite(temp,temp,temp);
    s->setColor( ABS(x), ABS(y), ABS(z));
    s->d = (float)(999 - (rand() % 40))/999;
    //s->d = 1;
    (s->p).x = rand() % SCREEN_WIDTH;//(float)i;
    (s->p).y = rand() % SCREEN_HEIGHT;//-(float)i;
    (s->v).x = (float)i;
    (s->v).y = (float)i;
    (s->v).z = (float)i;
    ph.add(s, g);
    } 
}

void output(int x,int y, float r, float g, float b, char string[]) {
  glColor3f (r,g,b);
  glRasterPos2f(x,y);
  int len, i;
  len = (int)strlen(string);
  for (i = 0; i < len; i++) {
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string[i]);
    }
}

void outPosition() {
  char* str;
  std::string p;
  std::stringstream out;
  out << "POSITION X: " << Camera.x << " Y: " << Camera.y << " Z: " << Camera.z;
  p = out.str();
  str = (char*)(p.c_str());
  output(-SCREEN_WIDTH / 4.f, -SCREEN_HEIGHT / 4.f,1.f,1.f,0.f, str);
  //printf("Position X: %f Y: %f\n", gCameraX, gCameraY);  
}


void drawAxis() {
  glBegin(GL_LINES);
    glColor3f(1,0,0);
    glVertex3f(0,0,0);
    glVertex3f(100,0,0);
  glEnd();

  glBegin(GL_LINES);
    glColor3f(0,1,0);
    glVertex3f(0,0,0);
    glVertex3f(0,100,0);
  glEnd();
  
  glBegin(GL_LINES);
    glColor3f(0,0,1);
    glVertex3f(0,0,0);
    glVertex3f(0,0,100);
  glEnd();
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
  else if (((*i)->particle->p).z > DEPTH_MAX/2 && ((*i)->particle->v).z > 0) {
     ((*i)->particle->v).z = -((*i)->particle->v).z;
  }
  else if (((*i)->particle->p).z < DEPTH_MIN/2 && ((*i)->particle->v).z < 0) {
     ((*i)->particle->v).z = -((*i)->particle->v).z;
  }
 }
}

void update() {
 for (unsigned i = 0; i < 4; i++) {
  boundsCheck(holder[i]);
 } 
}

void pfRender(PFholder &part) {
 for (std::vector<PFcontainer*>::iterator i = part.PFstorage.begin(); 
      i!= part.PFstorage.end(); i++) {
  (*i)->particle->render();
 }
}


void render() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
 
  //Set Axis: y+ up, x+ right, z+ forward
  //glRotatef(180,0,0,1);
  
  //glLoadIdentity();
  glTranslatef(-SCREEN_WIDTH/2,-SCREEN_HEIGHT/2, -CLIPPING_DEPTH_MIN-CENTER);
  //glTranslatef(0,0,-CLIPPING_DEPTH_MIN);
  glRotatef(rotatea, rotatei, rotatej, rotatek); 
  // Render Particles
  glPushMatrix();
 for (unsigned i = 0; i < 4; i++) {
  pfRender(holder[i]);
 } 
 glPopMatrix();

  // Generate Pointer 
  glPushMatrix();
  //glLoadIdentity();
  //glTranslatef(SCREEN_WIDTH/2.f,SCREEN_HEIGHT/2.f, 0.11);
 drawAxis();
 
 //glLoadIdentity();
 /*
  glColor3f(1,0,0); 
  
  glBegin(GL_QUADS);
    glVertex3f(0.0,0.0,0.0);
    glVertex3f(SCREEN_WIDTH/2, 0.0,0.0);
    glVertex3f(SCREEN_WIDTH/2, SCREEN_HEIGHT/2,0.0);
    glVertex3f(0.0,SCREEN_HEIGHT/2,0.0);
  glEnd();

  glColor3f(0,1,0); 
  
  glBegin(GL_QUADS);
    glVertex3f(SCREEN_WIDTH/2,0.0,0.0);
    glVertex3f(SCREEN_WIDTH/2, 0.0,DEPTH_MIN);
    glVertex3f(SCREEN_WIDTH/2, SCREEN_HEIGHT/2,DEPTH_MIN);
    glVertex3f(SCREEN_WIDTH/2,SCREEN_HEIGHT/2,0.0);
  glEnd();

  glColor3f(0,0,1); 
  
  glBegin(GL_QUADS);
    glVertex3f(0.0,0.0,DEPTH_MIN);
    glVertex3f(SCREEN_WIDTH/2, 0.0,DEPTH_MIN);
    glVertex3f(SCREEN_WIDTH/2, SCREEN_HEIGHT/2,DEPTH_MIN);
    glVertex3f(0.0,SCREEN_HEIGHT/2,DEPTH_MIN);
  glEnd();
*/
 outPosition();
 glPopMatrix();
 //glTranslatef(SCREEN_WIDTH/2.f,SCREEN_HEIGHT/2.f,1.f);
  glPopMatrix();
  glutSwapBuffers();
}

bool loadMedia() {return true;}

void handleKeys(unsigned char key, int x, int y) {  
  gameContext->_userContext->_input->handleInput(key);
}


void initAll(int argv, char* argc[]) {

  generateParticles(holder[0],  0.0, -1.0,  0.0);
  generateParticles(holder[1], -1.0, -1.0,  0.0);
  generateParticles(holder[2],  0.0,  0.0, -1.0);
  generateParticles(holder[3], -1.0,  0.0,  0.0);
  if (!InitGLContext(argv,argc)) {
    printf("FAILED TO INITIALIZE GL CONTEXT!\n TERMINATING..\n"); 
  }
}

int main(int argv, char* argc[]) {
  initAll(argv,argc);
  return 0;
}
