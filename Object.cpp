#include <Object.h>
 
Object::Object()
 :_position(), _direction(), _angle(0), _rotationPower(16,16,16)
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


GLfloat* Object::getRotation() {
 GLfloat* quaternion = new GLfloat[4];
 quaternion[0] = _angle;
 quaternion[1] = _direction.x;
 quaternion[2] = _direction.y;
 quaternion[3] = _direction.z;
 return quaternion;
}


void Object::setRotation(GLfloat a, GLfloat x, GLfloat y, GLfloat z) {
 _angle = a;
 _direction.x = x;
 _direction.y = y;
 _direction.z = z;
}
 
 
void Object::rotateX() {
 _direction.x += _rotationPower.x;
}

 
void Object::rotateY() {
 _direction.y += _rotationPower.y;
}
 
 
void Object::rotateZ() {
 _direction.z += _rotationPower.z;
}

 
void Object::setRotationPower(GLfloat x, GLfloat y, GLfloat z) {
 _rotationPower.x = x;
 _rotationPower.y = y;
 _rotationPower.z = z;
}

 
Vector Object::getRotationPower() {
 return _rotationPower;
}
