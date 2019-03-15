#pragma once
#include "stdafx.h"
#include "build.h"

class STABLE : public BUILD
{

private:


public:
	STABLE();
	~STABLE();

	virtual void create(int nLeft, int ntop, int nWidth, int nHeight, int nHp, float fBuildingTimer, int nFrameCount, const string& strImgKey);
	virtual void release()			override;
	virtual void render(HDC hdc)	override;

};
