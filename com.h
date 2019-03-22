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

	void searchFindGround(int nPathIndex,E_BUILDS eBuilds);
};