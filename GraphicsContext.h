#pragma once
#include <gl_libs.h>
#include <string.h>
#include <Mat4.h>
#include <map>


struct MatUniform {
  Mat4 data; 
  GLuint ID; 
};


struct VertexArrayObject {
 GLuint ID; 
};

class GraphicsContext {
public:
  GLint _program;
  GLint _fragmentShader;
  GLint _vertexShader;
  MatUniform _view;
  MatUniform _projection;
  std::map<std::string,GLuint> VertexArrayObject;
  
  GraphicsContext();
  bool initGraphicsContext();
  bool InitGLHelperLibraries(int argv, char* argc[]);
  
private:
 std::string getShaderSourceCode(const std::string& filename);
 void setupBuffers(); 
 void setupShaders();
 bool linkProgram();
};
