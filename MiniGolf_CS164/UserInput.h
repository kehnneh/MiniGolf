#pragma once

class Camera;

class UserInput
{
private:
	// External links to variables controlled via UserInput::Tick()
	Camera* camera;
  float _rotationSensitivity, _movementSensitivity;

private:
	// Internal data
	bool m_keys[256];

public:
	UserInput()
		: camera(0),
#pragma warning( suppress : 4351 )
		  m_keys(),
      _rotationSensitivity(50.f), _movementSensitivity(5.f)
	{}
	~UserInput()
	{}

	inline bool IsKeyPressed(unsigned char key);

	void BindCamera(Camera* c);

	void PressKey(unsigned char key);
	void ReleaseKey(unsigned char key);

	void Tick(const double dt);

	void Init();
	void DeInit();
};

