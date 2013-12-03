#include <VertexArrayObject.h>

VertexArrayObject::VertexArrayObject() {
  glGenVertexArrays(1, &ID);
}

void VertexArrayObject::addArrayPointer(const GLuint& vertexID, std::vector<GLfloat>& vertexContainer) {

  glBindVertexArray(ID);

  GLuint buffers[1];
  glGenBuffers(1,buffers);
  glBindBuffer(GL_ARRAY_BUFFER, buffers[0]); 
  glBufferData(GL_ARRAY_BUFFER, vertexContainer.size()*sizeof(GLfloat), &vertexContainer[0], GL_STREAM_DRAW);

  glEnableVertexAttribArray(vertexID);
  glVertexAttribPointer(vertexID , 4, GL_FLOAT, 0,0,0);
}
