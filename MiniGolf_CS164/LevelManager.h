#pragma once

#include <vector>
#include <string>

class Level;

class LevelManager
{
private:
  std::string _courseName;

  std::vector<Level*> *_levels;

  Level *_activeLevel;

public:
  LevelManager() :
    _levels(0),
    _activeLevel(0)
  {}

  ~LevelManager()
  {}

  unsigned char Initialize();

  unsigned char DeInitialize();

  unsigned char LoadLevels();

  void PlayLevel(unsigned int level);
};

