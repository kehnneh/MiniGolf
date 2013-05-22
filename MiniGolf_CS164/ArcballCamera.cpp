#include "ArcballCamera.h"

#include <glm\gtc\matrix_transform.hpp>

void ArcballCamera::RotateX()
{
	*_mat = glm::rotate(*_mat, _pitch, _xaxis);
}

void ArcballCamera::RotateY()
{
	*_mat = glm::rotate(*_mat, _yaw, _yaxis);
}

void ArcballCamera::RotateZ()
{
	*_mat = glm::rotate(*_mat, _roll, _zaxis);
}

void ArcballCamera::MoveForward(float distance)
{
	_target.x += (*_mat)[0].z * distance;
	_target.z += (*_mat)[2].z * distance;

	_eye.x += (*_mat)[0].z * distance;
	_eye.z += (*_mat)[2].z * distance;

	_bMatrixUpdate = true;
}

void ArcballCamera::ConstructMatrix()
{
	InitMatrix();
	RotateX();
	RotateY();
	// No rolling around here
	// _pipeline.push_back(&Camera::RotateZ);
	TranslateToTarget();
	ThirdPerson();
}