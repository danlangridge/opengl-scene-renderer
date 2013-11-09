#include <GameContext.h>

GameContext::GameContext()
  :_graphicsContext(),
   _userContext()
  {}

void GameContext::Input(unsigned char key) {
  this->_userContext->_input->handleInput(key);
}

void GameContext::InitGL(int argv, char* argc[]) {
  this->_graphicsContext->InitGLHelperLibraries(argv, argc);
}
