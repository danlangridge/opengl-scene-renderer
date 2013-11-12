#include <UserContext.h>
#include <KeyInput.h>

UserContext::UserContext()
 : _userState(new UserState()), 
   _keyInput(new KeyInput()),
   _mouseInput(new MouseInput())
 {}

