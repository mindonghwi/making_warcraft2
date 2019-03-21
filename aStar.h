#pragma once

#include "stdafx.h"
#include "tile.h"
#include "map.h"

class PLAYER;
class UNITMGR;
class BUILDMGR;

class ASTAR {
public:
	struct TILENODE
	{
		int			nIndexX;
		int			nIndexY;
		int			nPathStartToCurrent;
		int			nPathCurrentToEnd;
		int			nPathToatalCost;
		TILENODE*	parrentNode;
	};

	enum POS
	{
		POSX = 0,
		POSY,
		MAX
	};

	enum MOVEHEIGHT
	{
		GROUND = 0,
		WATER,
		FLY
	};
	

private:
	list<TILENODE*>				_listOpendNode;		//Ž���� �Ҽ� �ִ� ������ ����.
	list<TILENODE*>				_listClosedyPath;	//Ž���� ���� ������ ����.
	list<TILENODE*>				_listMaximumPath;	//������ ��ε��� ��� ����Ʈ
	vector<vector<TILENODE*>>	_vvTile;			//ã�ƺ� Ÿ�� �迭
	
	//						  ��		  ��			��		��		�»�      ���     ����    ����
	int	_arInterval[8][2]{ { 0,-1 },{ 0,1 },{ -1,0 },{ 1,0 },{ -1,-1 },{ 1,-1 },{ -1,1 },{ 1,1 } };
	int	_arHuristic[8]{		  10,	  10,	   10,		10,		14,		  14,		14,		14 };

	int				_nTileSizeX;
	int				_nTileSizeY;

	int				_nStartIndexX;
	int				_nStartIndexY;
	int				_nEndIndexX;
	int				_nEndIndexY;

	int				_nSearchLength;//4�� 8
	MAP*			_pMap;

	MOVEHEIGHT		_eMoveHeight;

	PLAYER*			_pPlayer;
	UNITMGR*		_pUnitMgr;
	BUILDMGR*		_pBuildMgr;
								//		��		������		�Ʒ�				����
	int				_arSnake[4][2] { { 0,-1 },	{ 1,0 },	{ 0,1 },	{ -1,0 } };
	
public:
	ASTAR();
	~ASTAR();
	void	init(int nSearchLength,MAP* pMap);
	//��� Ÿ�Ͽ� �ִ��� �ִ� �Լ�
	void	startFinder(int nStartIndexX, int nStartIndexY, int nEndIndexX, int nEndIndexY, MOVEHEIGHT eMoveHeight);
	void	startFinder(float fStartPosX, float fStartPosY, float fEndPosX, float fEndPosY, MOVEHEIGHT eMoveHeight);
	void	startFinderArray(float fStartPosX, float fStartPosY, float fEndPosX, float fEndPosY, MOVEHEIGHT eMoveHeight,int* nIndex);


	void	pathFinder();	

	
	void	release();


	list<TILENODE*>&		getPath() { return _listMaximumPath; }
	int		getListSize() { return static_cast<int>(_listMaximumPath.size()); }
	TILENODE*	getNode(int nIndex);
	bool	bIsEmety() { return _listMaximumPath.empty(); }

	void	setLinkUnitMgr(PLAYER* _pPlayer);

	void	search();

private:
	void	initMap();
};