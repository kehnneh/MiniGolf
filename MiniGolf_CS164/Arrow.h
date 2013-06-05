#pragma once

#include <glm\glm.hpp>

class Renderable;
class Camera;
class Shader;
class MatrixObject;

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

  unsigned char Initialize();

  unsigned char DeInitialize();

  unsigned char Tick(double t);

  unsigned char Render(Camera *camera, Shader *shader);

  void RotateY(float amt);

  MatrixObject *Matrix();
};

