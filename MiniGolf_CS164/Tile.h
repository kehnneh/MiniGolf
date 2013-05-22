#pragma once

#include <glm\glm.hpp>
#include "Renderable.h"
#include "Moveable.h"

#include <vector>

class Camera;

// use glm::intersectRayTriangle to determine if the ball has left the tile
// DO NOT USE BOUNDS, Tiles are NOT guaranteed to be rectangular shapes!

class Tile : public Renderable
{
private:
  glm::vec3 *_slope;

  void ComputeSlope(const glm::vec3 up);

protected:
	unsigned short edges;
	unsigned short* neighbors;

  // Physical borders that the golf ball can collide with
	std::vector<Renderable*> borders;
  // Imaginary borders that the golf ball can enter a new tile through
  


	void GenerateColor();

public:
	unsigned int tileId;

	Tile() :
      tileId(0),
		  edges(0),
		  neighbors(0),
      _slope(0)
	{}

	Tile(unsigned short Id) :
      tileId(Id),
		  edges(0),
		  neighbors(0),
      _slope(0)
	{}

	~Tile()
	{}

	void TileInit();

	void DeInit();

	bool SetNeighbor(unsigned short edgeId, unsigned short neighborTileId);

	void Finalize();
	void RenderBorders(Camera* c);

  glm::vec3 *Normal() const;
  glm::vec3 *FirstVertex(unsigned int tri) const;
  unsigned int Tile::TriangleCount() const;
};

