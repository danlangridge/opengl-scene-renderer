#pragma once
#include <gl_libs.h>
#include <string.h>
#include <Mat4.h>

struct MatUniform {
  Mat4 data; 
  GLuint ID; 
};

class GraphicsContext {
public:
  GLint _program;
  GLint _fragmentShader;
  GLint _vertexShader;
  MatUniform _view;
  MatUniform _projection;
  
  GraphicsContext();
  bool initGraphicsContext();
  bool InitGLHelperLibraries(int argv, char* argc[]);
  
private:
  std::string getShaderSourceCode(const std::string& filename);
  void setupBuffers(); 
  void setupUniforms();
  void setupShaders();
  bool linkProgram();
};
