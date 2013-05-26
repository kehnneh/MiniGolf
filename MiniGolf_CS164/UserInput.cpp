#include <gl\freeglut.h>

#include "MatrixObject.h"
#include "UserInput.h"
#include "Camera.h"

void UserInput::Init()
{
	memset(&m_keys, 0, 256 * sizeof(bool));
  memset(&m_specialKeys, 0, 256 * sizeof(bool));
}

void UserInput::DeInit()
{
	camera = 0;
  _ballDirection = 0;
}

void UserInput::PressKey(unsigned char key)
{
	m_keys[key] = true;
}

void UserInput::ReleaseKey(unsigned char key)
{
	m_keys[key] = false;
}

void UserInput::PressSpecialKey(unsigned char key)
{
  m_specialKeys[key] = true;
}

void UserInput::ReleaseSpecialKey(unsigned char key)
{
  m_specialKeys[key] = false;
}

bool UserInput::IsKeyPressed(unsigned char key)
{
	return m_keys[key];
}

void UserInput::BindCamera(Camera* c)
{
	camera = c;
}

void UserInput::BindDirection(MatrixObject *direction)
{
  _ballDirection = direction;
}

void UserInput::Tick(const double dt)
{
  float t = (float) dt;
	if (IsKeyPressed(27))
	{
		glutLeaveMainLoop();
	}
  // Camera controls
	else if (IsKeyPressed('q'))
	{
		camera->IncYaw(-1.f * _rotationSensitivity * t);
	}
	else if (IsKeyPressed('e'))
	{
		camera->IncYaw(1.f * _rotationSensitivity * t);
	}
	else if (IsKeyPressed('z'))
	{
		camera->IncPitch(-1.f * _rotationSensitivity * t);
	}
	else if (IsKeyPressed('x'))
	{
		camera->IncPitch(1.f * _rotationSensitivity * t);
	}
	else if (IsKeyPressed('a'))
	{
		camera->MoveLeft(-1.f * _movementSensitivity * t);
	}
	else if (IsKeyPressed('d'))
	{
		camera->MoveLeft(1.f * _movementSensitivity * t);
	}
	else if (IsKeyPressed('w'))
	{
		camera->MoveForward(1.f * _movementSensitivity * t);
	}
	else if (IsKeyPressed('s'))
	{
		camera->MoveForward(-1.f * _movementSensitivity * t);
	}
  // Ball Direction control
  else if (m_specialKeys[GLUT_KEY_LEFT])
  {
    _ballDirection->IncYaw(-1.f * _directionSensitivity * t);
  }
  else if (m_specialKeys[GLUT_KEY_RIGHT])
  {
    _ballDirection->IncYaw(1.f * _directionSensitivity * t);
  }
}