#include "NewRenderable.h"
#include "Shader.h"

static Shader *__shader = 0;

unsigned char NewRenderable::Initialize()
{
  _colorData = new glm::vec4;
  //_textureData = new std::vector<glm::vec2>;
  _mesh = new Mesh;

  return STATUS_OK;
}

unsigned char NewRenderable::DeInitialize()
{
  Delete(&_mesh);
  //Delete(&_textureData);
  Delete(&_colorData);

  return STATUS_OK;
}

unsigned char NewRenderable::PostLoad()
{
  return STATUS_OK;
}

unsigned char NewRenderable::Color(glm::vec4 const & color)
{
  *_colorData = color;

  return STATUS_OK;
}

unsigned char NewRenderable::DrawMode(GLenum mode)
{
  _drawMode = mode;

  return STATUS_OK;
}

void NewRenderable::BindBuffer
(
  GLenum target,
  GLuint buffer,
  std::vector<glm::vec3> const & data,
  GLenum usage,
  GLint attarr,
  bool const & vertAttrib
)
{
  glBindBuffer(target, buffer);
  glBufferData(target, sizeof(float) * data.size() * sizeof(glm::vec3), data.data(), usage);
  
  if (vertAttrib)
  {
    glEnableVertexAttribArray(attarr);
    glVertexAttribPointer(attarr, sizeof(glm::vec3), GL_FLOAT, GL_FALSE, 0, NULL);
  }
}

void NewRenderable::Render()
{
  BindBuffer(GL_ARRAY_BUFFER, __shader->vertexBuffer, _mesh->VertexData(), GL_DYNAMIC_DRAW, __shader->vertex, true);
  BindBuffer(GL_ARRAY_BUFFER, __shader->normalBuffer, _mesh->NormalData(), GL_DYNAMIC_DRAW, __shader->normal, true);
  //BindBuffer(GL_ARRAY_BUFFER, __shader->colorBuffer, *_colorData, GL_STATIC_DRAW
}

Mesh const * NewRenderable::GetMesh() const
{
  return _mesh;
}

glm::vec4 const * NewRenderable::GetColor() const
{
  return _colorData;
}