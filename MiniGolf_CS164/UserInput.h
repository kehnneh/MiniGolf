#pragma once

class Ball;
class Camera;

class UserInput
{
private:
	Camera *camera;
  float _rotationSensitivity, _movementSensitivity, _directionSensitivity;

  Ball *_ball;

private:
	// Internal data
	bool m_keys[256];
  bool m_specialKeys[256];

public:
	UserInput()
		: camera(0),
      _ball(0),
#pragma warning( suppress : 4351 )
		  m_keys(), m_specialKeys(),
      _rotationSensitivity(50.f), _movementSensitivity(5.f), _directionSensitivity(10.f)
	{}

	~UserInput()
	{}

	inline bool IsKeyPressed(unsigned char key);

	void BindCamera(Camera* c);
  void BindBall(Ball *ball);

	void PressKey(unsigned char key);
	void ReleaseKey(unsigned char key);

  void PressSpecialKey(unsigned char key);
  void ReleaseSpecialKey(unsigned char key);

	void Tick(const double dt);

	void Init();
	void DeInit();
};

