#pragma once

#include <vector>
#include <map>
#include <string>

class NewLevel;

class LevelManager
{
public:
  typedef void (NewLevel::*levelCallback)(char*);
  typedef void (LevelManager::*levelMgrCallback)(char*);

private:
  std::string _courseName;

  std::vector<NewLevel*> *_levels;

  unsigned int _activeLevel;

  unsigned int _holeCount;

  void InitializeCourse(char*);
  void CreateLevel(char*);
  void FinalizeLevel(char*);

  template <typename K, typename T>
  unsigned char ExecuteCallback(std::map<K, void (T::*)(char*)> const &, K, char*, T*);

public:
  LevelManager() :
    _levels(0),
    _activeLevel(-1),
    _holeCount(-1)
  {}

  ~LevelManager()
  {}

  unsigned char Initialize();

  unsigned char DeInitialize();

  unsigned char LoadLevels();

  void PlayLevel(unsigned int level);
};

