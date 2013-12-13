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
  else if (key == 'x') {rotatei++;}
  else if (key == 'c') {rotatej++;}
  else if (key == 'v') {rotatek++;}
  else if (key == 'b') {rotatea++;}
  else if (key == 'z') {rotatea = 0; rotatei = 0; rotatej = 0; rotatek = 0;}
  
  Vector position = userContext->getPosition();
}

