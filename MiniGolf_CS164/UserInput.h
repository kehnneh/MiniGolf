#pragma once

class Ball;
class Camera;
class LevelManager;
class MenuContext;

/// Defines what happens when the game receives input from the keyboard
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

  /// Returns whether the specified GLUT normal key has been pressed
	inline bool IsKeyPressed(unsigned char key);

  /// Binds a camera to specific user controls
	void BindCamera(Camera* c);

  /// Binds a ball to specific user controls
  void BindBall(Ball *ball);

  /// Marks the specified key as pressed
	void PressKey(unsigned char key);

  /// Marks the specified key as released
	void ReleaseKey(unsigned char key);

  /// Associates a LevelManager with user input
  void SetLevelManager(LevelManager *lvlMgr);

  /// Associates a MenuContext for level selection with user input
  void SetLevelMenuContext(MenuContext *mc);
  //void SetProfileMenuContext(MenuContext *mc);
  /// Associates a MenuContext for displaying current scores in game
  void SetGameMenuContext(MenuContext *mc);

  /// Marks the specified GLUT special key as pressed
  void PressSpecialKey(unsigned char key);

  /// Marks the specified GLUT special key as released
  void ReleaseSpecialKey(unsigned char key);

  /// Updates data based on the current state of keys
	void Tick(const double dt);

  /// Performs data allocation
	void Init();

  /// Performs data deallocation
	void DeInit();

  /// Returns the active MenuContext
  MenuContext *Menu();

  /// Returns the scoreboard MenuContext
  MenuContext *InGameHUD();
};

