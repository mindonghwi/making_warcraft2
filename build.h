#pragma once
#include "stdafx.h"
#include "object.h"

class BUILD : public OBJECT
{
private:
	float	_fBuildingTimer;	//지어지는데 걸리는 시간
	
	int		_nHp;

public:
	BUILD();
	~BUILD();

	void init(float fPosX, float fPosY, int nWidth, int nHeight, int nHp, float fBuildingTimer);

};
