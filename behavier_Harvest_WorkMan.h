#pragma once
#include "stdafx.h"
#include "behavier_Harvest.h"
class UNIT;

class BEHAVIER_HARVEST_WORKMAN :public BEHAVIER_HARVEST
{
	BEHAVIER_HARVEST_WORKMAN();
	~BEHAVIER_HARVEST_WORKMAN();

	virtual	void	update(UNIT* pUnit)			override;
	virtual void	end(UNIT* pUnit)		override;

};