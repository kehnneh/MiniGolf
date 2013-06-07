#pragma once

#include <vector>
#include <map>
#include <string>

class Level;
class Camera;
class Shader;
class UserInput;
class MenuContext;

/// Defines a score for a particular level
struct PlayerScore
{
  int strokes;
};

/// Manages all the Levels in a specific course, and loads Levels from a specified file
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

  /// Performs data allocation
  unsigned char Initialize();

  /// Performs data deallocation
  unsigned char DeInitialize();

  /// Loads levels from the course file
  unsigned char LoadLevels();

  /// Hits the ball and updates scoring in the game menu context
  void Hit(MenuContext*);

  /// Sets the active level to the specified level and starts playing it
  void PlayLevel(unsigned int level);

  /// Switches to the next level
  void NextLevel();

  /// Switches to the previous level
  void PrevLevel();

  /// Returns the number of holes in the course
  unsigned int GetHoleCount();

  /// Returns a vector of all the levels in the course
  std::vector<Level*> *Levels();

  /// Returns a vector of all the level names in the course
  std::vector<std::string> LevelNames();

  /// Renders the loaded course
  void Render(Camera *c, Shader *s);

  /// Updates the active level and its associated objects
  void Tick(double dt);
};

