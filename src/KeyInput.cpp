#include <gl_libs.h>
#include <statics.h>
#include <KeyInput.h>


void KeyInput::handleInput(unsigned char key, int x, int y) {

 UserContext* userContext = gameContext->getUserContext();
 if (key == 'w') {userContext->Move(0,0,16);}
  else if (key == 's') {userContext->Move(0,0,-16);}
  else if (key == 'a') {userContext->Move(16,0,0);}
  else if (key == 'd') {userContext->Move(-16,0,0);}
  else if (key == 'i') {userContext->Move(0,16,0);}
  else if (key == 'j') {userContext->Move(0,16,0);}
  else if (key == 'g') {
    for (unsigned i = 0; i < 4; i++) {
       ((ParticleGravity*)holder[i].PFstorage[0]->generator)->g; 
       Vector* point = new Vector(); 
       //Vector* point = &(((ParticleGravity*)((holder[i].PFstorage[0])->generator))->g); 
       point->x = -point->x;
       point->y = -point->y;
       point->z = -point->z;
    }
  } 
  else if (key == 'q') {exit(0);}
  else if (key == 'x') {userContext->_camera->rotateTheta(1);}
  else if (key == 'c') {userContext->_camera->rotateTheta(-1);}
  else if (key == 'v') {userContext->_camera->rotatePhi(1);}
  else if (key == 'b') {userContext->_camera->rotatePhi(-1);}
  else if (key == 'z') {userContext->_camera->resetOrientation();}
  
  Vector position = userContext->getPosition();
}

