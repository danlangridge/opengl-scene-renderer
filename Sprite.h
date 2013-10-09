#pragma once

#include "gl_libs.h"
#include "Particle.h"

class Sprite : public Particle {
  public:
    float h;
    float w;
    float l;
    GLfloat* color;
    Sprite();
    Sprite(float h, float w, float l);
    void setColor(float x, float y, float z);
    void render();
    ~Sprite();
};
