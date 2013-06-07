#pragma once

#include <glm\glm.hpp>

#define _SIMD_OPS_MAT

#ifdef _SIMD_OPS_MAT
  #define GLM_SIMD_ENABLE_XYZW_UNION
  #include <glm\gtx\simd_mat4.hpp>
  #include <glm\gtx\simd_vec4.hpp>

  #include "AlignedAllocationPolicy.h"

  typedef glm::simdMat4 Mat4;
#else
  #include <glm\core\type_mat4x4.hpp>
  #include <glm\core\type_vec4.hpp>

  typedef glm::mat4x4 Mat4;
#endif

/// Matrix manipulation class. Supports both standard (slow) matrix operations as well as SIMD (fast) matrix operations.
#ifdef _SIMD_OPS_MAT
class MatrixObject : public AlignedAllocationPolicy<16>
#else
class MatrixObject
#endif
{
private:
  Mat4 *_mat, *_rotmat, *_posmat;
  glm::vec3 *_pos, *_rot, *_scale;

  // two-bit flag for updating _rotmat and _posmat
  unsigned char _updateFlags;

public:
	MatrixObject() :
      _mat(0), _posmat(0), _rotmat(0),
      _pos(0), _rot(0), _scale(0),
      _updateFlags(0x3)
	{}

	~MatrixObject()
	{}

  /// Performs data allocation
  void Init();

  /// Performs data deallocation
  void DeInit();

  /// Updates the Matrix if any changes have occurred since the last call to Tick()
  void Tick();

  /// Returns a pointer to the current rotation in degrees
  const glm::vec3 *Rotation() const;

  /// Sets the current rotation in degrees
  void Rotation(float pitch, float yaw, float roll);

  /// Sets the current rotation in degrees
  void Rotation(glm::vec3 rot);
  
  /// Increments the current Pitch by the specified amount
  void IncPitch(float degrees);

  /// Increments the current Yaw by the specified amount
  void IncYaw(float degrees);

  /// Increments the current Roll by the specified amount
  void IncRoll(float degrees);

  /// Returns a pointer to the current world Position
  const glm::vec3 *Position() const;

  /// Sets the position relative to the world
  void Position(float x, float y, float z);

  /// Sets the position relative to the world
  void Position(glm::vec3 pos);

  /// Increments the X component of the matrix's position
  void IncX(float x);

  /// Increments the Y component of the matrix's position
  void IncY(float y);

  /// Increments the Z component of the matrix's position
  void IncZ(float z);
  
  /// Increments the matrix's position by dist distance along its Z axis
  void MoveForward(float dist);

  /// Increments the matrix's position by dist distance along its X axis
  void MoveRight(float dist);

  /// Increments the matrix's position by dist distance along its Y axis
  void MoveUp(float dist);

  /// Returns a pointer to the current scale of the matrix
  const glm::vec3 *Scale() const;

  /// Uniformly sets the scale of the matrix
  void Scale(float uniform);

  /// Component-wise sets the scale of the matrix
  void Scale(float x, float y, float z);

  /// Uniformly increments the scale of the marix
  void IncScale(float uniform);

  /// Component-wise increments the scale of the matrix
  void IncScale(float x, float y, float z);

  /// Returns the matrix data
  Mat4 *Matrix();
};

