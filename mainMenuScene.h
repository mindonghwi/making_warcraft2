#pragma once
#include "gameNode.h"
#include "stdafx.h"
#include "button.h"
#include "scrollButton.h"

class SCENEMAINMENU : public gameNode
{
private:
	enum class LAYER
	{
		E_MAINMENU = 0,
		E_GAMESEETING,
		E_MAX
	};

	enum class E_RACE
	{
		E_ORC = 0,
		E_HUMAN,
		E_MAX
	};

	enum class E_RESOURCEDEGREE
	{
		E_HUGE = 0,
		E_NORMAL,
		E_THIN,
		E_MAX
	};

private:
	button*			_pBtnMapTool;
	button*			_pBtnSingleGame;
	button*			_pBtnExit;


	SCROLLBUTTON*	_pResourceDegreeBtn;
	SCROLLBUTTON*	_pRaceBtn;
	button*			_pGameStart;
	button*			_pReturnMainMenu;
	LAYER			_eLayer;



public:
	SCENEMAINMENU();
	~SCENEMAINMENU();

	virtual HRESULT init()	override;
	virtual void release()	override;
	virtual void update()	override;
	virtual void render()	override;


	void	updateMainMenuLayer();
	void	updateSingleGameSettingLayer();
	void	renderMainMenuLayer();
	void	renderSingleGameSettingLayer();

	void	changeMapToolScene();
	void	exit();
	void	changeGameSettingLayer();

	void	nullCallbackFunction();

	void	changeGameScene();
	void	changeMainmenuLayer();
};