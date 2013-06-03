#pragma once

#include <vector>
#include <map>
#include <string>

class NewLevel;
class Camera;
class Shader;
class UserInput;

class LevelManager
{
public:
  typedef void (NewLevel::*levelCallback)(char*);
  typedef void (LevelManager::*levelMgrCallback)(char*);

  UserInput *_uin;

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
    _holeCount(-1),
    _uin(0)
  {}

  ~LevelManager()
  {}

  unsigned char Initialize();

  unsigned char DeInitialize();

  unsigned char LoadLevels();

  void PlayLevel(unsigned int level);

  void NextLevel();

  void PrevLevel();

  void Render(Camera *c, Shader *s);

  void Tick(double dt);
};

