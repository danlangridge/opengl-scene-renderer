#pragma once
#include <Input.h>


class MouseInput : public Input {
public:
 MouseInput();
 void handleInput(const unsigned char& key);
 void handleMouse(int x, int y); 

};
