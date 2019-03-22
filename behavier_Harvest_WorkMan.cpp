#include "stdafx.h"
#include "behavier_Harvest_WorkMan.h"
#include "unit.h"
#include "unitMGr.h"
#include "buildMgr.h"

BEHAVIER_HARVEST_WORKMAN::BEHAVIER_HARVEST_WORKMAN() :
	_fTimer(0.0f),
	_nCount(0)
{
}

BEHAVIER_HARVEST_WORKMAN::~BEHAVIER_HARVEST_WORKMAN()
{
}

void BEHAVIER_HARVEST_WORKMAN::update(UNIT * pUnit)
{
	//자원 채취중 자원 들양이 다차면 엔드
	_fTimer += TIMEMANAGER->getElapsedTime();
	if (pUnit->IsNearResources())
	{
		pUnit->getMyUnitMgr()->commandHarvestSingle(nullptr,pUnit);
	}
	else if (_fTimer >= 1.0f)
	{
		pUnit->harvestResources();
		_fTimer = 0.0f;
		_nCount++;
		if (_nCount >= 10)
		{
			end(pUnit);
		}
	}
}

void BEHAVIER_HARVEST_WORKMAN::end(UNIT * pUnit)
{
	float fDistacne = 128.0f * TILESIZE * 1.4f;
	fDistacne *= fDistacne;
	int nIndex = 201;
	for (int i = 0; i < pUnit->getMyBuildMgr()->getBuildCount(); i++)
	{
		if (pUnit->getHarvest() == UNIT::E_HARVEST::E_GOLD)
		{
			if (pUnit->getMyBuildMgr()->getBuild(i)->getBuildsTpye() == E_BUILDS::E_TOWN ||
				pUnit->getMyBuildMgr()->getBuild(i)->getBuildsTpye() == E_BUILDS::E_KEEP ||
				pUnit->getMyBuildMgr()->getBuild(i)->getBuildsTpye() == E_BUILDS::E_CASTLE)
			{
				float fTmp = Mins::getDoubleDis(pUnit->getPosX(), pUnit->getPosY(), pUnit->getMyBuildMgr()->getBuild(i)->getPosX(), pUnit->getMyBuildMgr()->getBuild(i)->getPosY());
				if (fTmp <= fDistacne)
				{
					nIndex = i;
					fDistacne = fTmp;
				}
				
			}
		}
		else if (pUnit->getHarvest() == UNIT::E_HARVEST::E_TREE) 
		{
			if (pUnit->getMyBuildMgr()->getBuild(i)->getBuildsTpye() == E_BUILDS::E_TOWN ||
				pUnit->getMyBuildMgr()->getBuild(i)->getBuildsTpye() == E_BUILDS::E_KEEP ||
				pUnit->getMyBuildMgr()->getBuild(i)->getBuildsTpye() == E_BUILDS::E_CASTLE ||
				pUnit->getMyBuildMgr()->getBuild(i)->getBuildsTpye() == E_BUILDS::E_LUMBER_MILL)
			{
				float fTmp = Mins::getDoubleDis(pUnit->getPosX(), pUnit->getPosY(), pUnit->getMyBuildMgr()->getBuild(i)->getPosX(), pUnit->getMyBuildMgr()->getBuild(i)->getPosY());
				if (fTmp <= fDistacne)
				{
					nIndex = i;
					fDistacne = fTmp;
				}
			}
		}
	}

	pUnit->setCurrentBehavir(UNIT::E_BEHAVIERNUM::E_NONE);
	pUnit->setCurrentState(UNIT::E_STATENUM::E_IDLE);
	pUnit->setBehavier(UNIT::E_BEHAVIERNUM::E_NONE);
	pUnit->getCurrentState()->start();
	pUnit->setTarget(nullptr);
	pUnit->addMapUnitData();
	pUnit->setIsHold(false);
	if (nIndex != 201)
	{
		pUnit->getMyUnitMgr()->commandMoveSingle(pUnit->getMyBuildMgr()->getBuild(nIndex)->getPosX(), pUnit->getMyBuildMgr()->getBuild(nIndex)->getPosY(), pUnit);
	}

	_fTimer = 0.0f;
	_nCount = 0;
}
