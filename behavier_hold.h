#pragma once
#include "stdafx.h"
#include "behavier.h"

class BEHAVIER_HOLD : public BEHAVIER
{
private:


public:
	BEHAVIER_HOLD();
	~BEHAVIER_HOLD();

	virtual	void	update(UNIT* pUnit)		override;
	virtual void	end(UNIT* pUnit)		override;
};