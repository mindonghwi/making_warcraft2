#pragma once
#include "stdafx.h"
#include "build.h"

class GRYPHON_AVIARY : public BUILD
{

private:


public:
	GRYPHON_AVIARY();
	~GRYPHON_AVIARY();

	virtual void create(int nLeft, int ntop, int nWidth, int nHeight, int nHp, float fBuildingTimer, int nFrameCount, const string& strImgKey);
	virtual void release()			override;
	virtual void render(HDC hdc)	override;

};
