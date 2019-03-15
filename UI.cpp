#include "stdafx.h"
#include "UI.h"

UI::UI()
{
}

UI::~UI()
{
}

void UI::create(UNIT * pUnit, BUILD * pBuild)
{
	_pImageCard;
	_pObjectImage;
	_pPrograssBar;


	if (pUnit == nullptr)
	{
		//ºôµå
		_eUiType = E_UITYPE::E_BUILD;
		
		_pBuild = pBuild;

	}
	else if (pBuild == nullptr)
	{
		//À¯´Ö
		_eUiType = E_UITYPE::E_UNIT;
		_pUnit = pUnit;
	}
}

void UI::update()
{
	if (_eUiType == E_UITYPE::E_UNIT)
	{

	}

}

void UI::render(HDC hdc)
{
	if (_eUiType == E_UITYPE::E_UNIT)
	{

	}
	else if (_eUiType == E_UITYPE::E_BUILD)
	{

	}
}

void UI::release()
{
}
