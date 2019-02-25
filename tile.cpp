#include "stdafx.h"
#include "tile.h"

TILE::TILE()
{
}

TILE::~TILE()
{
}

void TILE::setttingObject()
{
	string strTmp = "";

	switch (_object)
	{
	case TILE::OBJECT::NONE:
		
		break;

	case TILE::OBJECT::MAX:
		break;
	}


	_pObjectImage = IMAGEMANAGER->findImage(strTmp);
}

void TILE::init(int nTileLeft, int nTileTop, int nTileSize, image* pImg, int nNodeIndex)
{
	setAroundWall(PASS);
	setIsWall(false);
	setTerrian(TILE::TERRIAN::NONE);
	setImg(nullptr);
	setFrameX(28);
	//setFrameX(0);
	setFrameY(0);
	setRectTile(nTileLeft, nTileTop, nTileSize, nTileSize);
	setImg(pImg);
	setNodeIndex(nNodeIndex);
	_object = OBJECT::NONE;
	setLimitRect(RectMake(0, 0, WINSIZEX, WINSIZEY));
}

void TILE::render(HDC hdc)
{
	if (_rcTile.right > _rcCameraLimit.left
		&& _rcTile.left < _rcCameraLimit.right
		&&_rcTile.bottom > _rcCameraLimit.top
		&& _rcTile.top < _rcCameraLimit.bottom
		)
	{
		_pImage->frameRender(hdc, _rcTile.left, _rcTile.top, _nFrameX, _nFrameY);
		if (_object != OBJECT::NONE)
		{
			_pObjectImage->frameRender(hdc, _rcTile.left, _rcTile.top, 0, 0);
		}
	}

}

void TILE::release()
{
	_pImage = nullptr;
}

void TILE::settingTile(int nFrameX, int nFrameY, bool bIsWall, OBJECT object)
{
	setFrameX(nFrameX);
	setFrameY(nFrameY);
	setIsWall(bIsWall);
	setObject(object);
	if (!_bIsWall)
	{
		//지우는 경우
		//패스를 까는 경우
		setAroundWall(PASS);
	}
	else
	{
		_object = OBJECT::NONE;
	}
	setttingObject();
}

void TILE::readjustWall(int nAroundWall, int nFrameX, int nFrameY)
{
	setAroundWall(nAroundWall);
	setFrameX(nFrameX);
	setFrameY(nFrameY);
}

string TILE::makeSaveString()
{
	//노드인덱스/주변값/벽/프레임x/프레임y
	string strTmp = "";
	strTmp.append(to_string(_nNodeIndex));
	strTmp.append("/");
	strTmp.append(to_string(_nAroundWall));
	strTmp.append("/");
	strTmp.append(to_string((int)_bIsWall));
	strTmp.append("/");
	strTmp.append(to_string(_nFrameX));
	strTmp.append("/");
	strTmp.append(to_string(_nFrameY));
	strTmp.append("/");
	strTmp.append(to_string(static_cast<int>(_object)));
	strTmp.append("/");

	return strTmp;
}

bool TILE::setObject(OBJECT object)
{
	if (!_bIsWall)
	{
		_object = object;
		return true;
	}

	return false;
}

TILE::OBJECT TILE::getObject()
{
	return _object;
}

void TILE::move(int vertical, int horizontal)
{
	_rcTile.left += horizontal;
	_rcTile.right += horizontal;

	_rcTile.top += vertical;
	_rcTile.bottom += vertical;
}
