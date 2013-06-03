#include "Ball.h"

#include "Arrow.h"

#include "CommonUtils.h"
#include <glm\gtc\matrix_inverse.hpp>
#include <glm\gtx\rotate_vector.hpp>

unsigned char Ball::Initialize()
{
  _velocity = new glm::vec3(0.f, 0.f, 1.f);
  _transform = new MatrixObject;
  _transform->Init();

  Renderable::Color(glm::vec4(0.f, 1.f, 1.f, 1.f));
  _direction = new Arrow;
  _direction->Initialize();

  Renderable::Color(glm::vec4(1.f, 1.f, 1.f, 1.f));
  _renderable = new Renderable;
  _renderable->Initialize();
  _renderable->LoadFromFile("Models/golfball.obj");
  _renderable->PostLoad();

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

unsigned char DetectChange(glm::vec3 norm, glm::vec3 pos, float d)
{
  float p = glm::dot(norm, pos) + d;

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
  //*_velocit
}

float Ball::DetectCollision(glm::vec3 const & pos, glm::vec3 const & endPos, const Mesh *m, float dist)
{
  unsigned char pos_state, endPos_state;

  glm::vec3 norm = m->NormalData().at(0);
  float d = -glm::dot(m->VertexData().at(0), norm);

  pos_state = DetectChange(norm, pos + (-norm * dist), d);
  endPos_state = DetectChange(norm, endPos + (-norm * dist), d);

  // Orientation relative to the hyperplane described by the normal obtained!
  if (pos_state != endPos_state)
  {
    glm::vec3 ray = endPos - pos;
    ray = glm::normalize(ray);

    float timeToCollide = - (d + glm::dot(norm, pos)) / glm::dot(norm, ray);
    return timeToCollide;
    //t = - (d + D3DXVec3Dot(&vNormal, &pStart)) / D3DXVec3Dot(&vNormal, &ray);
  }

  return 0.f;
}

MatrixObject *Ball::Matrix()
{
  return _transform;
}

MatrixObject *Ball::DirectionMatrix()
{
  return _direction->Matrix();
}

unsigned char Ball::Tick(double t)
{
  _transform->Tick();

  _direction->Matrix()->Position(*_transform->Position());
  _direction->Tick(t);

  _speed -= 0.02f;

  if (_speed <= 0.f)
  {
    _speed = 0.f;
    return STATUS_OK;
  }

  // need to rotate _velocity to the Arrow's rotation
  //glm::vec3 direction = glm::rotateY(*_velocity, _direction->Matrix()->Rotation()->y);
  glm::vec3 direction = glm::normalize(glm::rotate(*_velocity, glm::degrees(_direction->Matrix()->Rotation()->y), _tile->Normal()));

  glm::vec3 pos = *_transform->Position();
  glm::vec3 endpos = *_transform->Position() + (((float) t * _speed) * direction);

  // COLLISION DETECTION! DID WE COLLIDE INTO ANOTHER TILE?
  std::vector<Mesh*> *fakeWalls = _tile->FakeWalls();
  //std::vector<Mesh*>::iterator fit = fakeWalls->begin(), fitend = fakeWalls->end();
  unsigned int numNeighbors = fakeWalls->size();
  for (unsigned int n = 0; n < numNeighbors; ++n)
  {
    Mesh *m = fakeWalls->at(n);
    if (m)
    {
      float timeElapsed = DetectCollision(pos, endpos, m, 0.f);
      if (timeElapsed > 0.f)
      {
        // we collided, find the new tile to move to, and update the position, and velocity
        _tile = _tile->Neighbor(n);
        //endpos = *_transform->Position() + ((timeElapsed * _speed) * direction);
        break;
      }
    }
  }

  _transform->Position(endpos);
  _direction->Matrix()->Position(endpos);

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