#include "Sprite.h"
#include <statics.h>
#define DEBUG_RENDER 0

    Sprite::Sprite() {
     d = .999f;
     h = 2;
     w = 2;
     l = 2;
     color = new GLfloat[3];
     color[0] = 1.f;
     color[1] = 1.f;
     color[2] = 1.f;
    }
    
    Sprite::Sprite(float h, float w, float l) {
      this->h = h;
      this->w = w;
      this->l = l;
      color = new GLfloat[3];
      color[0] = 1.f;
      color[1] = 1.f;
      color[2] = 1.f;
    }
    
   void Sprite::setColor(float x, float y, float z) {
      color[0] = x;
      color[1] = y;
      color[2] = z;
    }
    
    void Sprite::render() {
      GLfloat color[3] = { color[0],
                           color[1],
                           color[2]
                         };
     
      GLfloat cube[48] = {
        p.x-w, p.y+h, p.z+l,
        p.x+w, p.y+h, p.z+l,
        p.x+w, p.y-h, p.z+l,
        p.x-w, p.y-h, p.z+l,
     
        p.x-w, p.y+h, p.z-l,
        p.x+w, p.y+h, p.z-l,
        p.x+w, p.y-h, p.z-l,
        p.x-w, p.y-h, p.z-l,
     
        p.x+w, p.y+h, p.z+l,
        p.x+w, p.y+h, p.z-l,
        p.x+w, p.y-h, p.z-l,
        p.x+w, p.y-h, p.z+l,
     
        p.x-w, p.y+h, p.z+l,
        p.x-w, p.y+h, p.z-l,
        p.x-w, p.y-h, p.z-l,
        p.x-w, p.y-h, p.z+l
    }; 
    
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
