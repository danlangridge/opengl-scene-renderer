#include <MouseInput.h>
#include <Vector.h>
#include <Quaternion.h>

MouseInput::MouseInput() {
}

void MouseInput::handleMouseMovement(int x, int y)  {
  
  Vector v(x,y,0);
  v.normalize();
}

void MouseInput::handleMouseClick(int button, int state, int x, int y) {
}
