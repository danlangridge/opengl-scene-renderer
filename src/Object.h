#include <Vector.h>
#include <Quaternion.h>

/**
 * Generic class for physical objects within the world
 */
class Object {

public:
 
 Object(); 
 Object(Vector position, Vector orientation); 
 
 void setPosition(GLfloat x, GLfloat y, GLfloat z);

 // Adds position values to current position vector
 void updatePosition(GLfloat x, GLfloat y, GLfloat z);
 
 Vector getPosition();

 Quaternion getRotation();

 void setRotation(GLfloat a, GLfloat x, GLfloat y, GLfloat z);
 
 void rotateX();
 void rotateY();
 void rotateZ();

 void setRotationPower(GLfloat x, GLfloat y, GLfloat z);

 Vector getRotationPower(); 

private:
 // Position of the Object in the world
 Vector _position;
 
 Quaternion _orientation;

 Vector _rotationPower;

};
