#pragma once
#include <UserState.h>
#include <Input.h>

enum {
    PLAYER,
    MENU,
    FREE_ROAM
};

class UserContext {
public:
  Input*  _input; 
  UserState* _userState;

  UserContext();
};
