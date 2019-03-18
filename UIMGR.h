#pragma once

#include "UICARD.h"
#include "UI.h"

class PLAYER;



class UIMGR 
{
private:
	PLAYER*		_pPlayer;
	UICARD*		_arUiCard[9];
	UI*			_pUi;

	int			_nCount;
public:
	UIMGR();
	~UIMGR();

	void	init();
	void	update();
	void	release();
	void	render(HDC hdc);

	//linker
	inline	void	setLinkPlayer(PLAYER* pPlayer) { _pPlayer = pPlayer; }

};