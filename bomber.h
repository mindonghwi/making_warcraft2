#pragma once
#include "stdafx.h"
#include "object.h"
#include "unit.h"
#include "buildMgr.h"


class BOMBER : public UNIT
{
private:
	float	_fTimer;


public:
	BOMBER();
	~BOMBER();


	virtual void init(int nPosX, int nPosY, int nWidth, int nHeight, int nIndexNum);
	virtual void update()			override;
	virtual void updateBehavier()	override;

	virtual void release()			override;
	virtual void render(HDC hdc)	override;
	virtual	void renderSelected(HDC hdc) override;


private:
	void	allocateState();
	void	allocateBehavier();
	void	allocateAnimation();

};