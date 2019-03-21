#pragma once
#include "stdafx.h"
#include "behavier.h"

class BEHAVIER_TRANSPORTOUT : public BEHAVIER
{
private:
	float _fTimer;

public:
	BEHAVIER_TRANSPORTOUT();
	~BEHAVIER_TRANSPORTOUT();

	virtual	void	update(UNIT* pUnit)		override;
	virtual void	end(UNIT* pUnit)		override;
};