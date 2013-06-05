#pragma once

#include <glm\glm.hpp>
#include "MatrixObject.h"
#include "Tile.h"
#include "Renderable.h"

class Arrow;

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
  Arrow *_direction;

public:
  Ball() :
      _transform(0),
      _tile(0),
      _velocity(0),
      _renderable(0),
      _direction(0),
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

  void SetRadius(float r);

  float DetectCollision(glm::vec3 const & pos, glm::vec3 const & endPos, const Mesh *m, float dist);

  bool HandleFakeCollision(float & t, glm::vec3 & pos, glm::vec3 & endpos, glm::vec3 & d, float dist);

  bool HandleCollision(float & t, glm::vec3 & pos, glm::vec3 & endpos, glm::vec3 & d, float dist, glm::vec3 & w);

  bool Hit(float power);

  MatrixObject *Matrix();

  MatrixObject *DirectionMatrix();

  float Radius();
};

