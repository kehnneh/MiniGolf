#pragma once

#include "Camera.h"
#include "NewLevel.h"

class UserInput;
class Shader;
class Level;
class Projection;
class GameTimer;

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

  NewLevel *LEVEL;
	UserInput *userInput;
	Projection *_projection;
	Camera *c[2];
	Level *level;

	Kengine() :
      shader(0),
		  userInput(0),
#pragma warning( suppress: 4351 )
      c(),
		  level(0),
		  activeCamera(0),
      _projection(0),
      _timer(0)
	{}
	~Kengine()
	{}

	bool Init(int argc, char** argv);
	void DeInit();

	void Run();
};