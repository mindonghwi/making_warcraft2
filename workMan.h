#pragma once
#include "stdafx.h"
#include "object.h"
#include "unit.h"

class WORKMAN : public UNIT
{
public:


private:
	float	_fHarvestTime;		//�ڿ� ä���ϴ� �ð�
	int		_nHarvestCount;		//���� ������ �ִ� �ڿ���


public:
	WORKMAN();
	~WORKMAN();


	virtual void init(int nPosX, int nPosY, int nWidth, int nHeight);
	virtual void update()			override;
	virtual void release()			override;
	virtual void render(HDC hdc)	override;

private:
	void	allocateState();
	void	allocateBehavier();
	void	allocateAnimation();
	
};