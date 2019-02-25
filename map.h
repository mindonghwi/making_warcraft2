#pragma once
#include "tile.h"
#include "camera.h"


class MAP
{
public:
	MAP();
	~MAP();
private:
	//�� Ÿ���� ������� 32�� �Ѵ�. 32 X 32
	int		_nTileSize;

	//Ÿ�� ������ ���� 20 / ���� 20
	int		_nTileCountX;
	int		_nTileCountY;

	//Ÿ�� �� ������� 640 X 640
	int		_nMapWidth;
	int		_nMapHeight;

							
	vector<vector<TILE*>>	_vvMap;//��

	//�� frame
	image*	_pImgMap;
	image*	_pObjectImg;

	//ī�޶�

	int		_nVertical;
	int		_nHorizontal;
	bool	_bIsWall;
	TILE::E_OBJECT	_object;

	string	_strMapName;


private:
	void	createMap();
	
public:
	//�⺻ ��
	void	init(const char* mapName);
	void	release();
	void	render(HDC hdc);
	void	update();
	//�߰���

	void	load();


	
	//������Ʈ�� Ÿ�� ��ǥ�� ��µ� 
	bool	getObjectPos(vector<vector<int>>& _vvTileIndex, TILE::E_OBJECT object);

	void	deleteObject();

	inline	int		getMapCountX() { return _nTileCountX; }
	inline	int		getMapCountY() { return _nTileCountY; }
	inline	int		getTileSize() { return _nTileSize; }
	inline	void	setisWall(bool bIsWall) { _bIsWall = bIsWall; }

	inline	TILE*	getTile(int nX, int nY) { return _vvMap[nY][nX]; }

};
