#pragma once
#include <gl_libs.h>


class GraphicsContext {
public:
  GLint _program;
  GLint _fragmentShader;
  GLint _vertexShader;
  GLint _texture;

  GraphicsContext();
  bool initGraphicsContext();
  bool InitGLHelperLibraries(int argv, char* argc[]);

private:
  GLchar* getShaderSourceCode(const std::string& filename);

};
