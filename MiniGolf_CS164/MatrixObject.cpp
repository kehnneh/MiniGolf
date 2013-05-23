#include "MatrixObject.h"

#include "CommonUtils.h"
#include <glm\gtx\transform.hpp>
#include <glm\gtc\quaternion.hpp>

#define UPDATE_ROTATION 0x1
#define UPDATE_POSITION 0x2
#define UPDATE_SCALE    0x4

void MatrixObject::Init()
{
  _mat = new glm::mat4;
  _posmat = new glm::mat4;
  _rotmat = new glm::mat4;
  _pos = new glm::vec3;
  _rot = new glm::vec3;
  _scale = new glm::vec3(1.f, 1.f, 1.f);
}

void MatrixObject::DeInit()
{
  Delete(&_scale);
  Delete(&_rot);
  Delete(&_pos);
  Delete(&_rotmat);
  Delete(&_posmat);
  Delete(&_mat);
}

void IncrementDegreesWrap(float& val, float degrees, float limit)
{
  val += degrees;

  if (val > limit)
  {
    val -= limit;
  }
  else if (val < 0.f)
  {
    val += limit;
  }
}

void IncrementDegrees(float& val, float degrees, float limit)
{
  val += degrees;

  if (val > limit)
  {
    val = limit - 0.1f;
  }
  else if (val < -limit)
  {
    val = 0.1f - limit;
  }
}

const glm::vec3 *MatrixObject::Rotation() const
{
  return _rot;
}

void MatrixObject::Rotation(float pitch, float yaw, float roll)
{
  _rot->x = pitch;
  _rot->y = yaw;
  _rot->z = roll;
  _updateFlags |= UPDATE_ROTATION;
}

void MatrixObject::Rotation(glm::vec3 rot)
{
  *_rot = rot;
  _updateFlags |= UPDATE_ROTATION;
}

void MatrixObject::IncPitch(float degrees)
{
  // If this matrix is for a camera, prevent wrapping there
	// IncrementDegrees(_rot->x, degrees, 90.f);
  IncrementDegreesWrap(_rot->x, degrees, 360.f);
	_updateFlags |= UPDATE_ROTATION;
}

void MatrixObject::IncYaw(float degrees)
{
  IncrementDegreesWrap(_rot->y, degrees, 360.f);
	_updateFlags |= UPDATE_ROTATION;
}

void MatrixObject::IncRoll(float degrees)
{
  IncrementDegreesWrap(_rot->z, degrees, 360.f);
	_updateFlags |= UPDATE_ROTATION;
}

const glm::vec3 *MatrixObject::Position() const
{
  return _pos;
}

void MatrixObject::Position(float x, float y, float z)
{
  _pos->x = x;
  _pos->y = y;
  _pos->z = z;
  _updateFlags |= UPDATE_POSITION;
}

void MatrixObject::Position(glm::vec3 pos)
{
  *_pos = pos;
  _updateFlags |= UPDATE_POSITION;
}

void MatrixObject::IncX(float x)
{
  _pos->x += x;
  _updateFlags |= UPDATE_POSITION;
}

void MatrixObject::IncY(float y)
{
  _pos->y += y;
  _updateFlags |= UPDATE_POSITION;
}

void MatrixObject::IncZ(float z)
{
  _pos->z += z;
  _updateFlags |= UPDATE_POSITION;
}

void MatrixObject::MoveForward(float dist)
{
  _pos->x += (*_mat)[0].z * dist;
  _pos->y += (*_mat)[1].z * dist;
  _pos->z += (*_mat)[2].z * dist;
  _updateFlags |= UPDATE_POSITION;
}

void MatrixObject::MoveRight(float dist)
{
  _pos->x += (*_mat)[0].x * dist;
  _pos->y += (*_mat)[1].x * dist;
  _pos->z += (*_mat)[2].x * dist;
  _updateFlags |= UPDATE_POSITION;
}

void MatrixObject::MoveUp(float dist)
{
  _pos->x += (*_mat)[0].y * dist;
  _pos->y += (*_mat)[1].y * dist;
  _pos->z += (*_mat)[2].y * dist;
  _updateFlags |= UPDATE_POSITION;
}

const glm::vec3 *MatrixObject::Scale() const
{
  return _scale;
}

void MatrixObject::Scale(float uniform)
{
  if (uniform < 0.f)
  {
    return;
  }

  _scale->x = uniform;
  _scale->y = uniform;
  _scale->z = uniform;
  _updateFlags |= UPDATE_SCALE;
}

void MatrixObject::Scale(float x, float y, float z)
{
  if (x < 0.f || y < 0.f || z < 0.f)
  {
    return;
  }

  _scale->x = x;
  _scale->y = y;
  _scale->z = z;
  _updateFlags |= UPDATE_SCALE;
}

void MatrixObject::IncScale(float uniform)
{
  if (_scale->x + uniform < 0.f || _scale->y + uniform < 0.f || _scale->z + uniform < 0.f)
  {
    return;
  }

  _scale->x += uniform;
  _scale->y += uniform;
  _scale->z += uniform;
  _updateFlags |= UPDATE_SCALE;
}

void MatrixObject::IncScale(float x, float y, float z)
{
  if (_scale->x + x < 0.f || _scale->y + y < 0.f || _scale->z + z < 0.f)
  {
    return;
  }

  _scale->x += x;
  _scale->y += y;
  _scale->z += z;
  _updateFlags |= UPDATE_SCALE;
}

void MatrixObject::Tick()
{
  if (_updateFlags & UPDATE_ROTATION)
  {
    *_rotmat = glm::mat4_cast(glm::quat(*_rot));
  }

  if (_updateFlags & UPDATE_POSITION)
  {
    *_posmat = glm::translate(*_pos / *_scale);
  }

  if (_updateFlags)
  {
    *_mat = glm::scale(*_scale) * *_rotmat * *_posmat;
    _updateFlags = 0x0;
  }
}

const glm::mat4 *MatrixObject::Matrix() const
{
  return _mat;
}