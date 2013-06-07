#pragma once

#include <string>
#include <vector>

#include <glm\glm.hpp>

class Tile;
class Tee;

class Camera;
class Shader;
class Ball;

/// Defines one Golfcourse hole
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

  /// Performs data allocation
  unsigned char Initialize();

  /// Performs data deallocation
  unsigned char DeInitialize();

  /// Initializes the Level's ball properly and its Tiles' adjacency lists
  unsigned char PostLoad();

  /// Reads the name of the hole
  void ReadName(char*);

  /// Reads the par of the hole
  void ReadPar(char*);

  /// Reads data for one Tile in the hole
  void ReadTile(char*);

  /// Reads the Tee data for the hole
  void ReadTee(char*);

  /// Reads the cup data for the hole
  void ReadCup(char*);

  /// Returns the name of the hole
  std::string GetName();

  /// Returns the par of the hole
  unsigned int GetPar();

  /// Returns whether the player has finished the hole
  bool Finished();

  /// Renders the Level, including its Tiles, Ball, Tee, and Cup
  void Render(Camera *c, Shader *s);

  /// Updates the associated objects with the Level
  void Tick(double t);

  /// Returns the Ball object associated with the Level
  Ball *GetBall();
};

