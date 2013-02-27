#ifndef SPRITE_H
#define SPRITE_H

#include "gllibs.h"
#include "Particle.h"

class Sprite : public Particle {
  public:
    float h;
    float w;
    GLfloat* color;
    Sprite();
    Sprite(float h, float w);
    void setColor(float x, float y, float z);
    void render();
    ~Sprite();
};
#endif
