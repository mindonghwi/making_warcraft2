#pragma once
#include "player.h"

class COM : public PLAYER
{
private:
	bool	_bIsTown;

public:
	COM();
	~COM();
	virtual void update();

private:
	void commandTownBuild();
};