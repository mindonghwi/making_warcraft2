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

void UICARD::create(UNIT * pUnit, BUILD * pBuild)
{
	if (pUnit == nullptr)
	{
		//ºôµå
		_eUiType = E_UITYPE::E_BUILD;

		_pBuild = pBuild;
		_pImageCard;
		_pObjectImage;
		_pPrograssBar;
	}
	else if (pBuild == nullptr)
	{
		//À¯´Ö
		_eUiType = E_UITYPE::E_UNIT;
		_pUnit = pUnit;
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
}

void UICARD::render(HDC hdc)
{
	if (_eUiType == E_UITYPE::E_UNIT)
	{

	}
	else if (_eUiType == E_UITYPE::E_BUILD)
	{

	}
}

void UICARD::release()
{
	_pImageCard = nullptr;
	_pObjectImage= nullptr;
	_pPrograssBar= nullptr;
}
