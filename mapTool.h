#pragma once

#include "stdafx.h"
#include "tile.h"

class CAMERA;

class  MAPTOOL{
public:
	enum E_MAPTILEPOS
	{
		E_NONE			=	0x00,
		E_TOP			=	0x01,
		E_BOTTOM		=	0x02,
		E_LEFT			=	0x04,
		E_RIGHT			=	0x08
	};


public:
	MAPTOOL();
	~MAPTOOL();
private:
	//한 타일의 사이즈는 32로 한다. 32 X 32
	int		_nTileSize;

	//타일 갯수는 가로 20 / 세로 20
	int		_nTileCountX;
	int		_nTileCountY;

	//타일 총 사이즈는 640 X 640
	int		_nMapWidth;
	int		_nMapHeight;



	int		_nCurrentTileX;	//현재 선택되어있는 타일x
	int		_nCurrentTileY;	//현재 선택되어있는 타일y
	//맵
	vector<vector<TILE*>>	_vvMap;
	//맵 frame
	image*	_pImgMap;
	image*	_pObjectImg;



	int		_nVertical;
	int		_nHorizontal;
	bool	_bIsWall;
	TILE::E_OBJECT	_object;


	int		_nBrushSize;		//실제 찍히는 브러시 사이즈

	CAMERA*		_pCamera;
private:
	void	createMap();
	void	setResizeNodeIndex();

	string	setSaveMapTool();
	string	makeSaveMap();
public:
	//기본 셋
	void	init(int nTileCountX,int nTileCountY,int nTileSize);
	void	release();
	void	render(HDC hdc);
	void	update();
	//추가분
	void	mapResize(int nTileCountX,int nTileCountY);
	void	readjustMap();

	void	save();
	void	load();
	
;

	void	deleteObject();

	inline	int		getMapCountX() { return _nTileCountX; }
	inline	int		getMapCountY() { return _nTileCountY; }
	inline	int		getTileSize() { return _nTileSize; }
	inline	void	setCurrentX(int nCurrentX) {_nCurrentTileX = nCurrentX;}
	inline	void	setCurrentY(int nCurrentY){ _nCurrentTileY = nCurrentY; }
	inline	void	setisWall(bool bIsWall) { _bIsWall = bIsWall; }
	inline	void	setObject(TILE::E_OBJECT object) { _object = object; }

	inline	TILE*	getTile(int nX, int nY) { return _vvMap[nY][nX]; }
	

	inline	void	setCamera(CAMERA* pCamera) { _pCamera = pCamera; }
};