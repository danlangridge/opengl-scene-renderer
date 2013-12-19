#pragma once

#include <vector>
#include <gl_libs.h>

struct VertexArrayObject {
  GLuint ID;
  
  VertexArrayObject();   
  
  void generateArray();
  void addArrayPointer(const GLuint& vertexID, std::vector<GLfloat>& vertexContainer);

};
