#include "Moveable.h"
#include "CommonUtils.h"

#include "MatrixObject.h"
#include "Tile.h"

// This could be a little more dynamic, if we stored the World's Up
// vector and used that as the direction in which gravity operates.
const glm::vec3 *Moveable::_gravity = new glm::vec3(0.f, -9.81f, 0.f);

void Moveable::Init()
{
  _velocity = new glm::vec3;
}

void Moveable::DeInit()
{
  Delete(&_velocity);
}

void Moveable::SetTile(Tile * t)
{
  _tile = t;
}

char DeterminePosition(glm::vec3 norm, glm::vec3 pos)
{
  float p = glm::dot(norm, pos);

  if (p > 0.f)
  {
    return 0x1;
  }
  else if (p < 0.f)
  {
    return 0x2;
  }

  return 0x4;
}

char Moveable::IsOnTile()
{
  const glm::vec3 *pos = transform->Position();
  glm::vec3 *norm = _tile->Normal();
  unsigned int numTries = _tile->TriangleCount();

  for (unsigned int i = 0; i < numTries; i++)
  {
    float d = -glm::dot(*_tile->FirstVertex(i), *norm);
    char posLoc = DeterminePosition(*norm, *pos),
         destLoc = DeterminePosition(*norm, *pos + (_speed * *_velocity));
  }

  return 0x0;
}

void Moveable::Tick(double t)
{
  // Will the object collide with any borders?
  // - Check real borders first:
  //   + Ball needs to bounce off of them
  // - Check imaginary borders second:
  //   + Readjust ball's velocity based on the new tile's slope
  if (IsOnTile())
  {

  }
  else
  {

  }
  
}

void Moveable::BindMatrix(MatrixObject *m)
{
  transform = m;
}

void Moveable::Impulse(float s)
{
  _speed = s;
}

const glm::vec3 *Moveable::Position() const
{
  return transform->Position();
}