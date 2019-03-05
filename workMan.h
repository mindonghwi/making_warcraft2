#pragma once
#include "stdafx.h"
#include "object.h"
#include "unit.h"

class WORKMAN : public UNIT
{
private:
	float	_fHarvestTime;		//자원 채집하는 시간
	int		_nHarvestCount;		//현제 가지고 있는 자원량


public:
	WORKMAN();
	~WORKMAN();


	virtual void init(int nPosX, int nPosY, int nWidth, int nHeight);
	virtual void update()			abstract;
	virtual void release()			abstract;
	virtual void render(HDC hdc)	abstract;

	
};