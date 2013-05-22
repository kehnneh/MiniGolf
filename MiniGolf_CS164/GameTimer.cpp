#include "GameTimer.h"
#include <gl\glfw.h>

void GameTimer::Init()
{
  Reset();
}

void GameTimer::Reset()
{
  _lastQuery = 0.0;
  glfwSetTime(_lastQuery);
}

const double GameTimer::TickTime()
{
  double now = glfwGetTime();
  _lastTickDuration = now - _lastQuery;
  _lastQuery = now;
  return _lastTickDuration;
}