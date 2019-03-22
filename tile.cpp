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

void TILE::settingTerrian()
{
	string strTmp = "";

	switch (_eTerrian)
	{
	case TILE::E_TERRIAN::GROUND:
		strTmp = "mapSprites";
		setFrameY(0);

		break;
	case TILE::E_TERRIAN::WATER:
		strTmp = "mapSprites";
		setFrameY(1);

		break;
	case TILE::E_TERRIAN::DIRT:
		strTmp = "mapSprites";
		setFrameY(2);

		break;
	case TILE::E_TERRIAN::WALL:
		break;
	case TILE::E_TERRIAN::ROCK:
		strTmp = "rock";
		setFrameY(0);
		break;
	case TILE::E_TERRIAN::TREE:
		break;
	case TILE::E_TERRIAN::MAX:
		break;
	default:
		break;
	}


	_pImage = IMAGEMANAGER->findImage(strTmp);
}

void TILE::init(int nTileLeft, int nTileTop, int nTileSize, image* pImg, int nNodeIndex)
{
	setAroundWall(PASS);
	setIsWall(false);
	setTerrian(TILE::E_TERRIAN::NONE);
	setImg(nullptr);
	setFrameX(0);
	setFrameY(0);
	setRectTile(nTileLeft, nTileTop, nTileSize, nTileSize);
	setImg(pImg);
	setNodeIndex(nNodeIndex);
	_eObject = E_OBJECT::E_NONE;
	setLimitRect(RectMake(0, 0, WINSIZEX, WINSIZEY));
	setIsObjectLoadCheck(false);
}

void TILE::render(HDC hdc)
{
	//지형만 출력한다.
	//오브젝트 출력은 따로 관리하고 타일에만 저장

	if (_rcCameraLimit.left<= _rcTile.right && 
		_rcCameraLimit.right  >= _rcTile.left &&
		_rcCameraLimit.top <= _rcTile.bottom &&
		_rcCameraLimit.bottom >= _rcTile.top )
	{
		_pImage->frameRender(hdc, _rcTile.left, _rcTile.top, _nFrameX, _nFrameY);

		//char str[128];
		//sprintf_s(str, "%d,%d", int(_eObject), int(_eTerrian));
		//TextOut(hdc, _rcTile.left, _rcTile.top , str, strlen(str));

	}

}

void TILE::renderBackGround(HDC hdc)
{
	_pImage->frameRender(hdc, _rcTile.left, _rcTile.top, _nFrameX, _nFrameY);
}

void TILE::release()
{
	_pImage = nullptr;
}

void TILE::settingTile(int nFrameX, int nFrameY, bool bIsWall, TILE::E_TERRIAN eTerrian, E_OBJECT object)
{
	setFrameX(nFrameX);
	setFrameY(nFrameY);
	setIsWall(bIsWall);
	setObject(object);
	setTerrian(eTerrian);

	settingTerrian();
}

void TILE::readjustWall(int nAroundWall, int nFrameX, int nFrameY)
{
	setAroundWall(nAroundWall);
	setFrameX(nFrameX);
	setFrameY(nFrameY);

	if (getObject() != TILE::E_OBJECT::E_NONE)
	{
		setObject(TILE::E_OBJECT::E_NONE);
	}
}

string TILE::makeSaveString()
{
	//노드인덱스/주변값/벽/프레임x/프레임y/object/terrian
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
	strTmp.append(to_string(static_cast<int>(_eTerrian)));
	strTmp.append("/");

	return strTmp;
}


void TILE::move(int vertical, int horizontal)
{
	_rcTile.left += horizontal;
	_rcTile.right += horizontal;

	_rcTile.top += vertical;
	_rcTile.bottom += vertical;
}

void TILE::extendLimitRect(int nOffset)
{
	_rcCameraLimit.left -= nOffset;
	_rcCameraLimit.top -= nOffset;
	_rcCameraLimit.right += nOffset;
	_rcCameraLimit.bottom += nOffset;
}
