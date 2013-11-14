#include <Vector.h>
#include <Object.h>

/**
 * An Object used to record visual images
 *
 */
class Camera : public Object {

public:

 Camera();

private: 

 uint _height;
 uint _width;
 GLfloat _focalPoint;

};
