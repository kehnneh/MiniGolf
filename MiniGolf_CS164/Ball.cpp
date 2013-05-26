#include "Ball.h"

#include "Arrow.h"

#include "CommonUtils.h"
#include <glm\gtc\matrix_inverse.hpp>

unsigned char Ball::Initialize()
{
  _velocity = new glm::vec3;
  _transform = new MatrixObject;
  _transform->Init();

  Renderable::Color(glm::vec4(1.f, 1.f, 1.f, 1.f));
  _direction = new Arrow;
  _direction->Initialize();

  return STATUS_OK;
}

unsigned char Ball::DeInitialize()
{

  return STATUS_OK;
}

unsigned char Ball::CurrentTile(Tile* tile)
{
  _tile = tile;

  return STATUS_OK;
}

unsigned char Ball::SetRenderable(Renderable *renderable)
{
  _renderable = renderable;
  return STATUS_OK;
}

unsigned char DetectChange(glm::vec3 norm, glm::vec3 pos)
{
  float p = glm::dot(norm, pos);

  if (p > 0.f)
  {
    return 0x1; // in front
  }
  else if (p < 0.f)
  {
    return 0x2; // behind
  }

  return 0x4; // ON plane
}

void Ball::Hit(float power)
{
  _speed = power;
}

float Ball::DetectCollision(glm::vec3 const & pos, glm::vec3 const & endPos, const Mesh *m, float dist)
{
  unsigned char pos_state, endPos_state;

  glm::vec3 norm = m->NormalData().at(0);

  pos_state = DetectChange(norm, pos + (-norm * dist));
  endPos_state = DetectChange(norm, endPos + (-norm * dist));

  // If they are on different sides of the plane
  if (pos_state != endPos_state)
  {

  }

  return 0.f;
}

MatrixObject *Ball::Matrix()
{
  return _transform;
}

unsigned char Ball::Tick(double t)
{
  _transform->Tick();

  _direction->Matrix()->Position(*_transform->Position());

  if (_speed <= 0.f)
  {
    return STATUS_OK;
  }

  /*
  // calculate starting position and final position
  const glm::vec3 *pos = _transform->Position();
  const glm::vec3 end = *pos + (_speed * *_velocity);

  // Using these positions, is there a collision with any real walls?
  // Real wall collisions will happen before fake wall collisions
  // If a collision with a real wall existed, bounce off (recompute velocity, speed, start and final positions),
  // and reiterate this method with the remaining time left in the Tick
  std::vector<Renderable*> *realWalls = _tile->RealWalls();
  std::vector<Renderable*>::iterator rit = realWalls->begin(), ritend = realWalls->end();
  for (; rit != ritend; ++rit)
  {
    if (*rit)
    {
      float timeElapsed = DetectCollision(*pos, end, (*rit)->GetMesh(), _radius);
      if (timeElapsed < t)
      {
        // we collided, figure out how to update velocity and such
      }
    }
  }

  // If a collision with a fake wall existed, go through the fake wall, change velocity if the slope of the
  // next tile is different, adjust position if the slope is different, update tile reference to the new tile,
  // and reiterate t his method with the remaining time left in the Tick
  std::vector<Mesh*> *fakeWalls = _tile->FakeWalls();
  std::vector<Mesh*>::iterator fit = fakeWalls->begin(), fitend = fakeWalls->end();
  for (; fit != fitend; ++fit)
  {
    if (*fit)
    {
      float timeElapsed = DetectCollision(*pos, end, (*fit), 0.f);
      if (timeElapsed < t)
      {
        // we collided, find the new tile to move to, and update the position, and velocity
      }
    }
  }

  */

  /*
  const glm::vec3 *pos = _transform->Position();

  _transform->Position(*pos + (_speed * *_velocity));

  _speed -= 10.f * t;

  // Prevent speed from going below 0.
  if (_speed <= 0.f)
  {
    _speed = 0.f;
  }
  */

  return STATUS_OK;
}

unsigned char Ball::Render(Camera *camera, Shader *shader)
{
  glUniformMatrix4fv(shader->mat_modelTransform, 1, GL_FALSE, (GLfloat *) _transform->Matrix());

  glm::mat3 normalMat = glm::inverseTranspose(glm::mat3(*_transform->Matrix() * *camera->Matrix()));
	glUniformMatrix3fv(shader->mat_normal, 1, GL_FALSE, (GLfloat*) &normalMat);

  _renderable->Render();
  _direction->Render(camera, shader);

  return STATUS_OK;
}

float Ball::Radius()
{
  return _radius;
}