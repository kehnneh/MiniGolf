#pragma once

#include <vector>
#include "NewRenderable.h"

class NewTile
{
private:
  // This is the renderable that is drawn for this tile.
  NewRenderable *_surface;

  std::vector<NewTile*> *_neighbors;

  // Collision boundaries between tiles
  std::vector<Mesh*> *_tileBounds;

  // Physical boundaries at the edge of the world
  //std::vector<TileWall*> *_tileWalls;

public:
  NewTile() :
    _surface(0),
    _neighbors(0),
    _tileBounds(0)
  {}

  ~NewTile()
  {}

  unsigned char Initialize();

  unsigned char DeInitialize();

  unsigned char Tick(double t);
};

