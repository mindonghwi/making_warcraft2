#include "stdafx.h"
#include "UICARD.h"
#include "unit.h"
#include "build.h"
UICARD::UICARD()
{
}

UICARD::~UICARD()
{
}


void UICARD::create(int nLeft, int nTop, UNIT * pUnit, BUILD * pBuild)
{
	_pImageCard = IMAGEMANAGER->findImage("card");
	_nLeft = nLeft;
	_nTop = nTop;

	if (pUnit == nullptr)
	{
		//ºôµå
		_eUiType = E_UITYPE::E_BUILD;

		_pBuild = pBuild;
		_pObjectImage = IMAGEMANAGER->findImage("buildIcon");
	}
	else if (pBuild == nullptr)
	{
		//À¯´Ö
		_eUiType = E_UITYPE::E_UNIT;
		_pUnit = pUnit;
		_pObjectImage = IMAGEMANAGER->findImage("unitIcon");
	}
}

void UICARD::update()
{
	if (_eUiType == E_UITYPE::E_UNIT)
	{
		_nHp = _pUnit->getHp();
		_nMaxHp = _pUnit->getMaxHp();
		_nAttack = _pUnit->getAttack();
		_nDefence = _pUnit->getDefence();
	}
	else if (_eUiType == E_UITYPE::E_BUILD)
	{
		_nHp = _pBuild->getHp();
		_nMaxHp = _pBuild->getMaxHp();
	}

	_nPrograssBarWidth = (int)((float)((float)_nHp) *  50.0f/(float)_nMaxHp);
	if (_nPrograssBarWidth > 30)
	{
		_pPrograssBar = IMAGEMANAGER->findImage("greenBar");
	}
	else if (_nPrograssBarWidth > 15)
	{
		_pPrograssBar = IMAGEMANAGER->findImage("yellowBar");
	}
	else
	{
		_pPrograssBar = IMAGEMANAGER->findImage("redBar");
	}
}

void UICARD::render(HDC hdc)
{
	if (_eUiType == E_UITYPE::E_UNIT)
	{
		char str[128];
		sprintf_s(str, "HP: %d", _nHp);
		TextOut(hdc, 50, 50, str, strlen(str));
		sprintf_s(str, "attack: %d", _nAttack);
		TextOut(hdc, 50, 70, str, strlen(str));
		sprintf_s(str, "defence: %d", _nDefence);
		TextOut(hdc, 50, 90, str, strlen(str));

		_pImageCard->render(hdc, _nLeft, _nTop);
		_pObjectImage->frameRender(hdc, _nLeft + 4, _nTop+4, (int)_pUnit->getUnit(), 0);
		_pPrograssBar->render(hdc, _nLeft +2, _nTop+ _pImageCard->GetHeight() - 7, 0, 0, _nPrograssBarWidth, 5);
	}
	else if (_eUiType == E_UITYPE::E_BUILD)
	{
		char str[128];
		sprintf_s(str, "HP: %d", _nHp);
		TextOut(hdc, 50, 50, str, strlen(str));
		_pImageCard->render(hdc, _nLeft, _nTop);
		_pObjectImage->frameRender(hdc, _nLeft + 4, _nTop + 4, (int)_pBuild->getBuildsTpye(), 0);
		_pPrograssBar->render(hdc, _nLeft + 2, _nTop + _pImageCard->GetHeight() - 7, 0, 0, _nPrograssBarWidth, 5);
	}
}

void UICARD::release()
{
	_pImageCard = nullptr;
	_pObjectImage = nullptr;
	_pPrograssBar = nullptr;
	_pUnit = nullptr;
	_pBuild = nullptr;
}
