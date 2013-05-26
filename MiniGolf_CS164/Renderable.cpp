#include "Renderable.h"
#include "Shader.h"

/// Utilities
#include "CommonUtils.h"

static Shader *__shader = 0;

static glm::vec4 _color(0.f, 0.f, 0.f, 0.f);

unsigned char Renderable::Initialize()
{
  _colorData = new std::vector<glm::vec4>;
  //_textureData = new std::vector<glm::vec2>;
  //_mesh = new Mesh;

  return STATUS_OK;
}

unsigned char Renderable::DeInitialize()
{
  Delete(&_mesh);
  //Delete(&_textureData);
  Delete(&_colorData);

  return STATUS_OK;
}

unsigned char Renderable::LoadFromFile(std::string filename)
{
  _mesh = new Mesh;
  _mesh->Initialize();

  if (_mesh->LoadFromFile(filename) != STATUS_OK)
  {
    return 0x2;
  }

  _mesh->PostLoad();

  return STATUS_OK;
}

unsigned char Renderable::PostLoad()
{
  if (GenerateColors() != STATUS_OK)
  {
    return 0x2;
  }

  return STATUS_OK;
}

unsigned char Renderable::GenerateColors()
{
  unsigned int vertices = _mesh->VertexData().size();
  for (unsigned int i = 0; i < vertices; i++)
  {
    _colorData->push_back(_color);
  }

  return STATUS_OK;
}

void Renderable::SetMesh(Mesh *m)
{
  _mesh = m;
}

unsigned char Renderable::Color(glm::vec4 const & color)
{
  _color = color;

  return STATUS_OK;
}

unsigned char Renderable::DrawMode(GLenum mode)
{
  _drawMode = mode;

  return STATUS_OK;
}

template <typename T>
void Renderable::BindBuffer
(
  GLenum target,
  GLuint buffer,
  std::vector<T> const & data,
  int size,
  GLenum usage,
  GLint attarr
)
{
  glBindBuffer(target, buffer);
  glBufferData(target, sizeof(float) * data.size() * size, data.data(), usage);
  
  if (attarr >= 0)
  {
    glEnableVertexAttribArray(attarr);
    glVertexAttribPointer(attarr, size, GL_FLOAT, GL_FALSE, 0, NULL);
  }
}

void Renderable::Render()
{
  BindBuffer(GL_ARRAY_BUFFER, __shader->vertexBuffer, _mesh->VertexData(), 3, GL_DYNAMIC_DRAW, __shader->vertex);
  BindBuffer(GL_ARRAY_BUFFER, __shader->normalBuffer, _mesh->NormalData(), 3, GL_DYNAMIC_DRAW, __shader->normal);
  BindBuffer(GL_ARRAY_BUFFER, __shader->colorBuffer, *_colorData, 4, GL_STATIC_DRAW, __shader->color);
  BindBuffer(GL_ELEMENT_ARRAY_BUFFER, __shader->indexBuffer, _mesh->IndexData(), 1, GL_STATIC_DRAW, -1);

  glDrawElements(_drawMode, _mesh->IndexData().size(), GL_UNSIGNED_INT, NULL);
}

void Renderable::UseShader(Shader* shader)
{
  __shader = shader;
}

Mesh const * Renderable::GetMesh() const
{
  return _mesh;
}

glm::vec4 const * Renderable::Color() const
{
  return &_colorData->at(0);
}