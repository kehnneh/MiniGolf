#include "Ball.h"

#include "Arrow.h"

#include "CommonUtils.h"
#include <glm\gtc\matrix_inverse.hpp>
#include <glm\gtx\rotate_vector.hpp>
#include <glm\gtx\projection.hpp>

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

bool Ball::Hit(float power)
{
  if (_speed > 0.f)
  {
    return false;
  }

  _speed = power;
  return true;
}

bool Ball::IsMoving()
{
  return _speed > 0.f;
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

    return - (d + glm::dot(norm, pos)) / glm::dot(norm, ray);
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

glm::vec3 ComputeSurfaceDirection(glm::vec3 velocity, float degy, glm::vec3 up, glm::vec3 norm)
{
  glm::vec3 xzd = glm::rotate(velocity, degy, up);
  glm::vec3 x = glm::cross(xzd, up);
  return glm::cross(norm, x);
}

bool Ball::HandleFakeCollision(float & t, glm::vec3 & pos, glm::vec3 & endpos, glm::vec3 & d, float dist)
{
  std::vector<Mesh*> *fakeWalls = _tile->FakeWalls();
  unsigned int numNeighbors = fakeWalls->size();
  for (unsigned int n = 0; n < numNeighbors; ++n)
  {
    Mesh *m = fakeWalls->at(n);
    if (m)
    {
      float timeElapsed = DetectCollision(pos, endpos, m, dist);
      if (timeElapsed > 0.f)
      {
        // we collided, find the new tile to move to, and update the position, and velocity
        _tile = _tile->Neighbor(n);
        //endpos = *_transform->Position() + (((timeElapsed + 0.005f) * _speed) * d);
        t -= (timeElapsed + 0.005f);
        return true;
      }
    }
  }

  // no collision was found
  return false;
}

bool Ball::HandleCollision(float & t, glm::vec3 & pos, glm::vec3 & endpos, glm::vec3 & d, float dist)
{
  std::vector<Renderable*> *walls = _tile->RealWalls();
  unsigned int numNeighbors = walls->size();
  for (unsigned int n = 0; n < numNeighbors; ++n)
  {
    if (walls->at(n))
    {
      Mesh *m = walls->at(n)->GetMesh();
      float timeElapsed = DetectCollision(pos, endpos, m, dist);
      if (timeElapsed > 0.f)
      {
        //w = m->NormalData().at(0);
        // we collided, find the new tile to move to, and update the position, and velocity
        //_tile = _tile->Neighbor(n);
        
        /*
        w = glm::proj(-d, m->NormalData().at(0));
        d = (2.f * w) + d;
        */
        //d *= -1.f;
        t -= (timeElapsed + 0.005f);
        if (t < 0.f) t *= -1.f;
        d *= -1.f;
        endpos = *_transform->Position() + (((t - 0.01f) * _speed) * d);
        return true;
      }
    }
  }

  // no collision was found
  return false;
}

void Ball::SetRadius(float r)
{
  _radius = r;
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

  float dt = (float) t;

  float degrees = _direction->Matrix()->Rotation()->y;//glm::degrees(_direction->Matrix()->Rotation()->y);
  glm::vec3 normal = _tile->Normal();

  glm::vec3 d = ComputeSurfaceDirection(*_velocity, degrees, glm::vec3(0.f, 1.f, 0.f), normal);

  glm::vec3 pos = *_transform->Position();
  glm::vec3 endpos = *_transform->Position() + ((dt * _speed) * d);

  // COLLISION DETECTION! DID WE COLLIDE INTO ANOTHER TILE?
  while (HandleFakeCollision(dt, pos, endpos, d, 0.f))
  {
    pos = endpos;
    // recompute d
    d = ComputeSurfaceDirection(*_velocity, glm::degrees(_direction->Matrix()->Rotation()->y), glm::vec3(0.f, 1.f, 0.f), _tile->Normal());
    endpos = pos + ((dt * _speed) * d);
  }

  while (HandleCollision(dt, pos, endpos, d, 0.0f))
  {
    pos = endpos;
    // recompute d
    //w = glm::proj(-d, w);
    //d = (w * 2.f) + d;
    //d *= -1.f;
    endpos = pos + ((dt * _speed) * d);
  }
  
  _transform->Position(endpos);
  _direction->Matrix()->Position(endpos);

  return STATUS_OK;
}

unsigned char Ball::Render(Camera *camera, Shader *shader)
{
  glm::mat4 transform = glm::mat4_cast(*_transform->Matrix());

  glUniformMatrix4fv(shader->mat_modelTransform, 1, GL_FALSE, (GLfloat *) _transform->Matrix());

  glm::mat3 normalMat = glm::mat3(glm::inverse(glm::transpose(transform * *camera->Matrix())));
	glUniformMatrix3fv(shader->mat_normal, 1, GL_FALSE, (GLfloat*) &normalMat);

  _renderable->Render();

  if (_speed == 0.f)
  {
    _direction->Render(camera, shader);
  }

  return STATUS_OK;
}

float Ball::Radius()
{
  return _radius;
}