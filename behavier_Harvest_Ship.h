#pragma once
#include "stdafx.h"
#include "behavier_Harvest.h"
class UNIT;

class BEHAVIER_HARVEST_SHIP :public BEHAVIER_HARVEST
{
	BEHAVIER_HARVEST_SHIP();
	~BEHAVIER_HARVEST_SHIP();

	virtual	void	update(UNIT* pUnit)			override;
	virtual void	end(UNIT* pUnit)		override;

};