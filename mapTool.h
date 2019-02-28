#pragma once

#include "stdafx.h"
#include "tile.h"
#include "goldMine.h"
#include "tree.h"
#include "oliPatch.h"

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

	enum class E_DIAGONAL
	{
		E_NONE = 0,
		E_NORTH_WEST = 1,
		E_NORTH_EAST = 2,
		E_SOUTH_WEST = 3,
		E_SOUTH_EAST = 4
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


	int		_nBrushSize;		//실제 찍히는 브러시 사이즈

	CAMERA*		_pCamera;

	TILE::E_TERRIAN	_eTerrian;
	TILE::E_OBJECT	_eObject;
	
	//						  상		  하			좌		우		좌상      우상     좌하    우하
	int	_arInterval[8][2]{ { 0,-1 },{ 0,1 },{ -1,0 },{ 1,0 },{ -1,-1 },{ 1,-1 },{ -1,1 },{ 1,1 } };

	int	_arReadjustMap[6];


	list<GOLDMINE*> _listGoldMine;
	list<TREE*>		_listTree;
	list<OILPATCH*>	_listOilPatch;
private:
	void	createMap();
	void	setResizeNodeIndex();

	string	setSaveMapTool();
	string	makeSaveMap();


	void	drawMap(int nIndexX,int nIndexY);

	void	drawObject(int nIndexX, int nIndexY);
public:
	//기본 셋
	void	init(int nTileCountX,int nTileCountY,int nTileSize);
	void	release();
	void	render(HDC hdc);
	void	update();
	//추가분
	void	mapResize(int nTileCountX,int nTileCountY);
	bool	readjustMap();
	bool	readjustObject();
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
	inline	void	setObject(TILE::E_OBJECT object) { _eObject = object; }
	inline	void	setTerrian(TILE::E_TERRIAN eTerrian) { _eTerrian = eTerrian; }
	inline	TILE*	getTile(int nX, int nY) { return _vvMap[nY][nX]; }
	

	inline	void	setCamera(CAMERA* pCamera) { _pCamera = pCamera; }



private:
	//object - resource
	void	drawGoldMine(int nIndexX, int nIndexY);
	void	drawTree(int nIndexX, int nIndexY);
	void	readjustGoldMine();
	void	reAdjustTree();
	void	drawOilPatch(int nIndexX, int nIndexY);
	void	readjustOilPatch();

	//tile - terrian
	void	readjustRock();
};