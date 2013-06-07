#pragma once

#include <string>
#include <vector>

#include <glm\glm.hpp>

class MenuContext;
class LevelManager;

class GameMenu
{
private:
  std::vector<MenuContext*> *_contexts;
  MenuContext *_activeContext;
  MenuContext *_levelContext, *_profileContext, *_gameContext;

public:
  GameMenu() :
    _contexts(0),
    _activeContext(0)
  {}

  ~GameMenu()
  {}

  unsigned char Initialize();

  unsigned char DeInitialize();

  void SetLevelManager(LevelManager *levelMgr);

  void Deactivate();

  void ActivateLevelManagerContext();

  //void SetProfileManager(ProfileManager* profMgr);

  //void ActivateProfileManagerContext();

  void CreateGameContext();

  MenuContext *LevelContext();

  MenuContext *ProfileContext();

  MenuContext *GameContext();
};

