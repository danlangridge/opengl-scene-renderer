#pragma once
#include <Input.h>


class MouseInput : public Input {
public:
 MouseInput();
 void handleMouseMovement(int x, int y); 
 void handleMouseClick(int button, int state, int x, int y);
};
