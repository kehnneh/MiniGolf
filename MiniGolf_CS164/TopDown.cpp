#include "TopDown.h"

#include <glm\gtx\transform.hpp>

// This is probably the good general case that can be used in Arcball. Might test later
void TopDown::InitMatrix()
{
	*_mat = glm::lookAt(_up * 6.f, _direction * _eye * 2.f, _up * 2.f);
}

void TopDown::RotateX()
{
	*_mat = glm::rotate(_pitch, _xaxis) * *_mat;
}

void TopDown::RotateY()
{
	*_mat = glm::rotate(_yaw, _yaxis) * *_mat;
}

void TopDown::RotateZ()
{
	*_mat = glm::rotate(_roll, _zaxis) * *_mat;
}

// Translates along the Camera's x-axis
void TopDown::MoveLeft(float distance)
{
	_target.x -= (*_mat)[0].x * distance;
	//_target.y -= (*_mat)[1].x * distance;
	//_target.z -= (*_mat)[2].x * distance;

	//_eye.x -= (*_mat)[0].x * distance * 20.f;
	//_eye.y -= (*_mat)[1].x * distance;
	_eye.z -= (*_mat)[2].x * distance * 10.f;

	_bMatrixUpdate = true;
}

// 
// Here we want to rotate by Y, then by X. If we rotate by X first, the Y rotation
// will cause the camera to be rotated on its Y axis, not the world's, distorting the view.
//
void TopDown::ConstructMatrix()
{
	InitMatrix();
	RotateY();
	RotateX();
}