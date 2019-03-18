#pragma once
#include "stdafx.h"
#include "behavier.h"
class UNIT;

class BEHAVIER_ATTACK : public BEHAVIER
{
private:
	float _fTimer;
public:
	BEHAVIER_ATTACK();
	~BEHAVIER_ATTACK();


	virtual	void	update(UNIT* pUnit)		override;
	virtual void	end(UNIT* pUnit)		override;

};