#pragma once

#include "Camera.h"

/// A freelook camera: it moves as if the user was in the Source engine's NoClip mode
class FreelookCamera : public Camera
{
protected:
  /// Initializes the matrix
	void InitMatrix();

  /// The specific method for updating the matrix
	void ConstructMatrix();

  /// Rotates the camera along an X axis
	void RotateX();

  /// Rotates the camera along a Y axis
	void RotateY();
	
  /// Rotates the camera along a Z axis
  void RotateZ();

public:
	FreelookCamera()
	{ _eye.y -= 3.f; _eye.z += 3.f; _pitch *= -1.f; }

	~FreelookCamera()
	{}

  /// Defines moving along the camera's X axis differently than the typical camera would
	void MoveLeft(float distance);
	//void MoveForward(float distance);
};

