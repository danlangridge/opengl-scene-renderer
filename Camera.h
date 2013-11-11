#include <Vector.h>


/**
 * An Object used to record visual images
 *
 */
class Camera : public Object {

public:
 Camera();

private: 

 // Normalized Vector describing the direction of viewing
 Vector _direction;

 uint _height;
 uint _width;
 uint _focalPoint;

};
