#include <Object.h>
 
Object::Object()
 :_position(), _orientation(), _rotationPower(16,16,16)
{
}


Object::Object(Vector position)
 :_position(position), _orientation()
{
}


Object::Object(Quaternion orientation)
 :_position(), _orientation(orientation)
{
}


Object::Object(Vector position, Quaternion orientation)
 :_position(position), _orientation(orientation)
{
}


 void Object::setPosition(GLfloat x, GLfloat y, GLfloat z) {
 _position.x = x;
 _position.y = y;
 _position.z = z; 
}


void Object::updatePosition(GLfloat x, GLfloat y, GLfloat z) {
 _position.x += x;
 _position.y += y;
 _position.z += z;
}


Vector Object::getPosition() {
 return _position; 
}


Quaternion Object::getRotation() {
 return _orientation;
}


void Object::setRotation(GLfloat a, GLfloat x, GLfloat y, GLfloat z) {
 _orientation = Quaternion(a,x,y,z);
}
 

void Object::setRotationPower(GLfloat x, GLfloat y, GLfloat z) {
 _rotationPower.x = x;
 _rotationPower.y = y;
 _rotationPower.z = z;
}

 
Vector Object::getRotationPower() {
 return _rotationPower;
}
