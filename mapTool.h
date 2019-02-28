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
	//�� Ÿ���� ������� 32�� �Ѵ�. 32 X 32
	int		_nTileSize;

	//Ÿ�� ������ ���� 20 / ���� 20
	int		_nTileCountX;
	int		_nTileCountY;

	//Ÿ�� �� ������� 640 X 640
	int		_nMapWidth;
	int		_nMapHeight;



	int		_nCurrentTileX;	//���� ���õǾ��ִ� Ÿ��x
	int		_nCurrentTileY;	//���� ���õǾ��ִ� Ÿ��y
	//��
	vector<vector<TILE*>>	_vvMap;
	//�� frame
	image*	_pImgMap;
	image*	_pObjectImg;



	int		_nVertical;
	int		_nHorizontal;
	bool	_bIsWall;


	int		_nBrushSize;		//���� ������ �귯�� ������

	CAMERA*		_pCamera;

	TILE::E_TERRIAN	_eTerrian;
	TILE::E_OBJECT	_eObject;
	
	//						  ��		  ��			��		��		�»�      ���     ����    ����
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
	//�⺻ ��
	void	init(int nTileCountX,int nTileCountY,int nTileSize);
	void	release();
	void	render(HDC hdc);
	void	update();
	//�߰���
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