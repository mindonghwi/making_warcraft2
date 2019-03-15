#pragma once
#include "stdafx.h"
#include "build.h"

class SCOUT_TOWER : public BUILD
{

private:


public:
	SCOUT_TOWER();
	~SCOUT_TOWER();

	virtual void create(int nLeft, int ntop, int nWidth, int nHeight, int nHp, float fBuildingTimer, int nFrameCount, const string& strImgKey);
	virtual void release()			override;
	virtual void render(HDC hdc)	override;
	virtual void upgradeBuild() override;

};
