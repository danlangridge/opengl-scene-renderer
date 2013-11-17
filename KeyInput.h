#pragma once
#include <Input.h>
#include <UserContext.h>

class KeyInput : public Input
{
  public:
  void handleInput(unsigned char key, int x, int y);
};
