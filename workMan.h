#pragma once
#include "stdafx.h"
#include "object.h"
#include "unit.h"

class WORKMAN : public UNIT
{
private:
	float	_fHarvestTime;		//�ڿ� ä���ϴ� �ð�
	int		_nHarvestCount;		//���� ������ �ִ� �ڿ���


public:
	WORKMAN();
	~WORKMAN();


	virtual void init(int nPosX, int nPosY, int nWidth, int nHeight);
	virtual void update()			abstract;
	virtual void release()			abstract;
	virtual void render(HDC hdc)	abstract;

	
};