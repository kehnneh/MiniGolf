#pragma once

#include <vector>
#include <string>

#include "Tile.h"
#include "Camera.h"
#include "Ball.h"

class Level
{
private:
  // This needs to be Tile*
  std::vector<Tile*> *_tiles;

  glm::vec3 *_lightSourceDirection;
  glm::vec4 *_ambient;

  unsigned short _tee, _cup;

  Ball *_ball;

public:
  Level() :
    _tiles(0),
    _ball(0),
    _ambient(0),
    _lightSourceDirection(0),
    _tee(-1),
    _cup(-1)
  {}

  ~Level()
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

  unsigned char Render(Camera *camera, Shader *shader);

  Ball *GetBall();
};

