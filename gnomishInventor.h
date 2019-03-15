#pragma once
#include "stdafx.h"
#include "build.h"

class GNOMISH_INVENTOR : public BUILD
{

private:


public:
	GNOMISH_INVENTOR();
	~GNOMISH_INVENTOR();

	virtual void create(int nLeft, int ntop, int nWidth, int nHeight, int nHp, float fBuildingTimer, int nFrameCount, const string& strImgKey);
	virtual void release()			override;
	virtual void render(HDC hdc)	override;

};
