#include <UserContext.h>
#include <KeyInput.h>

UserContext::UserContext()
 :_input(new KeyInput()), _userState(new UserState())
 {}

