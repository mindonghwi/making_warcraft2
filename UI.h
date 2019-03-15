#pragma once
#include "stdafx.h"

class UNIT;
class BUILD;

class UI
{
private:
	enum E_UITYPE
	{
		E_NONE = 0,
		E_UNIT,
		E_BUILD,
		E_MAX
	};

private:
	image*	_pImageCard;
	image*	_pObjectImage;
	image*	_pPrograssBar;

	E_UITYPE _eUiType;

	UNIT*	_pUnit;
	BUILD*	_pBuild;
public:
	UI();
	~UI();

	void create(UNIT* pUnit = nullptr, BUILD* pBuild = nullptr);
	void update();
	void render(HDC hdc);
	void release();

	
};