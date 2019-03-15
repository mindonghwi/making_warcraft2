#pragma once
#include "stdafx.h"
#include "build.h"

class OIL_REFINERY : public BUILD
{

private:


public:
	OIL_REFINERY();
	~OIL_REFINERY();

	virtual void create(int nLeft, int ntop, int nWidth, int nHeight, int nHp, float fBuildingTimer, int nFrameCount, const string& strImgKey);
	virtual void release()			override;
	virtual void render(HDC hdc)	override;

};
