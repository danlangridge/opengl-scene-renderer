#include <GraphicsContext.h>
#include <VertexArrayObject.h>

#include <gl_libs.h>
#include <statics.h>
#include <Sprite.h>

#include <vector>
#include <fstream>
#include <sstream>


bool checkGLError(const std::string& function) {

  GLenum error;
  error = glGetError(); 
  if(error != GL_NO_ERROR) { 
    printf("OpenGL Error!\n%s: %s\n",function.c_str(), gluErrorString(error));
    return false;
  } 
  return true;
}


bool checkShaderCompilation(const GLint &shader) {
  
  GLint isCompiled = 0;
  glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
  
  if (isCompiled == GL_FALSE) {
    printf("Shader Compilation Failed!\n");
    GLint maxLength = 0;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

    GLchar* infoLog = new GLchar[maxLength];
    glGetShaderInfoLog(shader, maxLength, &maxLength, infoLog);

    printf("Could not compile: %s\n", infoLog);
    checkGLError(__FUNCTION__);
    return false; 
  }
  checkGLError(__FUNCTION__);
  return true;
}


void printShaderInfoLog(const GLint &shader) {

  GLint maxLength = 0;
  glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

  if (maxLength > 1) {
    GLchar* infoLog = new GLchar[maxLength];
    glGetShaderInfoLog(shader, maxLength, &maxLength, infoLog);

    printf("GLSL: %s\n", infoLog);
  }

  checkGLError(__FUNCTION__);  
}
