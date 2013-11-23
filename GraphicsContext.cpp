#include <GraphicsContext.h>

#include <gl_libs.h>
#include <fstream>
#include <sstream>
#include <statics.h>
#include <Sprite.h>

static Mat4 modelview = Mat4(), projection = Mat4();

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
 
  std::string vShaderString = getShaderSourceCode(vName);
  std::string fShaderString = getShaderSourceCode(fName);

  const char* vertexShaderName = vShaderString.c_str();
  const char* fragmentShaderName = fShaderString.c_str();

  GLint vShaderSize = vShaderString.size();
  GLint fShaderSize = fShaderString.size();
   
  glShaderSource(_vertexShader, 1, (const GLchar**)&vertexShaderName, (GLint*)&vShaderSize );
  glShaderSource(_fragmentShader, 1, (const GLchar**)&fragmentShaderName, (GLint*)&fShaderSize); 
 
  //printf("vShader:\n%s\nfShader:\n%s\n", vertexShaderName, fragmentShaderName);
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

    printf("Could not compile: %s", infoLog);
  }
  
  glGetShaderiv(_fragmentShader, GL_COMPILE_STATUS, &isCompiled);
  if (isCompiled == GL_FALSE) {
    printf("Fragment Shader Compilation Failed!\n");
    GLint maxLength = 0;
    glGetShaderiv(_fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

    GLchar* infoLog = new GLchar[maxLength];
    glGetShaderInfoLog(_fragmentShader, maxLength, &maxLength, infoLog);

    printf("Could not compile: %s", infoLog);
  }

  GLuint _program = glCreateProgram();

  glAttachShader(_program, _vertexShader);
  glAttachShader(_program, _fragmentShader);

  glLinkProgram(_program);
 
  GLint isLinked;

  glGetProgramiv(_program, GL_LINK_STATUS, &isLinked);
  if(!isLinked) {
    printf("Program not linked correctly!\n"); 
    GLint maxLength = 0;
    glGetProgramiv(_program, GL_INFO_LOG_LENGTH, &maxLength);

    GLchar* infoLog = new GLchar[maxLength];
    glGetProgramInfoLog(_vertexShader, maxLength, &maxLength, infoLog);
    printf("%s", infoLog);
  }
 
  glUseProgram(_program);  

  GLint projectionMatID;
  std::string proMat = "projectionMatrix";
  GLint modelMatID;
  std::string modMat = "modelMatrix";
  GLint viewMatID;
  std::string viewMat = "viewMatrix";
  
  const char* p = proMat.c_str();

  projectionMatID = glGetUniformLocation(_program, (const GLchar*)p);
  printf("value: %i , %s\n", projectionMatID, p); 
  
  //glUniformMatrix4fv(projectionMatID, 16, GL_FALSE, (GLfloat *)projection.m);   

  glClearColor(0.f,0.f,0.f,1.f);
  glEnable(GL_TEXTURE_2D);
  glEnable(GL_DEPTH_TEST);
  //glDepthFunc(GL_GREATER);

  error = glGetError();
  if(error != GL_NO_ERROR) { 
    printf("Error initializing OpenGL! %s\n",gluErrorString(error));
    return false;
  } 
  return true;
}


std::string GraphicsContext::getShaderSourceCode(const std::string& filename) {
  std::ifstream file (filename.c_str());
 
  printf("opening file: %s\n", filename.c_str());
  
  if (!file) {
    printf("Opening file failed\n"); 
  }

  std::stringstream shaderData;
  shaderData << file.rdbuf();
   
  file.close();
  return shaderData.str();
}


//TODO: Setup process to load textures
bool loadMedia() {return true;}


void drawAxis() {
  glBegin(GL_LINES);
    glColor3f(1,0,0);
    glVertex3f(0,0,0);
    glVertex3f(100,0,0);
  glEnd();

  glBegin(GL_LINES);
    glColor3f(0,1,0);
    glVertex3f(0,0,0);
    glVertex3f(0,100,0);
  glEnd();
  
  glBegin(GL_LINES);
    glColor3f(0,0,1);
    glVertex3f(0,0,0);
    glVertex3f(0,0,100);
  glEnd();
}


void output(int x,int y, float r, float g, float b, char string[]) {
  glColor3f (r,g,b);
  glRasterPos2f(x,y);
  int len, i;
  len = (int)strlen(string);
  for (i = 0; i < len; i++) {
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string[i]);
  }
}


void outPosition() {
  char* str;
  std::string p;
  std::stringstream out;
  out << "POSITION X: " << " Y: " << " Z: ";
  p = out.str();
  str = (char*)(p.c_str());
  output(-SCREEN_WIDTH / 4.f, -SCREEN_HEIGHT / 4.f,1.f,1.f,0.f, str);
}


void pfRender(PFholder &part) {
 for (std::vector<PFcontainer*>::iterator i = part.PFstorage.begin(); 
      i!= part.PFstorage.end(); i++) {
  (*i)->particle->render();
 }
}

extern void update();

void render() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
 
  for (unsigned i = 0; i < 4; i++) {
   pfRender(holder[i]);
  } 
  
  drawAxis(); 
  outPosition();
  
  glutSwapBuffers();
}


void runMainLoop(int val) {
  update();
  render();

  glutTimerFunc(1000 / SCREEN_FPS,runMainLoop,val);
}

void handleKeys(unsigned char key, int x, int y) {
gameContext->getUserContext()->_keyInput->handleInput(key,x,y);
}

void handleMouseMovement(int x, int y) {
 gameContext->getUserContext()->_mouseInput->handleMouseMovement(x,y);
}

void handleMouseClick(int button, int state, int x, int y) {
gameContext->getUserContext()->_mouseInput->handleMouseClick(button,state,x,y);
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
  glutMotionFunc(handleMouseMovement);
  glutMouseFunc(handleMouseClick); 
  glutDisplayFunc(render);
  glutTimerFunc(1000 / SCREEN_FPS,runMainLoop,0);
  glutMainLoop();

  return true;
}
