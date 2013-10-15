#pragma once
#include <Input.h>
#include <UserContext.h>

class KeyInput : public Input
{
  public:
  void handleInput(const unsigned char& key);
};
