#pragma once
#include <Vector.h>

class PlayerState : public UserState {

public:
  PlayerState();

  Vector getPosition();
  void setPosition(const Vector& vector);
  void updatePosition(const Vector& vector);

protected:
  Vector _position;
  //TODO: Add Camera to PlayerState
};
