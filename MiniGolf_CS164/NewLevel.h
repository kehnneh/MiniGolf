#pragma once

#include <string>
#include <vector>

#include <glm\glm.hpp>

class Tile;

class NewLevel
{
private:
  std::vector<Tile*> _tiles;
  std::string *_name;

  glm::vec3 _lightSourceDirection;
  glm::vec4 _ambientColor;

  unsigned int _par;

  // Tee *_t;
  // Cup *_c;

public:
  NewLevel() :
    _lightSourceDirection(1.f, 1.f, 1.f),
    _ambientColor(.2f, .2f, .2f, 1.f)
  {}

  ~NewLevel()
  {}

  unsigned char Initialize();

  unsigned char DeInitialize();

  void ReadName(char*);
  void ReadPar(char*);
  void ReadTile(char*);
  void ReadTee(char*);
  void ReadCup(char*);

  std::string GetName();
  unsigned int GetPar();
  // Tee *GetTee();
  // Cup *GetCup();
};

