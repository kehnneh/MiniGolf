#pragma once

#include <glm\glm.hpp>

class Renderable;
class Camera;
class Shader;
class MatrixObject;

/// Defines an arrow to draw in the world
class Arrow
{
private:
  Renderable *_renderable;
  MatrixObject *_transform;

public:
  Arrow() :
    _renderable(0),
    _transform(0)
  {}

  ~Arrow()
  {}

  /// Performs data allocation
  unsigned char Initialize();

  /// Performs data deallocation
  unsigned char DeInitialize();

  /// Updates the arrow's renderable and orientation marix
  unsigned char Tick(double t);

  /// Render's the arrow according to the camera's orientation and the active shader
  unsigned char Render(Camera *camera, Shader *shader);

  /// Gives easy access to the arrow's Y rotation
  void RotateY(float amt);

  /// Matrix access
  MatrixObject *Matrix();
};

