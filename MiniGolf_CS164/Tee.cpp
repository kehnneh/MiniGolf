#include "Tee.h"
#include "Shader.h"
#include "Camera.h"
#include "MatrixObject.h"
#include "Renderable.h"

#include "CommonUtils.h"

#include <glm\gtc\matrix_inverse.hpp>

unsigned char Tee::Initialize()
{
  _transform = new MatrixObject;
  _transform->Init();

  return STATUS_OK;
}

unsigned char Tee::DeInitialize()
{
  _transform->DeInit();

  return STATUS_OK;
}
  
void Tee::SetRenderable(Renderable *renderable)
{
  _renderable = renderable;
}

void Tee::SetMatrix(MatrixObject *m)
{
  _transform = m;
}

MatrixObject *Tee::GetMatrix()
{
  return _transform;
}

float Tee::GetRadius()
{
  return _radius;
}

void Tee::SetRadius(float radius)
{
  _radius = radius;
}

void Tee::SetGoal(bool goal)
{
  _goal = goal;
}

void Tee::Render(Camera *camera, Shader *shader)
{
  glUniformMatrix4fv(shader->mat_modelTransform, 1, GL_FALSE, (GLfloat*) _transform->Matrix());
  glm::mat3 normalMat = glm::inverseTranspose(glm::mat3(*_transform->Matrix() * *camera->Matrix()));
  glUniformMatrix3fv(shader->mat_normal, 1, GL_FALSE, (GLfloat*) &normalMat);

  _renderable->Render();
}

void Tee::SetTile(unsigned int id)
{
  _tileid = id;
}
  
unsigned int Tee::GetTile()
{
  return _tileid;
}

void Tee::Tick(double dt)
{
  _transform->Tick();
}