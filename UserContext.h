#pragma once
#include <UserState.h>
#include <KeyInput.h>
#include <MouseInput.h>

enum {
    PLAYER,
    MENU,
    FREE_ROAM
};

class UserContext {
public:
  UserState* _userState;
  KeyInput*  _keyInput; 
  MouseInput*  _mouseInput; 

  UserContext();
};
