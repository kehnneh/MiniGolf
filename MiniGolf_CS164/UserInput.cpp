#include <gl\glew.h>
#include <gl\freeglut.h>

#include "Ball.h"
#include "UserInput.h"
#include "Camera.h"
#include "LevelManager.h"
#include "MenuContext.h"

void UserInput::Init()
{
	memset(&m_keys, 0, 256 * sizeof(bool));
  memset(&m_specialKeys, 0, 256 * sizeof(bool));
}

void UserInput::DeInit()
{
	camera = 0;
  _ball = 0;
}

void UserInput::PressKey(unsigned char key)
{
	m_keys[key] = true;
}

void UserInput::ReleaseKey(unsigned char key)
{
	m_keys[key] = false;
}

void UserInput::PressSpecialKey(unsigned char key)
{
  m_specialKeys[key] = true;
}

void UserInput::ReleaseSpecialKey(unsigned char key)
{
  m_specialKeys[key] = false;
}

bool UserInput::IsKeyPressed(unsigned char key)
{
	return m_keys[key];
}

void UserInput::BindCamera(Camera* c)
{
	camera = c;
}

void UserInput::BindBall(Ball *ball)
{
  _ball = ball;
}

void UserInput::SetLevelManager(LevelManager *lvlMgr)
{
  _levelMgr = lvlMgr;
}

void UserInput::SetLevelMenuContext(MenuContext *mc)
{
  _lmc = mc;
}

void UserInput::SetGameMenuContext(MenuContext *mc)
{
  _gmc = mc;
}

void UserInput::Tick(const double dt)
{
  float t = (float) dt;
  if (!_menu)
  {
    camera->SetTarget(*_ball->Matrix()->Position());
	  if (IsKeyPressed(27))
	  {
      // go to level select menu
      _menu = _levelMenu = true;
      m_keys[27] = false;
		  //glutLeaveMainLoop();
	  }
    // Camera controls
	  else if (IsKeyPressed('q'))
	  {
		  camera->IncYaw(-1.f * _rotationSensitivity * t);
	  }
	  else if (IsKeyPressed('e'))
	  {
		  camera->IncYaw(1.f * _rotationSensitivity * t);
	  }
	  else if (IsKeyPressed('z'))
	  {
		  camera->IncPitch(-1.f * _rotationSensitivity * t);
	  }
	  else if (IsKeyPressed('x'))
	  {
		  camera->IncPitch(1.f * _rotationSensitivity * t);
	  }
	  else if (IsKeyPressed('a'))
	  {
		  camera->MoveLeft(-1.f * _movementSensitivity * t);
	  }
	  else if (IsKeyPressed('d'))
	  {
		  camera->MoveLeft(1.f * _movementSensitivity * t);
	  }
	  else if (IsKeyPressed('w'))
	  {
		  camera->MoveForward(1.f * _movementSensitivity * t);
	  }
	  else if (IsKeyPressed('s'))
	  {
		  camera->MoveForward(-1.f * _movementSensitivity * t);
	  }
    // Ball Direction control
    else if (m_specialKeys[GLUT_KEY_LEFT])
    {
      if (!_ball->IsMoving())
      {
        _ball->DirectionMatrix()->IncYaw(2.f * _rotationSensitivity * t);
      }
    }
    else if (m_specialKeys[GLUT_KEY_RIGHT])
    {
      if (!_ball->IsMoving())
      {
        _ball->DirectionMatrix()->IncYaw(-2.f * _rotationSensitivity * t);
      }
    }
    else if (m_specialKeys[GLUT_KEY_UP])
    {
      _ball->Hit(2.f);
      _levelMgr->Hit(_gmc);
      m_specialKeys[GLUT_KEY_UP] = false;
    }
    else if (IsKeyPressed('n'))
    {
      _levelMgr->NextLevel();
      m_keys['n'] = false;
    }
    else if (IsKeyPressed('p'))
    {
      _levelMgr->PrevLevel();
      m_keys['p'] = false;
    }
  }
  else
  {
    if (_levelMenu)
    {
      if (IsKeyPressed(27))
      {
        // go to profile select instead of quitting
        _levelMenu = false;
        m_keys[27] = false;
      }
      else if (m_keys[' '])
      {
        _levelMgr->PlayLevel(_lmc->Selection());
        _menu = false;
        m_keys[' '] = false;
      }
      else if (m_specialKeys[GLUT_KEY_UP])
      {
        _lmc->SelectPrevious();
        m_specialKeys[GLUT_KEY_UP] = false;
      }
      else if (m_specialKeys[GLUT_KEY_DOWN])
      {
        _lmc->SelectNext();
        m_specialKeys[GLUT_KEY_DOWN] = false;
      }
    }
    else // if (_profileMenu)
    {
      if (IsKeyPressed(27))
      {
        glutLeaveMainLoop();
      }
      else if (m_keys[' '])
      {
        _levelMenu = true;
      }
      else if (m_specialKeys[GLUT_KEY_UP])
      {
        //_pmc->SelectPrevious();
        m_specialKeys[GLUT_KEY_UP] = false;
      }
      else if (m_specialKeys[GLUT_KEY_DOWN])
      {
        //_pmc->SelectNext();
        m_specialKeys[GLUT_KEY_DOWN] = false;
      }
    }
  }
}

MenuContext *UserInput::Menu()
{
  if (_menu)
  {
    if (_levelMenu)
      return _lmc;
    else
      return 0;//_pmc;
  }
  else
  {
    return 0;
  }
}

MenuContext *UserInput::InGameHUD()
{
  return _gmc;
}