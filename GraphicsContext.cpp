#include <GraphicsContext.h>

#include <gl_libs.h>
#include <fstream>
#include <statics.h>

GraphicsContext::GraphicsContext()
  :_program(0),
   _fragmentShader(0),
   _vertexShader(0),
   _texture(0)
  {}


bool GraphicsContext::initGraphicsContext() {

  GLenum error;
  glViewport(0.f,0.f,SCREEN_WIDTH,SCREEN_HEIGHT);
  
  GLuint _vertexShader = glCreateShader(GL_VERTEX_SHADER);
  GLuint _fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

  std::string vName = "shaders/main.vert";
  std::string fName = "shaders/main.frag";
  
  const GLchar* vertexShaderName = getShaderSourceCode(vName);
  const GLchar* fragmentShaderName = getShaderSourceCode(fName);

  glShaderSource(_vertexShader, 1, &vertexShaderName, 0);
  glShaderSource(_fragmentShader, 1, &fragmentShaderName, 0); 
  
  glCompileShader(_vertexShader);
  glCompileShader(_fragmentShader);

  GLint isCompiled = 0;
  glGetShaderiv(_vertexShader, GL_COMPILE_STATUS, &isCompiled);
  if (isCompiled == GL_FALSE) {
    printf("Vertex Shader Compilation Failed!\n");
    GLint maxLength = 0;
    glGetShaderiv(_vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

    GLchar* infoLog = new GLchar[maxLength];
    glGetShaderInfoLog(_vertexShader, maxLength, &maxLength, infoLog);

    printf("Could not compile: %s\n", infoLog);
  }
  
  glGetShaderiv(_fragmentShader, GL_COMPILE_STATUS, &isCompiled);
  if (isCompiled == GL_FALSE) {
    printf("Fragment Shader Compilation Failed!\n");
    GLint maxLength = 0;
    glGetShaderiv(_fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

    GLchar* infoLog = new GLchar[maxLength];
    glGetShaderInfoLog(_fragmentShader, maxLength, &maxLength, infoLog);

    printf("Could not compile: %s\n", infoLog);
  }

  GLuint _program = glCreateProgram();

  glAttachShader(_program, _vertexShader);
  glAttachShader(_program, _fragmentShader);

  glLinkProgram(_program);
 
  GLint isLinked;

  glGetProgramiv(_program, GL_LINK_STATUS, &isLinked);
  if(!isLinked)
  {
    printf("Program not linked correctly!\n"); 
    GLint maxLength = 0;
    glGetProgramiv(_program, GL_INFO_LOG_LENGTH, &maxLength);

    GLchar* infoLog = new GLchar[maxLength];
    glGetProgramInfoLog(_vertexShader, maxLength, &maxLength, infoLog);
    printf("%s", infoLog);
 }
 
  glUseProgram(_program);

  error = glGetError();
  if(error != GL_NO_ERROR) { 
    //printf("Error initializing OpenGL! %s\n",gluErrorString(error));
  } 
    
  // Projection Matrix
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glFrustum(-SCREEN_WIDTH/2, SCREEN_WIDTH/2, SCREEN_HEIGHT/2, -SCREEN_HEIGHT/2, CLIPPING_DEPTH_MIN, CLIPPING_DEPTH_MAX);
  
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
   
  glPushMatrix();

  glClearColor(0.f,0.f,0.f,1.f);
  glEnable(GL_TEXTURE_2D);
  glEnable(GL_DEPTH_TEST);
  //glDepthFunc(GL_GREATER);

 error = glGetError();
  if(error != GL_NO_ERROR) { 
    //printf("Error initializing OpenGL! %s\n",gluErrorString(error));
    return false;
  } 
  return true;
}

GLchar* GraphicsContext::getShaderSourceCode(const std::string& filename) {
  std::ifstream file (filename.c_str());
 
  printf("opening file: %s\n", filename.c_str());
  
  if (!file) {
    printf("Opening file failed\n"); 
  }
    file.seekg(0, file.end);
    int length = file.tellg();
    file.seekg(0, file.beg);
    
    printf("Length: %i\n", length);
    GLchar* buffer = new char[length]();
 
    file.read(buffer,length);

    //printf("buffer: %s\n", buffer);
    file.close();
    return buffer; 
}


//TODO: Setup process to load textures
bool loadMedia() {return true;}


void handleKeys(unsigned char key, int x, int y) {  
  gameContext->KeyInput(key);
}


void handleMouse(int x, int y) {
  gameContext->MouseInput(x,y);
}


extern void render();
extern void update();


void runMainLoop(int val) {
  update();
  render();

  glutTimerFunc(1000 / SCREEN_FPS,runMainLoop,val);
}


bool GraphicsContext::InitGLHelperLibraries(int argv, char* argc[]) {

  // GLUT INITIALIZATION
  glutInit(&argv,argc);
  glutInitWindowPosition(SCREEN_WIDTH,SCREEN_HEIGHT);
  glutInitWindowSize(SCREEN_WIDTH,SCREEN_HEIGHT);
  glutCreateWindow("My OpenGL based Game");
  glutInitContextVersion(2,1);
  glutInitDisplayMode(GLUT_DOUBLE);

  GLenum err = glewInit();
  if (GLEW_OK != err) {
    printf("issues initializing GLEW: %s\n", glewGetErrorString(err) );
    return false; 
  }
  
  // INITIALIZE OPENGL AND LOADMEDIA
  if (!initGraphicsContext()) {
    printf("Cannot initialize OpenGL!");
    return false; 
  } 
  if (!loadMedia()) printf("Cannot load media!\n"); 
  
  glutKeyboardFunc(handleKeys);
  glutMotionFunc(handleMouse);
  glutDisplayFunc(render);
  glutTimerFunc(1000 / SCREEN_FPS,runMainLoop,0);
  glutMainLoop();

  return true;
}
