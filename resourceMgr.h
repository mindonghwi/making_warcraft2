#pragma once
#include "camera.h"
#include "goldMine.h"
#include "tree.h"
#include "oliPatch.h"
#include "map.h"

class MAP;

class RESOURCEMGR
{
private:
	CAMERA*		_pCamera;
	MAP*		_pMap;

	list<GOLDMINE*> _listGoldMine;
	list<TREE*>		_listTree;
	list<OILPATCH*>	_listOilPatch;

public:
	void	init();
	void	release();
	void	update();
	

	inline	void	setLinkCamera(CAMERA* pCamera) { _pCamera = pCamera; }
	inline	void	setLinkMap(MAP* pMap) { _pMap = pMap; }

	void	addGoldMine(int nLeft, int nTop);
	void	addTree(int nLeft, int nTop);
	void	addOilPatch(int nLeft, int nTop);
};