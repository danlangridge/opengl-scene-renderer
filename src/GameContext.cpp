#include <GameContext.h>
#include <statics.h>
#include <Sprite.h>

GameContext::GameContext()
  :_graphicsContext(new GraphicsContext()),
   _physicsContext(new PhysicsContext()), 
   _userContext(new UserContext())
  {}


UserContext* GameContext::getUserContext() {
  return _userContext;
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


void update() {
 for (unsigned i = 0; i < 4; i++) {
  boundsCheck(holder[i]);
 } 
}


void GameContext::InitGL(int argv, char* argc[]) {
  
  generateParticles(holder[0],  0.0, -1.0,  0.0);
  generateParticles(holder[1], -1.0, -1.0,  0.0);
  generateParticles(holder[2],  0.0,  0.0, -1.0);
  generateParticles(holder[3], -1.0,  0.0,  0.0);
  
  this->_graphicsContext->InitGLHelperLibraries(argv, argc);
}
