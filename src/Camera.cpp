#include <Camera.h>
#include <math.h>
#include <statics.h>

#include <Conversion.h>


Camera::Camera() 
 : _far(CLIPPING_DEPTH_MAX),
   _near(CLIPPING_DEPTH_MIN),
   _fov(90),
   _focalPoint(0)
{
  setPerspectiveMatrix(_near,_far,_fov);
}


Mat4 Camera::getProjectionMatrix() {
  return _projection;
}


void Camera::setPerspectiveMatrix(GLfloat near, GLfloat far, GLfloat fov) {
 
 _near = near;
 _far = far;
 _fov = fov;

 GLfloat s = 1/tan(_fov*0.5*PI/180);
 GLfloat p = -_far/(_far-_near);
 GLfloat mat[16] = {s,0,0,0,0,s,0,0,0,0,p,p*_near,0,0,-1,0};
 _projection = Mat4(mat);  
}


void Camera::setOrthographicMatrix() {
  GLfloat mat[16] = {1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1};
  _projection = Mat4(mat);
}


void Camera::rotateTheta(GLfloat angle) {
  GLfloat m[16] = { 1, 0, 0, 0,
                    0, cos(angle), 1, 0,
                    0, -sin(angle) - 1, 0
                  };
  Mat4 mat(m);

  Mat4 orientMatrix = Conversion::QuaternionToMat4(_orientation);
  _orientation = Conversion::Mat4ToQuaternion(mat*orientMatrix);
}


void Camera::rotatePhi(GLfloat angle) { 
  GLfloat m[16] = { cos(angle), sin(angle), 0, 0, 
                    -sin(angle), cos(angle), 0, 0,
                    0, 0, 1, 0
                  };
  Mat4 mat(m);

  Mat4 orientMatrix = Conversion::QuaternionToMat4(_orientation);
  _orientation = Conversion::Mat4ToQuaternion(mat*orientMatrix);
}
