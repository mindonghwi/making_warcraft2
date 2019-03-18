#pragma once
#include "stdafx.h"
#include "button.h"

class PLAYER;

class UI
{
private:

private:
	image*	_pGoldIcon;
	image*	_pTreeIcon;
	image*	_pOilIcon;
	image*	_pPopulationIcon;


	PLAYER*	_pPlayer;

	
public:
	UI();
	~UI();

	void init(PLAYER* pPlayer);
	void update();
	void render(HDC hdc);
	void release();

	
};