#include <PlayerState.h>

PlayerState::PlayerState()
 : _position(Vector(0,0,0))
{}

Vector PlayerState::getPosition(){
  return _position;
}

void PlayerState::setPosition(const Vector& vector) {
  _position = vector;
}

void PlayerState::updatePosition(const Vector& vector) {
  _position += vector;
}
