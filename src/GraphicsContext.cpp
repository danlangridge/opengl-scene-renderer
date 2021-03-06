#include <GraphicsContext.h>
#include <VertexArrayObject.h>
#include <Log.h>

#include <gl_libs.h>
#include <statics.h>
#include <Sprite.h>

#include <vector>
#include <fstream>
#include <sstream>


static Mat4 view, projection;
static GLuint vertexArray[1];
static GLuint vertexID;
static GLfloat vertices;

static Camera globalCamera;
static VertexArrayObject vao; 

static VertexArrayObject testTriangleVao;


GraphicsContext::GraphicsContext()
  :_program(0),
   _fragmentShader(0),
   _vertexShader(0)
  {}


bool GraphicsContext::linkProgram() {
  
  glLinkProgram(_program);
 
  GLint isLinked;

  glGetProgramiv(_program, GL_LINK_STATUS, &isLinked);
  if(!isLinked) {
    LOG_DEBUG("Program not linked correctly!\n"); 
    GLint maxLength = 0;
    glGetProgramiv(_program, GL_INFO_LOG_LENGTH, &maxLength);

    GLchar* infoLog = new GLchar[maxLength];
    glGetProgramInfoLog(_program, maxLength, &maxLength, infoLog);
    LOG_DEBUG("%s\n", infoLog);
    checkGLError(__FUNCTION__);
    return false; 
  }
  checkGLError(__FUNCTION__);
  return true;
}


void GraphicsContext::setupShaders() {

   _vertexShader = glCreateShader(GL_VERTEX_SHADER);
   _fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  
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
  checkShaderCompilation(_vertexShader); 
  
  glCompileShader(_fragmentShader);
  checkShaderCompilation(_fragmentShader); 
   
  checkGLError(__FUNCTION__);
}


void GraphicsContext::setupUniforms() {
  
  const char* proMat = "projectionMatrix\0";
  const char* viewMat = "viewMatrix\0";
  
  GLint projectionMatID = 0, viewMatID = 0;
  projectionMatID = glGetUniformLocation(_program, (const GLchar*)proMat);
  viewMatID = glGetUniformLocation(_program, (const GLchar*)viewMat);
  
  LOG_DEBUG("ID: %i %i\n", projectionMatID, viewMatID); 

  //globalCamera.setOrthographicProjectionMatrix();
  projection = globalCamera.getProjectionMatrix();
  
  LOG_DEBUG("matrix:\n%s", projection.output().c_str());

  glUniformMatrix4fv(projectionMatID, 1, GL_FALSE, (GLfloat *)projection.m);   
  glUniformMatrix4fv(viewMatID, 1, GL_FALSE, (GLfloat *)view.m);   
   
  checkGLError(__FUNCTION__);
}


std::vector<GLfloat> drawAxis() {

  GLfloat a[27] = {
                      1,0,0,0,0,0,100,0,0,
                      0,1,0,0,0,0,0,100,0,
                      0,0,1,0,0,0,0,0,100
                  };
  std::vector<GLfloat> axis(a,a + sizeof(a)); 
  return axis; 
}


std::vector<GLfloat> testTriangle() {
  GLfloat t[9] = {
                    1,0,101,
                    0,1,101,
                    0,0,101
                 };
  std::vector<GLfloat> triangle(t,t + sizeof(t));
  return triangle;
}


void GraphicsContext::setupArrays() {
  
  vertexID = glGetAttribLocation(_program,"position\0");
  vao.generateArray();
  testTriangleVao.generateArray();

  std::vector<GLfloat> axis = drawAxis();
  std::vector<GLfloat> triangle = testTriangle();

  //vao.addArrayPointer(vertexID, axis);
  testTriangleVao.addArrayPointer(vertexID, triangle);

  checkGLError(__FUNCTION__);
}


void GraphicsContext::setupBuffers() {
  
  setupUniforms();
 
  setupArrays();
  
  checkGLError(__FUNCTION__);
}


bool GraphicsContext::initGraphicsContext() {
   
  _program = glCreateProgram();

  setupShaders();
  glAttachShader(_program, _vertexShader);
  glAttachShader(_program, _fragmentShader);
   
  linkProgram();
  
  glUseProgram(_program);  
    
  setupBuffers();
  
  printShaderInfoLog(_vertexShader);
  printShaderInfoLog(_fragmentShader);

  return checkGLError(__FUNCTION__);
}


std::string GraphicsContext::getShaderSourceCode(const std::string& filename) {
  
  std::ifstream file (filename.c_str());
 
  LOG_DEBUG("opening file: %s\n", filename.c_str());
  
  if (!file) {
    LOG_DEBUG("Opening file failed\n"); 
  }

  std::stringstream shaderData;
  shaderData << file.rdbuf();
   
  file.close();
  return shaderData.str();
}


//TODO: Setup process to load textures
bool loadMedia() {return true;}


void output(int x,int y, float r, float g, float b, char string[]) {
 
  glColor3f (r,g,b);
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


void CLOutPosition() {
  char* str;
  std::string p;
  std::stringstream out;
  out << "POSITION X: " << " Y: " << " Z: ";
  p = out.str();
  str = (char*)(p.c_str());
  printf(p.c_str()); 
}


void render() {
  
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
 
  for (unsigned i = 0; i < 4; i++) {
   pfRender(holder[i]);
  } 
  
  outPosition();
  CLOutPosition();
  glBindVertexArray(testTriangleVao.ID);
  glDrawArrays(GL_TRIANGLES,0,1);

  glutSwapBuffers();
  checkGLError(__FUNCTION__);
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
    LOG_DEBUG("issues initializing GLEW: %s\n", glewGetErrorString(err) );
    return false; 
  }
  
  // INITIALIZE OPENGL AND LOADMEDIA
  if (!initGraphicsContext()) {
    LOG_DEBUG("Cannot initialize OpenGL!");
    return false; 
  } 
  if (!loadMedia()) LOG_DEBUG("Cannot load media!\n"); 
  
  glutKeyboardFunc(handleKeys);
  glutMotionFunc(handleMouseMovement);
  glutMouseFunc(handleMouseClick); 
  glutDisplayFunc(render);
  glutTimerFunc(1000 / SCREEN_FPS,runMainLoop,0);
  glutMainLoop();

  return true;
}
