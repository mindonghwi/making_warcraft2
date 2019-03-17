#pragma once
#include "stdafx.h"
#include "build.h"

class FARM : public BUILD
{

private:


public:
	FARM();
	~FARM();

	virtual void create(int nLeft, int ntop, int nWidth, int nHeight, int nHp, float fBuildingTimer, int nFrameCount, const string& strImgKey);
	//virtual void update()			override;
	virtual void release()			override;
	virtual void render(HDC hdc)	override;
	virtual	void creatingUpdate()	override;

};
