#pragma once

#include "Camera.h"

/// An arcball camera, that is, a camera that rotates about a central point while always focusing on that point
class ArcballCamera : public Camera
{
protected:
  /// The specific method for calculating how the camera moves
	void ConstructMatrix();

  /// Rotates the camera along an X axis
	void RotateX();

  /// Rotates the camera along a Y axis
	void RotateY();

  /// Rotates the camera along a Z axis
	void RotateZ();

public:
	ArcballCamera()
	{}

	~ArcballCamera()
	{}

  /// Overrides the Camera's forward moving mechanism to move only the XZ plane
	void MoveForward(float distance);
};

