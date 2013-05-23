#include "NewRenderable.h"

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

Mesh const * NewRenderable::GetMesh() const
{
  return _mesh;
}

glm::vec4 const * NewRenderable::GetColor() const
{
  return _colorData;
}