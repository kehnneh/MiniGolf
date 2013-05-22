#pragma once

#include <glm\glm.hpp>

class MatrixObject;
class Tile;

class Moveable
{
private:
  static const glm::vec3 *_gravity;

	glm::vec3 *_velocity;
  float _speed;
  
  MatrixObject *transform;

protected:
  //Hard-coded because it needs to know about the tile it's currently
  //residing on. Physics is relative to the virtual tile set created
  //by the application
  Tile* _tile;

  char IsOnTile();

public:
	Moveable() :
	  _velocity(0),
    _speed(0.f),
    _tile(0)
	{}

	~Moveable()
	{}

  void Init();
  void DeInit();

  void Tick(double t);

  void Impulse(float s);

  void SetTile(Tile * t);

  const glm::vec3 *Position() const;

  void BindMatrix(MatrixObject *m);
};

