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

	switch (_eObject)
	{
	case TILE::E_OBJECT::E_NONE:
		
		break;

	case TILE::E_OBJECT::E_MAX:
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
	_eObject = E_OBJECT::E_NONE;
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
		if (_eObject != E_OBJECT::E_NONE)
		{
			_pObjectImage->frameRender(hdc, _rcTile.left, _rcTile.top, 0, 0);
		}
	}

}

void TILE::release()
{
	_pImage = nullptr;
}

void TILE::settingTile(int nFrameX, int nFrameY, bool bIsWall, TILE::TERRIAN eTerrian, E_OBJECT object)
{
	setFrameX(nFrameX);
	setFrameY(nFrameY);
	setIsWall(bIsWall);
	setObject(object);
	setTerrian(eTerrian);
	if (!_bIsWall)
	{
		//지우는 경우
		//패스를 까는 경우
		setAroundWall(PASS);
	}
	else
	{
		_eObject = E_OBJECT::E_NONE;
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
	strTmp.append(to_string(static_cast<int>(_eObject)));
	strTmp.append("/");

	return strTmp;
}

bool TILE::setObject(TILE::E_OBJECT eObject)
{
	switch (eObject)
	{
	case TILE::E_OBJECT::E_TREE:
		_eObject = eObject;
		_eTerrian = TILE::TERRIAN::GROUND;
		break;

	case TILE::E_OBJECT::E_GOLDMINE:
		if (_eTerrian == TILE::TERRIAN::GROUND && _eObject == TILE::E_OBJECT::E_NONE)
		{
			_eObject = eObject;
		}
		else
		{
			return false;
		}
		break;
	case TILE::E_OBJECT::E_OILPATCH:
		if (_eTerrian == TILE::TERRIAN::WATER && _eObject == TILE::E_OBJECT::E_NONE)
		{
			_eObject = eObject;
		}
		else
		{
			return false;
		}
		break;
	case TILE::E_OBJECT::E_BUILDING:
		if (_eTerrian == TILE::TERRIAN::GROUND)
		{
			_eObject = eObject;
		}
		else
		{
			return false;
		}
		break;
	case TILE::E_OBJECT::E_UNIT:
		
		break;
	case TILE::E_OBJECT::E_MAX:
		
		break;
	default:
		break;
	}

	return true;
}

TILE::E_OBJECT TILE::getObject()
{
	return _eObject;
}

void TILE::move(int vertical, int horizontal)
{
	_rcTile.left += horizontal;
	_rcTile.right += horizontal;

	_rcTile.top += vertical;
	_rcTile.bottom += vertical;
}
