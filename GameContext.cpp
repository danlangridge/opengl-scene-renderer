#include <GameContext.h>

GameContext::GameContext()
  :_graphicsContext(new GraphicsContext()),
   _userContext(new UserContext())
  {}


UserContext* GameContext::getUserContext() {
  return _userContext;
}


void GameContext::InitGL(int argv, char* argc[]) {
  this->_graphicsContext->InitGLHelperLibraries(argv, argc);
}
