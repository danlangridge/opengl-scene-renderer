#include <vector>
#include <gl_libs.h>

struct VertexArrayObject {
  GLuint ID;
  VertexArrayObject();   
  void addArrayPointer(const GLuint& vertexID, std::vector<GLfloat>& vertexContainer);

};
