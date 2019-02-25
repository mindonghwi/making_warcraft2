#include "stdafx.h"
#include "object.h"

void OBJECT::init(float posX, float posY, int width, int height)
{
	_posX = posX;
	_posY = posY;
	_width = width;
	_height = height;

	_rc = RectMakeCenter(static_cast<int>(_posX), static_cast<int>(_posY), _width, _height);
}

void OBJECT::setImage(image * pImage)
{
	_pImg = pImage;
}

int OBJECT::getLeft()
{
	return static_cast<int>(_posX) - _width / 2;
}

int OBJECT::getTop()
{
	return static_cast<int>(_posY) - _height / 2;
}

