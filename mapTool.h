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
	//�� Ÿ���� ������� 32�� �Ѵ�. 32 X 32
	int		_nTileSize;

	//Ÿ�� ������ ���� 20 / ���� 20
	int		_nTileCountX;
	int		_nTileCountY;

	//Ÿ�� �� ������� 640 X 640
	int		_nMapWidth;
	int		_nMapHeight;

	//Ÿ�ϼ� ����(Ÿ���� ���� �ȷ�Ʈ ���� ����)
	int		_nPalletSellCount = 2;

	int		_arFrameNum[141];//������ Ž�� �迭

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
	TILE::OBJECT	_object;

private:
	void	createMap();
	void	setResizeNodeIndex();
	void	initFrameBit();

	string	setSaveMapTool();
	string	makeSaveMap();
public:
	//�⺻ ��
	void	init(int nTileCountX,int nTileCountY,int nTileSize);
	void	release();
	void	render(HDC hdc);
	void	update();
	//�߰���
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