#pragma once

#include "stdafx.h"
#include "image.h"
#include "object.h"

//렌더를 바꾸어야한다.
//y축 순으로 정렬

//최종 y오더 치는 지형 높이 + 오브젝트 높이
//길높이 + 플레이어
//길높이는 행단위로 같다.
//오브젝트 높이는 다 다르다.
//y축이 클수록 지형의 y오더치가 높아진다.


class CAMERA {
private:
	float _posX;			//중심x			(투영영역)
	float _posY;			//중심y			(투영영역)
	int _width;				//화면의 가로길이(투영영역)
	int _height;			//화면의 세로길이(투영영역)
	int	_left;				//그릴 영역 left	(투영영역)
	int _top;				//그릴영역 right	(투영영역)
	image* _pCameraBuffer;
	bool	_isMoving;		
	float	_time;
	float	_travelRangeX;
	float	_travelRangeY;
	RECT	_rcCameraLimit;
	
	list<OBJECT*>		_listRenderObject;
	int		_nMapWidth;		//맵의 가로	(World)
	int		_nMapHeight;	//맵의 세로	(World)

	image*	_pBackGroundBuffer;

	int		_nCameraLimitRight;
	int		_nCameraLimitBottom;

public:
	CAMERA();
	~CAMERA();
	
	void init(int posX, int posY, int windowWidth, int windowHeight,int mapWidth,int mapHeight);
	void update();

	void render(HDC hdc);
	void release();
	void renderinit();
	void	setting(int nPosX,int nPosY);										//중점 좌표를 잡는다
	void	settingCameraRange(int nLeft, int nTop, int nRight, int nBottom);	//카메라 그리는 영역을 설정
private:
	void	setLeftTop();

public:

	void	moveRight(float offset);
	void	moveLeft(float offset);
	void	moveUp(float offset);
	void	moveDown(float offset);

	void	outOfRange();

public:
	inline	int	getLeft() { return _left; }
	inline	int	getTop() { return _top; }
	inline	int	getRight() { return _left + _width; }
	inline	int	getBotton() { return _top + _height; }
	inline	int	getWidth() { return _width; }
	inline	int	getHeight() { return _height; }
	inline	bool getMoving() { return _isMoving; }

	inline	RECT getLimitRect() { return _rcCameraLimit; }


public:
	image * getCameraBuffer() { return _pCameraBuffer; }
	HDC getMemDC() { return _pCameraBuffer->getMemDC(); }
	void	setCameraBuffer(image* pImg);
	void	pushRenderObject(OBJECT* pObject);


	HDC	getBackGoroundBuffer() { return _pBackGroundBuffer->getMemDC(); }

	void	setLimitToTile(int nTileCountX,int nTileCountY);
};
