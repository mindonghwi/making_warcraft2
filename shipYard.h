#pragma once
#include "stdafx.h"
#include "build.h"

class SHIP_YARD : public BUILD
{

private:


public:
	SHIP_YARD();
	~SHIP_YARD();

	virtual void create(int nLeft, int ntop, int nWidth, int nHeight, int nHp, float fBuildingTimer, int nFrameCount, const string& strImgKey);
	virtual void release()			override;
	virtual void render(HDC hdc)	override;

};
