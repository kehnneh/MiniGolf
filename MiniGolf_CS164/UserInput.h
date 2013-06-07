#pragma once

class Ball;
class Camera;
class LevelManager;
class MenuContext;

class UserInput
{
private:
	Camera *camera;
  float _rotationSensitivity, _movementSensitivity, _directionSensitivity;

  Ball *_ball;
  LevelManager *_levelMgr;
  MenuContext *_lmc, *_gmc; // level and in-game

  bool _menu, _levelMenu;

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
      _rotationSensitivity(50.f), _movementSensitivity(5.f), _directionSensitivity(10.f),
      _levelMgr(0), _lmc(0),
      _menu(true), _levelMenu(true)
	{}

	~UserInput()
	{}

	inline bool IsKeyPressed(unsigned char key);

	void BindCamera(Camera* c);
  void BindBall(Ball *ball);

	void PressKey(unsigned char key);
	void ReleaseKey(unsigned char key);

  void SetLevelManager(LevelManager *lvlMgr);
  void SetLevelMenuContext(MenuContext *mc);
  //void SetProfileMenuContext(MenuContext *mc);
  void SetGameMenuContext(MenuContext *mc);

  void PressSpecialKey(unsigned char key);
  void ReleaseSpecialKey(unsigned char key);

	void Tick(const double dt);

	void Init();
	void DeInit();

  MenuContext *Menu();
  MenuContext *InGameHUD();
};

