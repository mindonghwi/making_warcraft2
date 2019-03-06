#pragma once
#include "stdafx.h"
#include "behavier.h"
class UNIT;

class BEHAVIER_ATTACK : public BEHAVIER
{

public:
	BEHAVIER_ATTACK();
	~BEHAVIER_ATTACK();


	virtual	void	update(UNIT* pUnit)			override;
};