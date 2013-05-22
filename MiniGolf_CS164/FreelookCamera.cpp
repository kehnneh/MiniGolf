#include "FreelookCamera.h"

#include <glm\gtx\transform.hpp>

// This is probably the good general case that can be used in Arcball. Might test later
void FreelookCamera::InitMatrix()
{
	*_mat = glm::lookAt(_origin - _eye, _direction - _eye, _up);
}

void FreelookCamera::RotateX()
{
	*_mat = glm::rotate(_pitch, _xaxis) * *_mat;
}

void FreelookCamera::RotateY()
{
	*_mat = glm::rotate(_yaw, _yaxis) * *_mat;
}

void FreelookCamera::RotateZ()
{
	*_mat = glm::rotate(_roll, _zaxis) * *_mat;
}

// Translates along the Camera's x-axis
void FreelookCamera::MoveLeft(float distance)
{
	_target.x -= (*_mat)[0].x * distance;
	_target.y -= (*_mat)[1].x * distance;
	_target.z -= (*_mat)[2].x * distance;

	_eye.x -= (*_mat)[0].x * distance;
	_eye.y -= (*_mat)[1].x * distance;
	_eye.z -= (*_mat)[2].x * distance;

	_bMatrixUpdate = true;
}

// 
// Here we want to rotate by Y, then by X. If we rotate by X first, the Y rotation
// will cause the camera to be rotated on its Y axis, not the world's, distorting the view.
//
void FreelookCamera::ConstructMatrix()
{
	InitMatrix();
	RotateY();
	RotateX();
}