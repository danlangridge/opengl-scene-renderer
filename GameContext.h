#pragma once
#include <UserContext.h>
#include <GraphicsContext.h>

class GameContext {
public:

  GameContext();

  /** 
   * Passes Input to UserContext
   *
   */
  void Input(unsigned char key);
 
  /** 
   * Starts Initializes The Graphics Context
   *
   */
  void InitGL(int argv, char* argc[]);

protected:
  
  GraphicsContext* _graphicsContext; 
  UserContext* _userContext;

};
