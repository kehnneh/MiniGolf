#include "NewTile.h"
#include "CommonUtils.h"

unsigned char NewTile::Initialize()
{
  _tileBounds = new std::vector<Mesh*>;
  _tileWalls = new std::vector<NewRenderable*>;

  return STATUS_OK;
}

unsigned char NewTile::DeInitialize()
{
  Delete(&_surface);
  Delete(&_neighbors);
  Delete(&_tileWalls);
  Delete(&_tileBounds);

  return STATUS_OK;
}

unsigned char NewTile::SetRenderable(NewRenderable *renderable)
{
  _surface = renderable;

  return STATUS_OK;
}

unsigned char NewTile::SetNeighbors(std::vector<NewTile*> *neighbors)
{
  _neighbors = neighbors;

  return STATUS_OK;
}

unsigned char NewTile::PostLoad()
{
  // All created walls are going to be this color 
  NewRenderable::Color(glm::vec4(1.f, 0.f, 0.f, 1.f));

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
      NewRenderable *r = new NewRenderable;
      r->Initialize();
      r->SetMesh(m);
      r->PostLoad();

      _tileBounds->push_back(0);
      _tileWalls->push_back(r);
    }
  }

  return STATUS_OK;
}

unsigned char NewTile::Tick(double t)
{
  _surface->Render();

  return STATUS_OK;
}