#pragma once

#include <vector>
#include "Renderable.h"
#include "Camera.h"
#include "Shader.h"
class Ball;

/// A piece of a Level's floor
class Tile
{
private:
  unsigned int _id;

  std::vector<unsigned int> *_neighborIds;

  // This is the renderable that is drawn for this tile.
  Renderable *_surface;

  std::vector<Tile*> *_neighbors;

  // Collision boundaries between tiles. Check these to see if the Tile has entered another tile
  std::vector<Mesh*> *_tileBounds;

  std::vector<Renderable*> _tileBoundRenderables;

  // Physical boundaries at the edge of the world. Check these to see if the Ball has collided with a wall
  std::vector<Renderable*> *_tileWalls;

  glm::vec3 *_xaxis, *_zaxis;

  unsigned char ComputeXZPlane(glm::vec3 const & up);

public:
  Tile() :
    _surface(0),
    _neighbors(0),
    _neighborIds(0),
    _tileBounds(0),
    _tileWalls(0),
    _xaxis(0),
    _zaxis(0),
    _id(-1)
  {}

  ~Tile()
  {}

  /// Reads tile data
  void ReadTile(char*);

  /// Performs data allocation
  unsigned char Initialize();

  /// Performs data deallocation
  unsigned char DeInitialize();

  /// Associates a renderable with this Tile
  unsigned char SetRenderable(Renderable *renderable);

  /// Sets the Tile's adjacency list
  unsigned char SetNeighbors(std::vector<Tile*> *neighbors);

  /// Returns the Tile's adjacency list by IDs
  std::vector<unsigned int> *GetNeighborIds();

  /// Returns the Tile in the adjacency list by its index in the list
  Tile *Neighbor(unsigned int n);

  /// Returns the Tile adjacency list
  std::vector<Tile*> *Neighbors();

  /// Initializes Meshes for the imaginary bounds between tiles and Renderables for the physical bounds between the tiles and the world.
  unsigned char PostLoad();

  /// Does nothing! A tile has nothing to update!
  unsigned char Tick(double t);

  /// Renders the Tile
  unsigned char Render(Camera *camera, Shader *s);

  /// Returns the surface normal of the Tile
  glm::vec3 Normal();

  /// Returns a vector of all the phsyical walls associated with the Tile
  std::vector<Renderable*> *RealWalls();

  /// Returns a vector of all the imaginary walls between each Tile that are associated with this Tile
  std::vector<Mesh*> *FakeWalls();
};

