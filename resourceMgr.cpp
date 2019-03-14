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

int RESOURCEMGR::clickedResources(POINT ptMouse)
{
	list<GOLDMINE*>::iterator iter = _listGoldMine.begin();
	list<GOLDMINE*>::iterator end = _listGoldMine.end();
	while (iter != end)
	{
		if (PtInRect((*iter)->getRect(),ptMouse))
		{
			return (int)E_RESOURCE::E_GOLD;
		}
		iter++;
	}

	list<TREE*>::iterator iterTree = _listTree.begin();
	list<TREE*>::iterator endTree = _listTree.end();
	while (iterTree != endTree)
	{
		if (PtInRect((*iterTree)->getRect(), ptMouse))
		{
			return (int)E_RESOURCE::E_TREE;
		}
		iterTree++;
	}

	list<OILPATCH*>::iterator iterOil = _listOilPatch.begin();
	list<OILPATCH*>::iterator endOil = _listOilPatch.end();
	while (iterOil != endOil)
	{
		if (PtInRect((*iterOil)->getRect(), ptMouse))
		{
			return (int)E_RESOURCE::E_OIL;
		}		
		iterOil++;
	}


	return (int)E_RESOURCE::E_MAX;
}

GOLDMINE * RESOURCEMGR::getSelectGoldMine(POINT ptMouse)
{

	list<GOLDMINE*>::iterator iter = _listGoldMine.begin();
	list<GOLDMINE*>::iterator end = _listGoldMine.end();
	while (iter != end)
	{
		if (PtInRect((*iter)->getRect(), ptMouse))
		{
			return (*iter);
		}
		iter++;
	}
	return nullptr;
}

TREE * RESOURCEMGR::getSelectTree(POINT ptMouse)
{
	list<TREE*>::iterator iterTree = _listTree.begin();
	list<TREE*>::iterator endTree = _listTree.end();
	while (iterTree != endTree)
	{
		if (PtInRect((*iterTree)->getRect(), ptMouse))
		{
			return (*iterTree);
		}
		iterTree++;
	}

	return nullptr;
}

OILPATCH * RESOURCEMGR::getSelectOilPatch(POINT ptMouse)
{
	list<OILPATCH*>::iterator iterOil = _listOilPatch.begin();
	list<OILPATCH*>::iterator endOil = _listOilPatch.end();
	while (iterOil != endOil)
	{
		if (PtInRect((*iterOil)->getRect(), ptMouse))
		{
			return (*iterOil);
		}
		iterOil++;
	}
	return nullptr;
}

RESOURCES * RESOURCEMGR::getResource(POINT ptMouse)
{
	list<GOLDMINE*>::iterator iter = _listGoldMine.begin();
	list<GOLDMINE*>::iterator end = _listGoldMine.end();
	while (iter != end)
	{
		if (PtInRect((*iter)->getRect(), ptMouse))
		{
			return *iter;
		}
		iter++;
	}

	list<TREE*>::iterator iterTree = _listTree.begin();
	list<TREE*>::iterator endTree = _listTree.end();
	while (iterTree != endTree)
	{
		if (PtInRect((*iterTree)->getRect(), ptMouse))
		{
			return *iterTree;
		}
		iterTree++;
	}

	list<OILPATCH*>::iterator iterOil = _listOilPatch.begin();
	list<OILPATCH*>::iterator endOil = _listOilPatch.end();
	while (iterOil != endOil)
	{
		if (PtInRect((*iterOil)->getRect(), ptMouse))
		{
			return *iterOil;
		}
		iterOil++;
	}


	return nullptr;
}

GOLDMINE * RESOURCEMGR::getfindNearGoldMine(float fPosX, float fPosY)
{
	list<GOLDMINE*>::iterator iter = _listGoldMine.begin();
	list<GOLDMINE*>::iterator end = _listGoldMine.end();
	float fDistance = Mins::getDoubleDis((*iter)->getPosX(), (*iter)->getPosY(), fPosX, fPosY);
	iter++;
	float fTmp = 0.0f;
	int nIndex = 0;

	int nCount = 1;
	while (iter != end)
	{
		fTmp = Mins::getDoubleDis((*iter)->getPosX(), (*iter)->getPosY(), fPosX, fPosY);
		if (fDistance >= fTmp)
		{
			fDistance = fTmp;
			nIndex = nCount;
		}
		iter++;
		nCount++;
	}

	iter = _listGoldMine.begin();
	
	for (int i = 0; i < nIndex; i++)
	{
		iter++;
	}

	return *iter;
}

TREE * RESOURCEMGR::getfindNearTree(float fPosX, float fPosY)
{
	list<TREE*>::iterator iter = _listTree.begin();
	list<TREE*>::iterator end = _listTree.end();
	float fDistance = Mins::getDoubleDis((*iter)->getPosX(), (*iter)->getPosY(), fPosX, fPosY);
	iter++;
	float fTmp = 0.0f;
	int nIndex = 0;

	int nCount = 1;
	while (iter != end)
	{
		fTmp = Mins::getDoubleDis((*iter)->getPosX(), (*iter)->getPosY(), fPosX, fPosY);
		if (fDistance >= fTmp)
		{
			fDistance = fTmp;
			nIndex = nCount;
		}
		iter++;
		nCount++;
	}

	iter = _listTree.begin();

	for (int i = 0; i < nIndex; i++)
	{
		iter++;
	}

	return *iter;
}
