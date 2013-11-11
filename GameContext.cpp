#include <GameContext.h>

GameContext::GameContext()
  :_graphicsContext(new GraphicsContext()),
   _userContext(new UserContext())
  {}

void GameContext::Input(unsigned char key) {
  this->_userContext->_input->handleInput(key);
}

void GameContext::InitGL(int argv, char* argc[]) {
  this->_graphicsContext->InitGLHelperLibraries(argv, argc);
}
