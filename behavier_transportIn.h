#pragma once
#include "stdafx.h"
#include "behavier.h"

class BEHAVIER_TRANSPORTIN : public BEHAVIER
{
private:
	float _fTimer;

public:
	BEHAVIER_TRANSPORTIN();
	~BEHAVIER_TRANSPORTIN();

	virtual	void	update(UNIT* pUnit)		override;
	virtual void	end(UNIT* pUnit)		override;
};