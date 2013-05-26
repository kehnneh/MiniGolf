#pragma once

#include "Camera.h"
#include "Level.h"

class UserInput;
class Shader;
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

  Level *LEVEL;
	UserInput *userInput;
	Projection *_projection;
	Camera *c[2];

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

	bool Init(int argc, char** argv);
	void DeInit();

	void Run();
};