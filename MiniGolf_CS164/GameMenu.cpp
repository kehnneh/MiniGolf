#include "GameMenu.h"

#include <gl\glew.h>
#include <gl\freeglut.h>

#include "MenuContext.h"

#include "CommonUtils.h"

#include "LevelManager.h"
#include "Level.h"

unsigned char GameMenu::Initialize()
{
  _contexts = new std::vector<MenuContext*>;

  return STATUS_OK;
}

unsigned char GameMenu::DeInitialize()
{
  std::vector<MenuContext*>::iterator it, end;

  it = _contexts->begin(), end = _contexts->end();
  for (; it != end; it++)
  {
    Delete(&(*it));
  }

  return STATUS_OK;
}

// gets called first, this is _contexts->at(0)
void GameMenu::SetLevelManager(LevelManager *levelMgr)
{
  std::vector<std::string> names = levelMgr->LevelNames();
  //MenuContext *mc = new MenuContext;
  _levelContext = new MenuContext;
  _levelContext->Initialize();

  std::vector<std::string>::iterator it = names.begin(), end = names.end();
  for (; it != end; it++)
  {
    _levelContext->AddSelectableText(*it, glm::vec2(50.f, std::distance(names.begin(), it) * 12));
  }

  _contexts->push_back(_levelContext);

  _gameContext = new MenuContext();
  _gameContext->Initialize();
  for (unsigned int i = 0; i < levelMgr->GetHoleCount(); i++)
  {
    char derp[4];
    _gameContext->AddStaticText(itoa(-levelMgr->Levels()->at(i)->GetPar(), derp, 10), glm::vec2(50.f + 20.f * (float) i, 20.f));
  }
}

void GameMenu::ActivateLevelManagerContext()
{
  _activeContext = _contexts->at(0);
}

void GameMenu::CreateGameContext()
{
  
}

/*
void GameMenu::Render()
{
  if (_activeContext)
  {
    _activeContext->Render();
  }
}
*/

void GameMenu::Deactivate()
{
  _activeContext = nullptr;
}

MenuContext *GameMenu::LevelContext()
{
  return _levelContext;
}

MenuContext *GameMenu::ProfileContext()
{
  return _profileContext;
}

MenuContext *GameMenu::GameContext()
{
  return _gameContext;
}