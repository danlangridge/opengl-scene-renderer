#include "gllibs.h"
#include "Sprite.h"
#include "PFholder.h"

GLfloat change = 0.f;
GLfloat gCameraX = 0.f;
GLfloat gCameraY = 0.f;


Sprite s = Sprite();

PFholder sprites;
void generate_particles() {
  Vector grav = Vector(0.f,1.f,0.f);
  ParticleGravity* g = new ParticleGravity(grav);
  for (unsigned i = 0; i < 20; i++) {
    Sprite* s = new Sprite(); 
    (s->p).x = 30.f + (float)i;
    (s->v).x = 5.f + (float)i;
    sprites.add(s, g);
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

void update() {
 sprites.updateForces(1); 

 for (std::vector<PFcontainer*>::iterator i = sprites.PFstorage.begin(); 
      i!= sprites.PFstorage.end(); i++) {
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

void render() {
  glClear(GL_COLOR_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glPopMatrix();
  glPushMatrix();

  //s.render(); 

  // Go to middle of the screen
  glTranslatef(SCREEN_WIDTH/2.f,SCREEN_HEIGHT/2.f,0.f);
  
 for (std::vector<PFcontainer*>::iterator i = sprites.PFstorage.begin(); 
      i!= sprites.PFstorage.end(); i++) {
  (*i)->particle->render();
}
 /* glBegin(GL_QUADS);
    glColor3f(1.f,0.f,0.f);
    glVertex2f(-10.f, -10.f);
    glVertex2f(10.f, -10.f);
    glVertex2f(20.f, 20.f);
    glVertex2f(-20.f, 20.f);
  glEnd();
*/
  out_position();
  glutSwapBuffers();
}

bool loadMedia() {return true;}

void handleKeys(unsigned char key, int x, int y) {
  if (key == 'w') {gCameraY -= 16.f;}
  else if (key == 's') {gCameraY += 16.f;}
  else if (key == 'a') {gCameraX -= 16.f;}
  else if (key == 'd') {gCameraX += 16.f;}
  else if (key == 'g') {s.v.x += 1;}
  glMatrixMode(GL_MODELVIEW);
  glPopMatrix();
  glLoadIdentity();
  glTranslatef(-gCameraX,-gCameraY,0.f);
  glPushMatrix();
}


void initAll(int argv, char* argc[]) {
  generate_particles();
  
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
