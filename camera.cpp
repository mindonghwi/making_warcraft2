#include "stdafx.h"
#include "camera.h"

CAMERA::CAMERA()
{
}

CAMERA::~CAMERA()
{
}



void CAMERA::init(int posX, int posY, int windowWidth, int windowHeight, int mapWidth, int mapHeight)
{
	_posX = static_cast<float>(posX);
	_posY = static_cast<float>(posY);
	_width = windowWidth;
	_height = windowHeight;
	setLeftTop();
	_nMapHeight = mapHeight;
	_nMapWidth = mapWidth;

	_rcCameraLimit = { 0,0,_nMapWidth,_nMapHeight };

	_pCameraBuffer = IMAGEMANAGER->addImage("camera", _nMapWidth, _nMapHeight);
	_pBackGroundBuffer = IMAGEMANAGER->addImage("backGroundBuffer", _nMapWidth, _nMapHeight);

	_listRenderObject.clear();

	_posY += TILESIZE;
}

void CAMERA::update()
{
	_listRenderObject.clear();


	if (KEYMANAGER->isStayKeyDown(VK_UP))	
	{
		moveUp(10);
	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN))	
	{
		moveDown(10);
	}
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))	
	{
		moveLeft(10);

	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		moveRight(10);
	}


	


	_rcCameraLimit = RectMake( _left,_top, _width, _height);

	//outOfRange();
}

void CAMERA::render(HDC hdc)
{
	list<OBJECT*>::iterator	iter = _listRenderObject.begin();
	list<OBJECT*>::iterator	end = _listRenderObject.end();

	while (iter != end)
	{
		OBJECT* pObject = (*iter);
		//클러핑
		if (pObject->getPosX() > _left - pObject->getWidth() &&
			pObject->getPosY() > _top - pObject->getHeight() &&
			pObject->getPosX() < _left + _width + pObject->getWidth() &&
			pObject->getPosY() < _top + _height + pObject->getHeight())
		{
			pObject->render(getMemDC());
		}
		iter++;
	}

	_pCameraBuffer->render(hdc, 0, 0, _left, _top, _width, _height);
}

void CAMERA::release()
{
	_listRenderObject.clear();
}

void CAMERA::renderinit()
{
	//PatBlt(_pCameraBuffer->getMemDC(), 0, 0, _nMapWidth, _nMapHeight, BLACKNESS);
	BitBlt(_pCameraBuffer->getMemDC(), _left, _top, _nMapWidth, _nMapWidth, _pBackGroundBuffer->getMemDC(), _left, _top, SRCCOPY);
}

void CAMERA::setting(int nPosX, int nPosY)
{
	_posX = static_cast<float>(nPosX);
	_posY = static_cast<float>(nPosY);
	//outOfRange();
	setLeftTop();
}



void CAMERA::settingCameraRange(int nLeft, int nTop, int nRight, int nBottom)
{
	_rcCameraLimit = { nLeft,nTop,nRight,nBottom };
}

void CAMERA::setLeftTop()
{
	_left = static_cast<int>(_posX) - _width / 2;
	_top  = static_cast<int>(_posY) - _height / 2;
}

void CAMERA::moveRight(float offset)
{
	_posX += offset;
	if (_posX + _width / 2 >= _nCameraLimitRight - TILESIZE)
	{
		_posX = static_cast<float>(_nCameraLimitRight - _width / 2) - TILESIZE;
	}
	setLeftTop();

}

void CAMERA::moveLeft(float offset)
{
	_posX -= offset;
	//사방향 한칸씩 여유공간으로 막기
	if (_posX - _width / 2 <= TILESIZE)
	{
		_posX = static_cast<float>(_width / 2) + TILESIZE;
	}
	setLeftTop();

}

void CAMERA::moveUp(float offset)
{
	_posY -= offset;
	if (_posY - _height / 2 <= TILESIZE)
	{
		_posY = static_cast<float>(_height / 2) + TILESIZE;
	}
	setLeftTop();

}

void CAMERA::moveDown(float offset)
{
	_posY += offset;

	if (_posY + _height / 2 >= _nCameraLimitBottom - TILESIZE)
	{
		_posY = static_cast<float>(_nCameraLimitBottom - _height / 2) - TILESIZE;
	}
	setLeftTop();
}

void CAMERA::outOfRange()
{
	if (_posX + _width / 2 >= _nCameraLimitRight - TILESIZE)
	{
		_posX = static_cast<float>(_nCameraLimitRight - _width / 2) - TILESIZE;
	}
	else if (_posX - _width / 2 <= TILESIZE)
	{
		_posX = static_cast<float>(_width / 2) + TILESIZE;
	}
	if (_posY - _height / 2 <= TILESIZE)
	{
		_posY = static_cast<float>(_height / 2) + TILESIZE;
	}
	else if (_posY + _height / 2 >= _nCameraLimitBottom - TILESIZE)
	{
		_posY = static_cast<float>(_nCameraLimitBottom - _height / 2) - TILESIZE;
	}

	setLeftTop();

}

void CAMERA::setCameraBuffer(image * pImg)
{
	_pCameraBuffer = pImg;
	_nMapHeight = _pCameraBuffer->GetHeight();
	_nMapWidth = _pCameraBuffer->GetWidth();
}

void CAMERA::pushRenderObject(OBJECT * pObject)
{
	//정렬도 되야한다
	float fZorder = pObject->getPosY();// +static_cast<float>(pObject->getPosZ());

	list<OBJECT*>::iterator	iter = _listRenderObject.begin();
	list<OBJECT*>::iterator	end = _listRenderObject.end();

	bool bIsSearch = false;

	while (iter != end)
	{
		float fTmp = (*iter)->getPosY();// +static_cast<float>((*iter)->getPosZ());
		if (fTmp > fZorder)
		{
			_listRenderObject.insert(iter, pObject);
			iter = end;
			bIsSearch = true;
		}
		else
		{
			iter++;
		}
	}

	if (!bIsSearch)
	{
		_listRenderObject.push_back(pObject);
	}

}

void CAMERA::setLimitToTile(int nTileCountX, int nTileCountY)
{
	_nCameraLimitRight = nTileCountX * TILESIZE;
	_nCameraLimitBottom = nTileCountY * TILESIZE;
}
