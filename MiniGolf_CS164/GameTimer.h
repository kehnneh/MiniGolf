#pragma once

class GameTimer
{
private:
  double _lastQuery, _lastTickDuration;

public:
  GameTimer() :
      _lastQuery(0.0),
      _lastTickDuration(0.0)
  {}
  ~GameTimer()
  {}

  void Init();

  void Reset();

  // Obtains the time elapsed since the previous call to this function,
  // updates the time since the _lastQuery and the _lastTickDuration
  const double TickTime();
};

