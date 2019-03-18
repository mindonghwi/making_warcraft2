#include "stdafx.h"
#include "UI.h"
#include "player.h"

UI::UI()
{
}

UI::~UI()
{
}



void UI::init(PLAYER * pPlayer)
{
	_pGoldIcon = IMAGEMANAGER->findImage("UiGold");
	_pTreeIcon = IMAGEMANAGER->findImage("UiTree");
	_pOilIcon = IMAGEMANAGER->findImage("UiOil");
	_pPopulationIcon = IMAGEMANAGER->findImage("UiPopulation");

	_pPlayer = pPlayer;
}

void UI::update()
{

}

void UI::render(HDC hdc)
{
	char str[128];

	_pGoldIcon->render(hdc, WINSIZEX / 2, 3);
	sprintf_s(str, "%d", _pPlayer->getGold());
	TextOut(hdc, WINSIZEX / 2 + 40, 3, str, strlen(str));
	_pTreeIcon->render(hdc, WINSIZEX / 2 + 100, 3);
	sprintf_s(str, "%d", _pPlayer->getTree());
	TextOut(hdc, WINSIZEX / 2 + 140, 3, str, strlen(str));
	_pOilIcon->render(hdc, WINSIZEX / 2 + 200, 3);
	sprintf_s(str, "%d", _pPlayer->getOil());
	TextOut(hdc, WINSIZEX / 2 + 240, 3, str, strlen(str));
	_pPopulationIcon->render(hdc, WINSIZEX / 2 + 300, 3);
	sprintf_s(str, "%d / %d", _pPlayer->getPopulation(), _pPlayer->getMaxPopulation());
	TextOut(hdc, WINSIZEX / 2 + 340, 3, str, strlen(str));

}

void UI::release()
{
	_pGoldIcon = nullptr;
	_pTreeIcon = nullptr;
	_pOilIcon = nullptr;
	_pPopulationIcon = nullptr;
	_pPlayer = nullptr;
}
