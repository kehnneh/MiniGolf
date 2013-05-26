#pragma once

#include <glm\glm.hpp>
#include "MatrixObject.h"
#include "Tile.h"
#include "Renderable.h"

class Ball
{
private:
  // For physics
  glm::vec3 *_velocity;
  float _radius, _speed;

  Tile *_tile;

  // World placement
  MatrixObject *_transform;

  // Drawing
  Renderable *_renderable;

public:
  Ball() :
      _transform(0),
      _tile(0),
      _velocity(0),
      _renderable(0),
      _radius(0.f),
      _speed(0.f)
  {}

  ~Ball()
  {}

  unsigned char Initialize();
  
  unsigned char DeInitialize();

  unsigned char CurrentTile(Tile* tile);

  unsigned char SetRenderable(Renderable *renderable);

  unsigned char Tick(double t);

  unsigned char Render(Camera *camera, Shader *shader);

  float DetectCollision(glm::vec3 const & pos, glm::vec3 const & endPos, const Mesh *m, float dist);

  void Hit(glm::vec3 direction, float power);

  MatrixObject *Matrix();

  float Radius();
};

