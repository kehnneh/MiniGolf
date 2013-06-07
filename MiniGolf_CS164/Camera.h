#pragma once

#include <glm\glm.hpp>
//#include <vector>

class Camera
{
protected:
	bool _bMatrixUpdate;

	// Static constants need to be defined in the class's source file.
	// See Camera.cpp for initialization.
	// These particular values will *never* change. They are relative to the World.
	static const glm::vec3 _origin, _xaxis, _yaxis, _zaxis;

	// This is the direction which the Camera faces after InitMatrix() is called
	glm::vec3 _direction;

	// The matrix field will end up looking like the following matrix.
	// X.x Y.x Z.x  0
	// X.y Y.y Z.y  0
	// X.z Y.z Z.z  0
	//  0   0   0   1
	glm::mat4 *_mat;

	// Camera position information
	glm::vec3 _eye, _target, _up;

	// Camera rotation information. TODO: consider using quaternions with this data! :)
	float _pitch, _yaw, _roll;

	// Sets up the Camera's pipeline of instructions. Typically this is something like the following:
	// - Default matrix initializaion
	// - Rotation (typically in XYZ order)
	// - Translation to point of interest
	// - Move the camera back, as if in Third Person
	virtual void ConstructMatrix() = 0;

	// TopDownCamera::InitMatrix will need to override this such that _up and _direction are different
	virtual void InitMatrix();

	void ThirdPerson();
	void TranslateToTarget();
	void TranslateToEye();

	// Leave implementation up to the type of camera
	virtual void RotateX() = 0;
	virtual void RotateY() = 0;
	virtual void RotateZ() = 0;

public:
	Camera()
		: _pitch(-45.f), _yaw(0.f), _roll(0.f),
	      _bMatrixUpdate(true),
	      _direction(0.f, 0.f, 1.f),
	      _eye(0.f, 0.f, 0.f), _target(0.f, 0.f, 0.f), _up(0.f, 1.f, 0.f)
	{}
	virtual ~Camera()
	{}

	void Init();
	void DeInit();

	void IncYaw(float degrees);
	void IncPitch(float degrees);
	void IncRoll(float degrees);

  void SetTarget(glm::vec3 target);

	virtual void MoveForward(float distance);
	virtual void MoveLeft(float distance);
	virtual void MoveUp(float distance);

	void TranslateX(float distance);
	void TranslateY(float distance);
	void TranslateZ(float distance);

	void Tick();

	glm::mat4 const * const Matrix();
	glm::vec3 const * const GetPosition();
};

