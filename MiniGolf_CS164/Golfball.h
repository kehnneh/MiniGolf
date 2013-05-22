#pragma once

#include "Renderable.h"
#include "Moveable.h"
#include "MatrixObject.h"

class Golfball : public Moveable
{
private:
  Renderable *_sphere;

  float _radius;

public:
  Golfball() :
      _sphere(0),
      _radius(0.f)
  {}

  ~Golfball()
  {}

  bool Init();
  void DeInit();

  void Tick(double t);
  void Render(Camera *camera);

  // Position Setter
  void Position(const glm::vec3 pos);

  // Scale Setter
  void Scale(float uniform);

  // Rotation Setter
  void Rotation(const glm::vec3 eulerAngles);
};

