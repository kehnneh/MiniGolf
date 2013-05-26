#include "Arrow.h"
#include "CommonUtils.h"

#include "Renderable.h"
#include "Camera.h"
#include "Shader.h"
#include "MatrixObject.h"

#include <glm\gtc\matrix_inverse.hpp>

unsigned char Arrow::Initialize()
{
  _renderable = new Renderable;
  _renderable->Initialize();
  _renderable->LoadFromFile("Models/Arrow.obj");
  Renderable::Color(glm::vec4(.0f, 1.f, 1.f, 1.f));
  _renderable->PostLoad();

  Mesh *m = _renderable->GetMesh();

  unsigned int vertices = m->VertexData().size();
  std::vector<glm::vec3> *normals = new std::vector<glm::vec3>;
  for (unsigned int i = 0; i < vertices; i++)
  {
    normals->push_back(glm::vec3(0.f, 1.f, 0.f));
  }
  m->SetNormalData(normals);

  _transform = new MatrixObject;
  _transform->Init();

  return STATUS_OK;
}

unsigned char Arrow::DeInitialize()
{

  return STATUS_OK;
}

unsigned char Arrow::Tick(double t)
{
  _transform->Tick();

  return STATUS_OK;
}

unsigned char Arrow::Render(Camera *camera, Shader *shader)
{
  glUniformMatrix4fv(shader->mat_modelTransform, 1, GL_FALSE, (GLfloat*) _transform->Matrix());

  glm::mat3 normalMat = glm::inverseTranspose(glm::mat3(*_transform->Matrix() * *camera->Matrix()));
	glUniformMatrix3fv(shader->mat_normal, 1, GL_FALSE, (GLfloat*) &normalMat);

  _renderable->Render();

  return STATUS_OK;
}

MatrixObject *Arrow::Matrix()
{
  return _transform;
}