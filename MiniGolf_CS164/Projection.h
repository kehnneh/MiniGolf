#pragma once

#include <glm\glm.hpp>

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

	void Init();
	void DeInit();

	void fovy(float fovy);
	void znear(float znear);
	void zfar(float zfar);
	void screenWidth(int w);
	void screenHeight(int h);

	void Tick();

	glm::mat4 const * const Matrix();
};

