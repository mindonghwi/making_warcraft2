#pragma once
#include "stdafx.h"
#include "behavier_Move.h"

class UNIT;

class BEHAVIER_MOVE_FLY : public BEHAVIER_MOVE
{

public:
	BEHAVIER_MOVE_FLY();
	~BEHAVIER_MOVE_FLY();

	virtual	void	update(UNIT* pUnit)			override;
	virtual void	end(UNIT* pUnit)		override;

};