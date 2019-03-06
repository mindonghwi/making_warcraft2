#pragma once
#include "stdafx.h"
#include "state.h"

class STATE_HOLD : public STATE
{
private:


public:
	STATE_HOLD();
	~STATE_HOLD();

	virtual void update()	override;

};