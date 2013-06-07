#pragma once

#include <glm\glm.hpp>
#include "MatrixObject.h"
#include "Tile.h"
#include "Renderable.h"

class Arrow;

/// Defines a ball that is moveable by surface physics, akin to Unreal Engine's SurfaceActor class
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

  /// Performs data allocation
  unsigned char Initialize();
  
  /// Performs data deallocation
  unsigned char DeInitialize();

  /// Sets the current tile that the ball is on
  unsigned char CurrentTile(Tile* tile);

  /// Sets the renderable for the ball
  unsigned char SetRenderable(Renderable *renderable);

  /// Updates the ball's position and checks for collisions
  unsigned char Tick(double t);

  /// Draws the ball relative to the camera and active shader
  unsigned char Render(Camera *camera, Shader *shader);

  /// Sets the ball's radius
  void SetRadius(float r);

  /// Detects collision against a given mesh, accounting for the specified distance between the mesh and the ball
  float DetectCollision(glm::vec3 const & pos, glm::vec3 const & endPos, const Mesh *m, float dist);

  /// Handles collisions between Tile entities
  bool HandleFakeCollision(float & t, glm::vec3 & pos, glm::vec3 & endpos, glm::vec3 & d, float dist);

  /// Handles collisions between the ball and physical walls
  bool HandleCollision(float & t, glm::vec3 & pos, glm::vec3 & endpos, glm::vec3 & d, float dist);

  /// Hits the ball forward
  bool Hit(float power);

  /// Returns true if the ball is moving, fals otherwise
  bool IsMoving();

  /// Returns the Tile entity that the ball is currently on
  Tile *GetTile();

  /// Returns the ball's matrix for easy access
  MatrixObject *Matrix();

  /// Returns the associated Arrow's matrix for easy access
  MatrixObject *DirectionMatrix();

  /// Returns the ball's radius
  float Radius();
};

