#pragma once
#include <Vector.h>
#include <Mat4.h>
#include <Object.h>

/**
 * An Object used to record visual images
 *
 */
class Camera : public Object {

public:

 Camera();

 /*
  * set the projection matrix used for calculating the view 
  */
 Mat4 getProjectionMatrix();
 void setProjectionMatrix(GLfloat near, GLfloat far, GLfloat fov);

private: 

 GLfloat _far;
 GLfloat _near;
 GLfloat _fov;
 GLfloat _focalPoint;
 Mat4 _projection;

};
