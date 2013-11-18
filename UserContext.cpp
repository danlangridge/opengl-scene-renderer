#include <UserContext.h>
#include <KeyInput.h>
#include <statics.h>

UserContext::UserContext()
 : _user(), 
   _camera(new Camera()), 
   _keyInput(new KeyInput()),
   _mouseInput(new MouseInput())
 {}

 
 void UserContext::Move(float x, float y, float z) {
  this->_camera->updatePosition(x,y,z);
 }


 Vector UserContext::getPosition() {
  return _camera->getPosition();
 }


 void UserContext::Fire() {
 }
