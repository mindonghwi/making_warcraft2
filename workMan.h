#pragma once
#include "stdafx.h"
#include "object.h"
#include "unit.h"

class WORKMAN : public UNIT
{
public:


private:
	float	_fHarvestTime;		//자원 채집하는 시간
	int		_nHarvestCount;		//현제 가지고 있는 자원량


public:
	WORKMAN();
	~WORKMAN();


	virtual void init(int nPosX, int nPosY, int nWidth, int nHeight, int nIndexNum);
	virtual void update()			override;
	virtual void updateBehavier()	override;

	virtual void release()			override;
	virtual void render(HDC hdc)	override;
	virtual	void renderSelected(HDC hdc) override;
	virtual void commandMove(int* nCount)	override;



private:
	void	allocateState();
	void	allocateBehavier();
	void	allocateAnimation();
	
};