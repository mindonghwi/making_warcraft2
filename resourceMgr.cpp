#include "stdafx.h"
#include "resourceMgr.h"

void RESOURCEMGR::init()
{
}

void RESOURCEMGR::release()
{
}

void RESOURCEMGR::update()
{
	//resource push the Camera
	list<GOLDMINE*>::iterator iter = _listGoldMine.begin();
	list<GOLDMINE*>::iterator end = _listGoldMine.end();
	while (iter != end)
	{
		(*iter)->update();
		iter++;
	}

	list<TREE*>::iterator iterTree = _listTree.begin();
	list<TREE*>::iterator endTree = _listTree.end();
	while (iterTree != endTree)
	{
		(*iterTree)->update();
		iterTree++;
	}

	list<OILPATCH*>::iterator iterOil = _listOilPatch.begin();
	list<OILPATCH*>::iterator endOil = _listOilPatch.end();
	while (iterOil != endOil)
	{
		(*iterOil)->update();
		iterOil++;
	}
}

void RESOURCEMGR::addGoldMine(int nLeft, int nTop)
{
	_listGoldMine.push_back(new GOLDMINE);
	_listGoldMine.back()->linkCamera(_pCamera);
	_listGoldMine.back()->init(nLeft, nTop);
	_listGoldMine.back()->setResourceCount(15000);
}

void RESOURCEMGR::addTree(int nLeft, int nTop)
{
	_listTree.push_back(new TREE);
	_listTree.back()->linkCamera(_pCamera);
	_listTree.back()->init(nLeft, nTop);
	_listTree.back()->setResourceCount(1500);
}

void RESOURCEMGR::addOilPatch(int nLeft, int nTop)
{
	_listOilPatch.push_back(new OILPATCH);
	_listOilPatch.back()->linkCamera(_pCamera);
	_listOilPatch.back()->init(nLeft, nTop);
	_listOilPatch.back()->setResourceCount(15000);
}
