#pragma once
#include "stdafx.h"
#include "build.h"

class TOWN : public BUILD
{

private:


public:
	TOWN();
	~TOWN();

	virtual void create(float fPosX, float fPosY, int nWidth, int nHeight, int nHp, float fBuildingTimer, int nFrameCount, const string& strImgKey);
	virtual void update()			override;
	virtual void release()			override;
	virtual void render(HDC hdc)	override;
	//virtual	void creatingUpdate()	override;

};
