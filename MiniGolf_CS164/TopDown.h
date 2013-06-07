#pragma once

#include "Camera.h"

/// Defines a top-down camera that looks directly downwards upon the world
class TopDown : public Camera
{
protected:
  /// Initializes the matrix for the world
	void InitMatrix();

  /// Constructs the matrix according to updated data
	void ConstructMatrix();

  /// Rotates the camera along an X axis
	void RotateX();

  /// Rotates the camera along a Y axis
	void RotateY();

  /// Rotates the camera along a Z axis
	void RotateZ();

public:
	TopDown()
	{ _eye.y -= 3.f; _eye.z += 3.f; _pitch *= -1.f; }

	~TopDown()
	{}

  /// Moves the camera along its X axis
	void MoveLeft(float distance);
	//void MoveForward(float distance);
};

