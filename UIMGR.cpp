#include "stdafx.h"
#include "UIMGR.h"
#include "unitMGr.h"
#include "unit.h"
#include "buildMgr.h"
#include "player.h"

UIMGR::UIMGR()
{
}

UIMGR::~UIMGR()
{
}

void UIMGR::init()
{
	for (int i = 0; i < 9; i++)
	{
		_arUiCard[i] = new UICARD();
		
	}

	_pUi = new UI();
	_pUi->init(_pPlayer);

	_nCount = 0;
}

void UIMGR::update()
{
	_nCount = 0;
	_pUi->update();

	for (int i = 0; i < _pPlayer->getUnitMgr()->getUnitSelectedCount(); i++)
	{
		_arUiCard[i]->create(280 + i * 54,WINSIZEY - 77,_pPlayer->getUnitMgr()->getSelectedUnit(i));
		_arUiCard[i]->update();
		_nCount++;
	}

	if (_pPlayer->getBuildMgr()->getSelectedBuild())
	{
		_arUiCard[0]->create(280, WINSIZEY - 77,nullptr, _pPlayer->getBuildMgr()->getSelectedBuild());
		_arUiCard[0]->update();
		_nCount = 1;
	}
}

void UIMGR::release()
{
	_pPlayer = nullptr;

	for (int i = 0; i < 9; i++)
	{
		_arUiCard[i]->release();
		delete _arUiCard[i];
		_arUiCard[i] = nullptr;
	}

	_pUi->release();
	delete	_pUi;
	_pUi = nullptr;
}

void UIMGR::render(HDC hdc)
{
	_pUi->render(hdc);

	for (int i = 0; i <_nCount; i++)
	{
		_arUiCard[i]->render(hdc);

	}

}
