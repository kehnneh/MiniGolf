#pragma once

#include <glm\glm.hpp>

class MatrixObject
{
private:
  glm::mat4 *_mat, *_rotmat, *_posmat;
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

  void Init();
  void DeInit();

  void Tick();

  // Rotation getter
  const glm::vec3 *Rotation() const;

  // Rotation setters
  void Rotation(float pitch, float yaw, float roll);
  void Rotation(glm::vec3 rot);
  
  // Rotation incrementers
  void IncPitch(float degrees);
  void IncYaw(float degrees);
  void IncRoll(float degrees);

  // Position getter
  const glm::vec3 *Position() const;

  // Position setters
  void Position(float x, float y, float z);
  void Position(glm::vec3 pos);

  // Position incrementers
  void IncX(float x);
  void IncY(float y);
  void IncZ(float z);
  
  // Relative position incrementers
  void MoveForward(float dist);
  void MoveRight(float dist);
  void MoveUp(float dist);

  // Scale getter
  const glm::vec3 *Scale() const;

  // Scalar setters
  void Scale(float uniform);
  void Scale(float x, float y, float z);

  // Scalar incrementers
  void IncScale(float uniform);
  void IncScale(float x, float y, float z);

  // Matrix getter
  const glm::mat4 *Matrix() const;
};

