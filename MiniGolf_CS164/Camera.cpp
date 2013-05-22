#include "Camera.h"
#include "CommonUtils.h"

#include <glm\core\func_trigonometric.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtx\transform.hpp>

// Constant data initialization
const glm::vec3 Camera::_origin(0.f, 0.f, 0.f);
const glm::vec3 Camera::_xaxis(1.f, 0.f, 0.f);
const glm::vec3 Camera::_yaxis(0.f, 1.f, 0.f);
const glm::vec3 Camera::_zaxis(0.f, 0.f, 1.f);

static const float pitch_limit = 90.f;
static const float backup = -5.f;

// Performs memory allocation!
void Camera::Init()
{
	_mat = new glm::mat4;
}

void Camera::DeInit()
{
	SAFE_DELETE(_mat);
}

void Camera::InitMatrix() {	*_mat = glm::lookAt(_origin, _direction, _up); }

// Grab the Camera's z-axis vector and move negatively along it
void Camera::ThirdPerson() { *_mat = glm::translate(*_mat, (*_mat)[0].z * backup, (*_mat)[1].z * backup, (*_mat)[2].z * backup); }

// Translates the camera such that it is positioned at the fixed point
// Here, target is the fixed point to rotate about
void Camera::TranslateToTarget() { *_mat = glm::translate(*_mat, _target); }

void Camera::TranslateToEye() { *_mat = glm::translate(*_mat, _eye); }

// Get's called every time Kengine::Tick() is called
void Camera::Tick()
{
	if (_bMatrixUpdate)
	{
		ConstructMatrix();
		_bMatrixUpdate = false;
	}
}

// Increments the Yaw (Y-Rotation) by the specified amount in degrees, then
// flags the Camera matrix for updating
void Camera::IncYaw(float degrees)
{
	_yaw += degrees;

	if (_yaw > 360.f)
	{
		_yaw -= 360.f;
	}
	else if (_yaw < 0.f)
	{
		_yaw += 360.f;
	}

	_bMatrixUpdate = true;
}

// Increments the Pitch (X-Rotation) by the specified amount in degrees, then
// flags the Camera matrix for updating
void Camera::IncPitch(float degrees)
{
	_pitch += degrees;

	if (_pitch > pitch_limit)
	{
		_pitch = 89.9f;
	}
	else if (_pitch < -pitch_limit)
	{
		_pitch = -89.9f;
	}

	_bMatrixUpdate = true;
}

// Increments the Roll (Z-Rotation) by the specified amount in degrees, then
// flags the Camera matrix for updating
void Camera::IncRoll(float degrees)
{
	_roll += degrees;
	
	if (_roll > 360.f)
	{
		_roll -= 360.f;
	}
	else if (_roll < 0.f)
	{
		_roll += 360.f;
	}

	_bMatrixUpdate = true;
}

// Translates along the Camera's z-axis.
void Camera::MoveForward(float distance)
{
	_target.x += (*_mat)[0].z * distance;
	_target.y += (*_mat)[1].z * distance;
	_target.z += (*_mat)[2].z * distance;

	_eye.x += (*_mat)[0].z * distance;
	_eye.y += (*_mat)[1].z * distance;
	_eye.z += (*_mat)[2].z * distance;

	_bMatrixUpdate = true;
}

// Translates along the Camera's x-axis
void Camera::MoveLeft(float distance)
{
	_target.x += (*_mat)[0].x * distance;
	_target.y += (*_mat)[1].x * distance;
	_target.z += (*_mat)[2].x * distance;

	_eye.x += (*_mat)[0].x * distance;
	_eye.y += (*_mat)[1].x * distance;
	_eye.z += (*_mat)[2].x * distance;

	_bMatrixUpdate = true;
}

// Translates along the Camera's y-axis
void Camera::MoveUp(float distance)
{
	_target.x += (*_mat)[0].x * distance;
	_target.y += (*_mat)[1].x * distance;
	_target.z += (*_mat)[2].x * distance;

	_eye.x += (*_mat)[0].x * distance;
	_eye.y += (*_mat)[1].x * distance;
	_eye.z += (*_mat)[2].x * distance;

	_bMatrixUpdate = true;
}

// Translates along the World's x-axis.
void Camera::TranslateX(float distance)
{
	_target.x += distance;
	_eye.x += distance;

	_bMatrixUpdate = true;
}

// Translates along the World's y-Axis
void Camera::TranslateY(float distance)
{
	_target.y += distance;
	_eye.y += distance;

	_bMatrixUpdate = true;
}

// Translates along the World's z-axis
void Camera::TranslateZ(float distance)
{
	_target.z += distance;
	_eye.z += distance;

	_bMatrixUpdate = true;
}

glm::mat4 const * const Camera::Matrix() { return _mat; }

glm::vec3 const * const Camera::GetPosition() { return &_eye; }