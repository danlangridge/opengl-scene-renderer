#include <statics.h>
#include <Sprite.h>
#include <gl_libs.h>
#include <PFholder.h>
#include <GameContext.h>
#include <KeyInput.h>

#include <fstream>
#include <cstdio>
#include <cstdlib>

extern void generateParticles(PFholder &ph, float x, float y, float z);


void initAll(int argv, char* argc[]) {

  generateParticles(holder[0],  0.0, -1.0,  0.0);
  generateParticles(holder[1], -1.0, -1.0,  0.0);
  generateParticles(holder[2],  0.0,  0.0, -1.0);
  generateParticles(holder[3], -1.0,  0.0,  0.0);
  
  gameContext->InitGL(argv,argc);
}


int main(int argv, char* argc[]) {
  initAll(argv,argc);
  return 0;
}
