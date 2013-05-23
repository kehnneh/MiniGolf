#include "Golfball.h"
#include "CommonUtils.h"

bool Golfball::Init()
{
  Moveable::Init();

  _sphere = new Renderable();
  if (!_sphere->Init("Models/golfball.obj"))
  {
    return false;
  }

  _sphere->GenerateColor(glm::vec4(1.f, 1.f, 1.f, 1.f));

  BindMatrix(_sphere->Matrix());

  return true;
}

void Golfball::DeInit()
{
  Delete(&_sphere);
}

void Golfball::Render(Camera* camera)
{
  _sphere->Render(camera);
}

void Golfball::Tick(double t)
{
  _sphere->Matrix()->Tick();
  Moveable::Tick(t);
  
  // If _tile has
  // check if the ball went in the hole?
}

void Golfball::Position(const glm::vec3 pos)
{
  _sphere->SetPosition(pos);
}

void Golfball::Scale(float uniform)
{
	_sphere->UniformScale(uniform);
}

void Golfball::Rotation(const glm::vec3 eulerAngles)
{
  _sphere->Rotation(eulerAngles);
}