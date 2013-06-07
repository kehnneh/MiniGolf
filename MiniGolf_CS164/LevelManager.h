#pragma once

#include <vector>
#include <map>
#include <string>

class Level;
class Camera;
class Shader;
class UserInput;
class MenuContext;

struct PlayerScore
{
  int strokes;
};

class LevelManager
{
public:
  typedef void (Level::*levelCallback)(char*);
  typedef void (LevelManager::*levelMgrCallback)(char*);

  UserInput *_uin;

private:
  std::string _courseName;

  std::vector<Level*> *_levels;
  std::vector<PlayerScore*> *_scores;

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

  void Hit(MenuContext*);

  void PlayLevel(unsigned int level);

  void NextLevel();

  void PrevLevel();

  unsigned int GetHoleCount();

  std::vector<Level*> *Levels();

  std::vector<std::string> LevelNames();

  void Render(Camera *c, Shader *s);

  void Tick(double dt);
};

