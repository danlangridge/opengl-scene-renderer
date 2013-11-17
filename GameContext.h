#pragma once
#include <UserContext.h>
#include <GraphicsContext.h>
#include <PhysicsContext.h>

class GameContext {
public:

  GameContext();

  /** 
   * Passes Input to UserContext
   *
   */
  void KeyInput(unsigned char key, int x, int y);
  void MouseInput(int x, int y);
 
  /** 
   * Starts Initializes The Graphics Context
   *
   */
  void InitGL(int argv, char* argc[]);

  UserContext* getUserContext();

protected:
  
  GraphicsContext* _graphicsContext; 
  PhysicsContext* _physicsContext;
  UserContext* _userContext;
};
