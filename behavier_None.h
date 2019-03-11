#pragma once
#include "stdafx.h"
#include "behavier.h"

class BEHAVIER_NONE : public BEHAVIER
{
private:


public:
	BEHAVIER_NONE();
	~BEHAVIER_NONE();

	virtual	void	update(UNIT* pUnit)			override;
	virtual void	end(UNIT* pUnit)		override;
};