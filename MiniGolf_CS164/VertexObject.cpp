#include "VertexObject.h"

#include "CommonUtils.h"

#include <glm\gtc\quaternion.hpp>
#include <glm\gtx\rotate_vector.hpp>

void VertexObject::Init()
{
  _vec = NewAligned<Vec4>(16);
  _vert = new glm::vec3;
}

void VertexObject::DeInit()
{
  Delete(&_vert);
  DeleteAligned(&_vec);
}

float VertexObject::Length() const
{
  //return glm::length(*_vert);
  return glm::length(*_vec);
}

void VertexObject::Normalize()
{
  *_vert = glm::normalize(*_vert);
}

void VertexObject::Rotate(float pitch, float yaw, float roll)
{
  *_vert = glm::mat3_cast(glm::quat(glm::vec3(pitch, yaw, roll))) * *_vert;
}

void VertexObject::Increment(float x, float y, float z)
{
  IncX(x);
  IncY(y);
  IncZ(z);
}

void VertexObject::IncX(float x)
{
  _vert->x += x;
}

void VertexObject::IncY(float y)
{
  _vert->y += y;
}

void VertexObject::IncZ(float z)
{
  _vert->z += z;
}

void VertexObject::Set(float x, float y, float z)
{
  _vert->x = x;
  _vert->y = y;
  _vert->z = z;
}

const glm::vec3 *VertexObject::Vertex() const
{
  return _vert;
}