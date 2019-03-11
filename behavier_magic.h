#pragma once
#include "stdafx.h"
#include "behavier.h"
class UNIT;

class BEHAVIER_MAGIC :public BEHAVIER
{
public:
	virtual	void	update(UNIT* pUnit)		abstract;
	virtual void	end(UNIT* pUnit)		abstract;

};