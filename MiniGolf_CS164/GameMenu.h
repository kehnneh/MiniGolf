#pragma once

#include <string>
#include <vector>

#include <glm\glm.hpp>

class MenuContext;
class LevelManager;

/// Defines a menu system for the game
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

  /// Performs data allocation
  unsigned char Initialize();

  /// Performs data deallocation
  unsigned char DeInitialize();

  /// Associates the specified LevelManager with this Menu system and constructs relevant menus
  void SetLevelManager(LevelManager *levelMgr);

  /// Deactivates menus from being displayed
  void Deactivate();

  /// Activates the Level Management menu
  void ActivateLevelManagerContext();

  //void SetProfileManager(ProfileManager* profMgr);

  //void ActivateProfileManagerContext();

  /// Placeholder
  void CreateGameContext();

  /// Returns the LevelManagement MenuContext
  MenuContext *LevelContext();

  /// Returns the ProfileManagement MenuContext
  MenuContext *ProfileContext();

  /// Returns the Game Score MenuContext
  MenuContext *GameContext();
};

