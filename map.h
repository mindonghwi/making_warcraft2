#pragma once
#include "tile.h"
#include "camera.h"
#include "goldMine.h"
#include "tree.h"
#include "oliPatch.h"
#include "resourceMgr.h"


class MAP
{

public:
	MAP();
	~MAP();
private:
	//한 타일의 사이즈는 32로 한다. 32 X 32
	int		_nTileSize;

	//타일 갯수는 가로 20 / 세로 20
	int		_nTileCountX;
	int		_nTileCountY;

	//타일 총 사이즈는 640 X 640
	int		_nMapWidth;
	int		_nMapHeight;

							
	vector<vector<TILE*>>	_vvMap;//맵

	//맵 frame
	image*	_pImgMap;
	image*	_pObjectImg;

	//카메라

	int		_nVertical;
	int		_nHorizontal;
	bool	_bIsWall;
	TILE::E_OBJECT	_object;

	string	_strMapName;

	CAMERA*		_pCamera;

	list<GOLDMINE*> _listGoldMine;
	list<TREE*>		_listTree;
	list<OILPATCH*>	_listOilPatch;

	RESOURCEMGR*		_pResourceMgr;

private:
	void	createMap();
	
public:
	//기본 셋
	void	init(const char* mapName);
	void	release();
	void	render(HDC hdc);
	void	update();

	void	drawMap(HDC hdc);

	
	//추가분
	void	load();
	void	loadObject();
	
	//오브젝트의 타일 좌표를 얻는데 
	bool	getObjectPos(vector<vector<int>>& _vvTileIndex, TILE::E_OBJECT object);

	void	deleteObject();

	inline	int		getMapCountX() { return _nTileCountX; }
	inline	int		getMapCountY() { return _nTileCountY; }
	inline	int		getTileSize() { return _nTileSize; }
	inline	void	setisWall(bool bIsWall) { _bIsWall = bIsWall; }

	inline	TILE*	getTile(int nX, int nY) { return _vvMap[nY][nX]; }

	inline	void	setLinkCamera(CAMERA* pCamera) { _pCamera = pCamera; }
	inline	void	setLinkResourceMgr(RESOURCEMGR* pResourceMgr) { _pResourceMgr = pResourceMgr; }



	void	readjust();


};
