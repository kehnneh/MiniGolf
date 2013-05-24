#pragma once

#include <vector>
#include "NewRenderable.h"

class NewTile
{
private:
  // This is the renderable that is drawn for this tile.
  NewRenderable *_surface;

  std::vector<NewTile*> *_neighbors;

  // Collision boundaries between tiles. Check these to see if the Tile has entered another tile
  std::vector<Mesh*> *_tileBounds;

  // Physical boundaries at the edge of the world. Check these to see if the Ball has collided with a wall
  std::vector<NewRenderable*> *_tileWalls;

public:
  NewTile() :
    _surface(0),
    _neighbors(0),
    _tileBounds(0),
    _tileWalls(0)
  {}

  ~NewTile()
  {}

  /*
   * _neighbors and _surface will be specifically passed into Tile instances, and are not allocated here
   */
  unsigned char Initialize();

  unsigned char DeInitialize();

  unsigned char SetRenderable(NewRenderable *renderable);

  unsigned char SetNeighbors(std::vector<NewTile*> *neighbors);

  /*
   * Initializes Meshes for the imaginary bounds between tiles and Renderables for the physical bounds
   * between the tiles and the world.
   */
  unsigned char PostLoad();

  unsigned char Tick(double t);
};

