#include <gl_libs.h>
#include <statics.h>
#include <KeyInput.h>


void KeyInput::handleInput(const unsigned char& key) {
 
 if (key == 'w') {Camera.z += 16.f;}
  else if (key == 's') {Camera.z -= 16.f;}
  else if (key == 'a') {Camera.x -= 16.f;}
  else if (key == 'd') {Camera.x += 16.f;}
  else if (key == 'i') {Camera.y += 16.f;}
  else if (key == 'j') {Camera.y -= 16.f;}
  else if (key == 'g') {
    for (unsigned i = 0; i < 4; i++) {
      Vector* point = &(((ParticleGravity*)((holder[i].PFstorage[0])->generator))->g); 
       point->x = -point->x;
       point->y = -point->y;
       point->z = -point->z;
    }
  } 
  else if (key == 'q') {exit(0);}
  else if (key == 'x') {rotatei++;}
  else if (key == 'c') {rotatej++;}
  else if (key == 'v') {rotatek++;}
  else if (key == 'b') {rotatea++;}
  else if (key == 'z') {rotatea = 0; rotatei = 0; rotatej = 0; rotatek = 0;}
  
  
  glMatrixMode(GL_MODELVIEW);
  glPopMatrix();
  glLoadIdentity();
  glTranslatef( Camera.x, Camera.y, Camera.z);
  glPushMatrix();
}

