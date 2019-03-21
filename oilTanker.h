#pragma once
#include "stdafx.h"
#include "object.h"
#include "unit.h"
#include "buildMgr.h"


class OILTANKER : public UNIT
{
private:
	float	_fTimer;
	float	_fBuildTime;

public:
	OILTANKER();
	~OILTANKER();


	virtual void init(int nPosX, int nPosY, int nWidth, int nHeight, int nIndexNum);
	virtual void update()			override;
	virtual void updateBehavier()	override;

	virtual void release()			override;
	virtual void render(HDC hdc)	override;
	virtual	void renderSelected(HDC hdc) override;
	virtual void build(float fPosX, float fPosY, E_BUILDS eBuilds) override;


private:
	void	allocateState();
	void	allocateBehavier();
	void	allocateAnimation();

};