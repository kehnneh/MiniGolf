#pragma once

#include <vector>
#include "Renderable.h"
#include "Camera.h"
#include "Shader.h"
class Ball;

class Tile
{
private:
  // This is the renderable that is drawn for this tile.
  Renderable *_surface;

  std::vector<Tile*> *_neighbors;

  // Collision boundaries between tiles. Check these to see if the Tile has entered another tile
  std::vector<Mesh*> *_tileBounds;

  // Physical boundaries at the edge of the world. Check these to see if the Ball has collided with a wall
  std::vector<Renderable*> *_tileWalls;

  glm::vec3 *_xaxis, *_zaxis;

  unsigned char ComputeXZPlane(glm::vec3 const & up);

public:
  Tile() :
    _surface(0),
    _neighbors(0),
    _tileBounds(0),
    _tileWalls(0),
    _xaxis(0),
    _zaxis(0)
  {}

  ~Tile()
  {}

  /*
   * _neighbors and _surface will be specifically passed into Tile instances, and are not allocated here
   */
  unsigned char Initialize();

  unsigned char DeInitialize();

  unsigned char SetRenderable(Renderable *renderable);

  unsigned char SetNeighbors(std::vector<Tile*> *neighbors);

  /*
   * Initializes Meshes for the imaginary bounds between tiles and Renderables for the physical bounds
   * between the tiles and the world.
   */
  unsigned char PostLoad();

  unsigned char Tick(double t);

  unsigned char Render(Camera *camera, Shader *s);

  glm::vec3 Normal();

  std::vector<Renderable*> *RealWalls();

  std::vector<Mesh*> *FakeWalls();
};

