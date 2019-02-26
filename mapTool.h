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
	TILE::E_OBJECT	_object;


	int		_nBrushSize;		//���� ������ �귯�� ������

	CAMERA*		_pCamera;
private:
	void	createMap();
	void	setResizeNodeIndex();

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
	inline	void	setObject(TILE::E_OBJECT object) { _object = object; }

	inline	TILE*	getTile(int nX, int nY) { return _vvMap[nY][nX]; }
	

	inline	void	setCamera(CAMERA* pCamera) { _pCamera = pCamera; }
};