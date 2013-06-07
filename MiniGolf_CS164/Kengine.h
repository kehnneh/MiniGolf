#pragma once

#include <iostream>

#include "Camera.h"

class UserInput;
class Shader;
class Projection;
class GameTimer;
class LevelManager;
class GameMenu;

/// The actual engine! Does everything the game needs to do.
class Kengine
{
private:
	int windowId;

	void InitGlut(int argc, char** argv);
	void InitCallbacks();

public:
	int activeCamera;


  GameTimer *_timer;
	Shader *shader;
  GameMenu *_menu;
	UserInput *userInput;
	Projection *_projection;
	Camera *c[2];

  LevelManager *_levelMgr;

	Kengine() :
      shader(0),
		  userInput(0),
#pragma warning( suppress: 4351 )
      c(),
		  activeCamera(0),
      _projection(0),
      _timer(0)
	{}

	~Kengine()
	{}

  /// Initializes all subsystems. Rockets are good to go.
	bool Init(int argc, char** argv);

  /// Performs memory deallocation
	void DeInit();

  /// Runs the engine, starting glutMainLoop()
	void Run();
};