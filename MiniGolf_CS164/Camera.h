#pragma once

#include <glm\glm.hpp>
//#include <vector>

/// Defines a viewpoint from which the User will look into the world
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
  /// Initializes the matrix
	virtual void InitMatrix();

  /// Sets the camera to look into the world as if it was a third person camera
	void ThirdPerson();

  /// Moves the camera to its target
	void TranslateToTarget();

  /// Moves the camera to its final position
	void TranslateToEye();

	// Leave implementation up to the type of camera
  /// Rotates the camera along an X axis
	virtual void RotateX() = 0;
	
  /// Rotates the camera along a Y axis
  virtual void RotateY() = 0;
	
  /// Rotates the camera along a Z axis
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

  /// Performs data allocation
	void Init();

  /// Performs data deallocation
	void DeInit();

  /// Increments the Yaw angle of the Camera
	void IncYaw(float degrees);

  /// Increments the Pitch angle of the Camera
	void IncPitch(float degrees);

  /// Increments the Roll angle of the Camera
	void IncRoll(float degrees);

  /// Sets the target that the camera will attempt to look at
  void SetTarget(glm::vec3 target);

  /// Moves the camera forward along its Z axis
	virtual void MoveForward(float distance);

  /// Moves the camera along its X axis
	virtual void MoveLeft(float distance);

  /// Moves the camera along its Y axis
	virtual void MoveUp(float distance);

  /// Moves the camera along the world's X axis
	void TranslateX(float distance);

  /// Moves the camera along the world's Y axis
	void TranslateY(float distance);

  /// Moves the camera along the world's Z axis
	void TranslateZ(float distance);

  /// Updates the camera's matrix data
	void Tick();

  /// Returns a pointer to the camera's matrix
	glm::mat4 const * const Matrix();

  /// Returns a pointer to the camera's position
	glm::vec3 const * const GetPosition();
};

