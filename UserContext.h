#pragma once
#include <UserState.h>
#include <KeyInput.h>

enum {
    PLAYER,
    MENU,
    FREE_ROAM
};

class UserContext {
public:
  KeyInput*  _input; 
  UserState* _userState;

  UserContext();
};
