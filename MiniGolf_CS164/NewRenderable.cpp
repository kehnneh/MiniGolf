#include "NewRenderable.h"
#include "Shader.h"

/// Utilities
#include "CommonUtils.h"

static Shader *__shader = 0;

static glm::vec4 _color(0.f, 0.f, 0.f, 0.f);

unsigned char NewRenderable::Initialize()
{
  _colorData = new std::vector<glm::vec4>;
  //_textureData = new std::vector<glm::vec2>;
  //_mesh = new Mesh;

  return STATUS_OK;
}

unsigned char NewRenderable::DeInitialize()
{
  Delete(&_mesh);
  //Delete(&_textureData);
  Delete(&_colorData);

  return STATUS_OK;
}

unsigned char NewRenderable::LoadFromFile(std::string filename)
{
  _mesh = new Mesh;
  _mesh->Initialize();

  if (_mesh->LoadFromFile(filename) != STATUS_OK)
  {
    return 0x2;
  }

  return STATUS_OK;
}

unsigned char NewRenderable::PostLoad()
{
  if (GenerateColors() != STATUS_OK)
  {
    return 0x2;
  }

  return STATUS_OK;
}

unsigned char NewRenderable::GenerateColors()
{
  unsigned int vertices = _mesh->VertexData().size();
  for (unsigned int i = 0; i < vertices; i++)
  {
    _colorData->push_back(_color);
  }

  return STATUS_OK;
}

void NewRenderable::SetMesh(Mesh *m)
{
  _mesh = m;
}

unsigned char NewRenderable::Color(glm::vec4 const & color)
{
  _color = color;

  return STATUS_OK;
}

unsigned char NewRenderable::DrawMode(GLenum mode)
{
  _drawMode = mode;

  return STATUS_OK;
}

template <typename T>
void NewRenderable::BindBuffer
(
  GLenum target,
  GLuint buffer,
  std::vector<T> const & data,
  GLenum usage,
  GLint attarr
)
{
  glBindBuffer(target, buffer);
  glBufferData(target, sizeof(float) * data.size() * sizeof(T), data.data(), usage);
  
  if (attarr > 0)
  {
    glEnableVertexAttribArray(attarr);
    glVertexAttribPointer(attarr, sizeof(T), GL_FLOAT, GL_FALSE, 0, NULL);
  }
}

void NewRenderable::Render()
{
  // I want to iterate over this even more genericly but I'm not sure that's a good idea right now
  BindBuffer(GL_ARRAY_BUFFER, __shader->vertexBuffer, _mesh->VertexData(), GL_DYNAMIC_DRAW, __shader->vertex);
  BindBuffer(GL_ARRAY_BUFFER, __shader->normalBuffer, _mesh->NormalData(), GL_DYNAMIC_DRAW, __shader->normal);
  BindBuffer(GL_ARRAY_BUFFER, __shader->colorBuffer, *_colorData, GL_STATIC_DRAW, __shader->color);
  BindBuffer(GL_ELEMENT_ARRAY_BUFFER, __shader->indexBuffer, _mesh->IndexData(), GL_STATIC_DRAW, 0);
}

void NewRenderable::UseShader(Shader* shader)
{
  __shader = shader;
}

Mesh const * NewRenderable::GetMesh() const
{
  return _mesh;
}

glm::vec4 const * NewRenderable::Color() const
{
  return &_colorData->at(0);
}