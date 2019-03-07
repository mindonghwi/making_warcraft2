#pragma once
#include "stdafx.h"
#include "behavier_Move.h"

class UNIT;

class BEHAVIER_MOVE_WALK : public BEHAVIER_MOVE
{
private:
	float _fTimer;
public:
	BEHAVIER_MOVE_WALK();
	~BEHAVIER_MOVE_WALK();

	virtual	void	update(UNIT* pUnit)			override;
};