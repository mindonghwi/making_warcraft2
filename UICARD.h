#pragma once
#include "stdafx.h"

class UNIT;
class BUILD;

class UICARD
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
	image * _pImageCard;
	image*	_pObjectImage;
	image*	_pPrograssBar;

	E_UITYPE _eUiType;

	UNIT*	_pUnit;
	BUILD*	_pBuild;

	int		_nHp;
	int		_nMaxHp;
	int		_nAttack;
	int		_nDefence;
	
public:
	UICARD();
	~UICARD();

	void create(UNIT* pUnit = nullptr, BUILD* pBuild = nullptr);
	void update();
	void render(HDC hdc);
	void release();


};