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
	setFrameX(0);
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
	//지형만 출력한다.
	//오브젝트 출력은 따로 관리하고 타일에만 저장

	if (_rcCameraLimit.left <= _rcTile.right && 
		_rcCameraLimit.right >= _rcTile.left &&
		_rcCameraLimit.top <= _rcTile.bottom &&
		_rcCameraLimit.bottom >= _rcTile.top )
	{
		_pImage->frameRender(hdc, _rcTile.left, _rcTile.top, _nFrameX, _nFrameY);
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


void TILE::move(int vertical, int horizontal)
{
	_rcTile.left += horizontal;
	_rcTile.right += horizontal;

	_rcTile.top += vertical;
	_rcTile.bottom += vertical;
}
