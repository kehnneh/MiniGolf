#include "Tile.h"
#include "CommonUtils.h"
#include "Ball.h"

#include <glm\glm.hpp>

#include <glm\gtc\matrix_inverse.hpp>

unsigned char Tile::ComputeXZPlane(glm::vec3 const & up)
{
  glm::vec3 n = _surface->GetMesh()->NormalData().at(0);

  if (n == up)
  {
    _xaxis = new glm::vec3(1.f, 0.f, 0.f);
    _zaxis = new glm::vec3(0.f, 0.f, 1.f);
    return STATUS_OK;
  }

  _xaxis = new glm::vec3(glm::cross(n, up));
  _zaxis = new glm::vec3(glm::cross(n, *_xaxis));

  return STATUS_OK;
}

unsigned char Tile::Initialize()
{
  _tileBounds = new std::vector<Mesh*>;
  _tileWalls = new std::vector<Renderable*>;

  return STATUS_OK;
}

unsigned char Tile::DeInitialize()
{
  Delete(&_surface);
  Delete(&_neighbors);
  Delete(&_tileWalls);
  Delete(&_tileBounds);
  Delete(&_xaxis);
  Delete(&_zaxis);

  return STATUS_OK;
}

unsigned char Tile::SetRenderable(Renderable *renderable)
{
  _surface = renderable;

  return STATUS_OK;
}

unsigned char Tile::SetNeighbors(std::vector<Tile*> *neighbors)
{
  _neighbors = neighbors;

  return STATUS_OK;
}

unsigned char Tile::PostLoad()
{
  // All created walls are going to be this color 
  Renderable::Color(glm::vec4(1.f, 0.f, 0.f, 1.f));

  std::vector<glm::vec3> vertices = _surface->GetMesh()->VertexData();

  unsigned int neighbors = _neighbors->size();
  for (unsigned int i = 0; i < neighbors; i++)
  {
    // Create the Mesh: we need it when either a physical or imaginary wall exists
    const glm::vec3 *vb1, *vb2;

    vb1 = &vertices.at(i);
    vb2 = &vertices.at(i + 1 == neighbors ? 0 : i + 1);

    Mesh *m = Mesh::VerticalQuad(*vb1, *vb2);
    m->PostLoad();

    if (_neighbors->at(i))
    {
      // If here, then another tile borders this tile on this particular edge. Imaginary wall, push and be done.
      _tileBounds->push_back(m);
      _tileWalls->push_back(0);
    }
    else
    {
      // If here, then no tile borders this tile on this particular edge. Real wall, create the Renderable, push, and be done.
      Renderable *r = new Renderable;
      r->Initialize();
      r->SetMesh(m);
      r->PostLoad();

      _tileBounds->push_back(0);
      _tileWalls->push_back(r);
    }
  }

  if (ComputeXZPlane(glm::vec3(0.f, 1.f, 0.f)) != STATUS_OK)
  {
    return 0x2;
  }

  return STATUS_OK;
}

std::vector<Renderable*> *Tile::RealWalls()
{
  return _tileWalls;
}

std::vector<Mesh*> *Tile::FakeWalls()
{
  return _tileBounds;
}

// Tick shouldn't do anything (yet)
unsigned char Tile::Tick(double t)
{

  return STATUS_OK;
}

unsigned char Tile::Render(Camera *camera, Shader *s)
{
  glUniformMatrix4fv(s->mat_modelTransform, 1, GL_FALSE, (GLfloat*) &glm::mat4());

  glm::mat3 normalMat = glm::inverseTranspose(glm::mat3(*camera->Matrix()));
	glUniformMatrix3fv(s->mat_normal, 1, GL_FALSE, (GLfloat*) &normalMat);

  std::vector<Renderable*>::iterator it = _tileWalls->begin(), end = _tileWalls->end();
  for (; it != end; ++it)
  {
    if (*it)
    {
      (*it)->Render();
    }
  }

  _surface->Render();

  return STATUS_OK;
}