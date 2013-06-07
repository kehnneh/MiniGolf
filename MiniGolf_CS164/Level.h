#pragma once

#include <string>
#include <vector>

#include <glm\glm.hpp>

class Tile;
class Tee;

class Camera;
class Shader;
class Ball;

class Level
{
private:
  std::vector<Tile*> _tiles;
  std::string *_name;

  glm::vec3 _lightSourceDirection;
  glm::vec4 _ambientColor;

  unsigned int _par;

  Tee *_tee, *_cup;
  Ball *_ball;

  bool _finished;

public:
  Level() :
    _lightSourceDirection(1.f, 1.f, 1.f),
    _ambientColor(.2f, .2f, .2f, 1.f),
    _name(0),
    _tee(0),
    _cup(0),
    _ball(0),
    _finished(false)
  {}

  ~Level()
  {}

  unsigned char Initialize();

  unsigned char DeInitialize();

  unsigned char PostLoad();

  void ReadName(char*);
  void ReadPar(char*);
  void ReadTile(char*);
  void ReadTee(char*);
  void ReadCup(char*);

  std::string GetName();
  unsigned int GetPar();

  bool Finished();

  void Render(Camera *c, Shader *s);
  void Tick(double t);

  Ball *GetBall();
};

