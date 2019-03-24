#pragma once
#include "player.h"

class COM : public PLAYER
{
public:
	
private:
	bool	_bIsTown;
	float	_fTimer;

	vector<vector<int>>		_vvMapNode;
	int		_nFarmCount;
	int		_nWorkManCount;

	int		_arBuildsCount[static_cast<const int>(E_BUILDS::E_MAX)];
	int		_arUnitCount[static_cast<const int>(UNIT::E_UNIT::E_MAX)];
	bool	_bIsPhaseTwo;
	bool	_bIsPhaseThree;

	int		_nPhaseCount;
	int		_nCount;
public:
	COM();
	~COM();
	virtual void update();
	virtual void render(HDC hdc);
private:
	void commandTownBuild();
	void commandFarmBuild(int nIndexX,int nIndexY);
	void commandBarrackBuild(int nIndexX, int nIndexY);


	void commandCreateWorkMan();
	void commandCreateUnit(BUILDMGR::E_UNITMASK eUnitMask);
	void searchFindGround(int nPathIndex,E_BUILDS eBuilds);

	void phaseOne();
	void pahseTwo();
	void phaseThree();
};