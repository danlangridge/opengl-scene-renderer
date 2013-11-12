#include <Vector.h>

/**
 * Generic class for physical objects within the world
 */
class Object {

public:
 
 Object(); 
 
 void setPosition(GLfloat x, GLfloat y, GLfloat z);

 // Adds position values to current position vector
 void updatePosition(GLfloat x, GLfloat y, GLfloat z);
 
 Vector getPosition();

 GLfloat* getRotation();

 void setRotation(GLfloat a, GLfloat x, GLfloat y, GLfloat z);
 
 void rotateX();
 void rotateY();
 void rotateZ();

 void setRotationPower(GLfloat x, GLfloat y, GLfloat z);

 Vector getRotationPower(); 

private:
 // Position of the Object in the world
 Vector _position;
 
 // Normalized Vector describing the direction of viewing
 // TODO: Make a Quaternion class to handle rotations 
 Vector _direction;
 GLfloat _angle;
 
 Vector _rotationPower;

};
