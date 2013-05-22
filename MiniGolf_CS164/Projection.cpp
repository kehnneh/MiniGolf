#include "Projection.h"
#include "CommonUtils.h"

#include <glm\gtc\matrix_transform.hpp>

void Projection::Init()
{
	_mat = new glm::mat4;
}

void Projection::DeInit()
{
	SAFE_DELETE(_mat);
}

void Projection::fovy(float fovy) {	_fovy = fovy; _bNeedsUpdate = true; }

void Projection::znear(float znear) { _znear = znear; _bNeedsUpdate = true; }

void Projection::zfar(float zfar) { _zfar = zfar; _bNeedsUpdate = true; }

void Projection::screenWidth(int w) { _screenWidth = w; _bNeedsUpdate = true; }

void Projection::screenHeight(int h) { _screenHeight = h; _bNeedsUpdate = true; }

void Projection::Tick()
{
	if (_bNeedsUpdate)
	{
		*_mat = glm::perspective(_fovy, (float) _screenWidth / (float) _screenHeight, _znear, _zfar);
		_bNeedsUpdate = false;
	}
}

// Returns a non-modifiable POINTER to a non-modifiable VALUE
glm::mat4 const * const Projection::Matrix() { return _mat; }