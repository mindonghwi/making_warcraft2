#pragma once
#include "stdafx.h"

class UNIT;

class BEHAVIER abstract
{
public:
	virtual	void	update(UNIT* pUnit)		abstract;
	virtual void	end(UNIT* pUnit)		abstract;
};