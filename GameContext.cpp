#include <GameContext.h>

GameContext::GameContext()
  :_graphicsContext(new GraphicsContext()),
   _userContext(new UserContext())
  {}

UserContext* GameContext::getUserContext() {
  return _userContext;
}

void GameContext::KeyInput(unsigned char key) {
  this->_userContext->_keyInput->handleInput(key);
}

void GameContext::MouseInput(int x, int y) {
  this->_userContext->_mouseInput->handleMouse(x,y);
}

void GameContext::InitGL(int argv, char* argc[]) {
  this->_graphicsContext->InitGLHelperLibraries(argv, argc);
}
