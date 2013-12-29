#pragma once
#include <User.h>
#include <KeyInput.h>
#include <MouseInput.h>
#include <Camera.h>

enum {
    PLAYER,
    MENU,
    FREE_ROAM
};

class UserContext {

public:

  UserContext();
  
  double _id; 
  
  User* _user;
  
  Camera* _camera;
  
  KeyInput*  _keyInput; 
  
  MouseInput*  _mouseInput; 

 /*
  * Move function, defines movement of all objects associated with user i.e. Camera, Model etc
  */
 void Move(float x, float y, float z);
 
 Vector getPosition();
  
};
