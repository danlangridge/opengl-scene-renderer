#pragma once
#include <UserContext.h>
#include <GraphicsContext.h>

class GameContext {
public:
  GraphicsContext* _graphicsContext; 
  UserContext* _userContext;
  
  GameContext();

};
