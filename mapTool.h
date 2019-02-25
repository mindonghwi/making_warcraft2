#pragma once

#include "stdafx.h"
#include "tile.h"
#include "camera.h"



class  MAPTOOL{
public:
	enum E_MAPTILEPOS
	{
		E_TOP			=	0x01,
		E_BOTTOM		=	0x02,
		E_LEFT			=0x04	,
		E_RIGHT			=0x08	,
		E_LEFT_TOP		=0x10	,
		E_RIGHT_TOP		=0x20	,
		E_LEFT_BOTTOM=	0x40	,
		E_RIGHT_BOTTOM=0x80
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

	//타일셋 범위(타일을 찍어올 팔레트 같은 역할)
	int		_nPalletSellCount = 2;

	int		_arFrameNum[141];//프레임 탐색 배열

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
	TILE::OBJECT	_object;

private:
	void	createMap();
	void	setResizeNodeIndex();
	void	initFrameBit();

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
	inline	void	setObject(TILE::OBJECT object) { _object = object; }

	inline	TILE*	getTile(int nX, int nY) { return _vvMap[nY][nX]; }
	
};