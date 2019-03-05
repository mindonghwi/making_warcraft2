#pragma once
#include "gameNode.h"
#include "stdafx.h"
#include "button.h"
#include "scrollButton.h"

class SCENEMAINMENU : public gameNode
{
private:
	SCROLLBUTTON*	_pScrollBtn;

	button*			_pBtnMapTool;
	button*			_pBtnSingleGame;
	button*			_pBtnExit;

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
};