#include "Sprite.h"

#define DEBUG_RENDER 0

    Sprite::Sprite() {
     d = .999f;
     h = 2;
     w = 2;
     color = new GLfloat[3];
     color[0] = 1.f;
     color[1] = 1.f;
     color[2] = 1.f;
    }
    Sprite::Sprite(float h, float w) {
      this->h = h;
      this->w = w;
      color = new GLfloat[3];
      color[0] = 1.f;
      color[1] = 1.f;
      color[2] = 1.f;
    }
    void Sprite::render() {
      //glClearColor(0.f,0.f,0.f,1.f);
      glColor3f(color[0],color[1],color[2]);
      //glColor3f(1,0,0);
      //printf("Render\n");
      glBegin(GL_QUADS);
        glVertex2f(p.x-w, p.y+h);
        glVertex2f(p.x+w, p.y+h);
        glVertex2f(p.x+w, p.y-h);
        glVertex2f(p.x-w, p.y-h);
      glEnd();
    
     if (DEBUG_RENDER) { 
       glColor3f(1.f,1.f,1.f);
         glBegin(GL_LINES);
            glVertex2f(p.x,p.y);
            glVertex2f(p.x+v.x,p.y+v.y);
         glEnd();
    }
   }
   Sprite::~Sprite() {
    delete [] color;
   }
