#pragma once
#include "stdafx.h"
#include "object.h"
#include "unit.h"
#include "buildMgr.h"


class WORKMAN : public UNIT
{
public:
	

private:
	float	_fHarvestTime;		//�ڿ� ä���ϴ� �ð�
	int		_nHarvestCount;		//���� ������ �ִ� �ڿ���
	float	_fBuildTime;
	float	_fTimer;


public:
	WORKMAN();
	~WORKMAN();


	virtual void init(int nPosX, int nPosY, int nWidth, int nHeight, int nIndexNum);
	virtual void update()			override;
	virtual void updateBehavier()	override;

	virtual void release()			override;
	virtual void render(HDC hdc)	override;
	virtual	void renderSelected(HDC hdc) override;
	virtual void command()		override;
	virtual void commandBuild() override;
	virtual void build(float fPosX, float fPosY, E_BUILDS eBuilds) override;

	virtual	void harvestResources() override;
	virtual void commandHarvest()   override;
	virtual void commandReturnHarvest();

private:
	void	allocateState();
	void	allocateBehavier();
	void	allocateAnimation();
	
};