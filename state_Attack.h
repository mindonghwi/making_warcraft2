#pragma once
#include "stdafx.h"
#include "state.h"



class STATE_ATTACK : public STATE
{
private:

public:
	STATE_ATTACK();
	~STATE_ATTACK();

	virtual void update()	override;

};