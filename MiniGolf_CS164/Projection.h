#pragma once

#include <glm\glm.hpp>

/// Defines a projection matrix for displaying things in a perspective projection on the screen
class Projection
{
private:
	glm::mat4 *_mat;
	float _fovy, _znear, _zfar;
	int _screenWidth, _screenHeight;
	bool _bNeedsUpdate;

public:
	Projection()
		: _fovy(45.f), _znear(0.1f), _zfar(10000.f),
		  _screenWidth(0), _screenHeight(0),
		  _mat(0),
		  _bNeedsUpdate(true)
	{}
	~Projection()
	{}

  /// Performs data allocation
	void Init();
	
  /// Performs data deallocation
  void DeInit();

  /// Sets the Field of View in terms of degrees in screen Y coordinates
	void fovy(float fovy);

  /// Sets the near clipping plane's depth
	void znear(float znear);

  /// Sets the far clipping plane's depth
	void zfar(float zfar);

  /// Sets the screen's width
	void screenWidth(int w);

  /// Sets the screen's height
	void screenHeight(int h);

  /// Updates the projection matrix, if necessary
	void Tick();

  /// Returns the projection matrix itself
	glm::mat4 const * const Matrix();
};

