#pragma once
#include "stdafx.h"
#include "build.h"

class KEEP: public BUILD
{

private:


public:
	KEEP();
	~KEEP();

	virtual void create(int nLeft, int ntop, int nWidth, int nHeight, int nHp, float fBuildingTimer, int nFrameCount, const string& strImgKey);
	virtual void update()			override;
	virtual void release()			override;
	virtual void render(HDC hdc)	override;

};
