#pragma once

#include "Camera.h"

class TopDown : public Camera
{
protected:
	void InitMatrix();

	void ConstructMatrix();

	void RotateX();
	void RotateY();
	void RotateZ();

public:
	TopDown()
	{ _eye.y -= 3.f; _eye.z += 3.f; _pitch *= -1.f; }
	~TopDown()
	{}

	void MoveLeft(float distance);
	//void MoveForward(float distance);
};

