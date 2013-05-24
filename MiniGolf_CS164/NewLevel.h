#pragma once

#include <vector>
#include <string>

#include "NewTile.h"

class NewLevel
{
private:
  // This needs to be NewTile*
  std::vector<NewTile*> *_tiles;

  glm::vec3 *_lightSourceDirection;
  glm::vec4 *_ambient;

  unsigned short _tee, _cup;

public:
  NewLevel() :
    _tiles(0),
    _ambient(0),
    _lightSourceDirection(0),
    _tee(-1),
    _cup(-1)
  {}

  ~NewLevel()
  {}

  /*
   * Allocates memory
   */
  unsigned char Initialize();

  /*
   * Frees memory
   */
  unsigned char DeInitialize();

  /*
   * Loads the level from the specified level file. Populates _tiles
   */
  unsigned char LoadFromFile(std::string filename);

  /*
   * Post-Initialization data assignments
   */
  unsigned char PostLoad();

  unsigned char Tick(double t);
};

