#pragma once
#include <Object.h>

#include <Vector.h>
#include <Mat4.h>

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
 void setPerspectiveMatrix(GLfloat near, GLfloat far, GLfloat fov);
 void setOrthographicMatrix();
 void rotateTheta(GLfloat angle);
 void rotatePhi(GLfloat angle);

private: 

 GLfloat _far;
 GLfloat _near;
 GLfloat _fov;
 GLfloat _focalPoint;
 Mat4 _projection;

};
