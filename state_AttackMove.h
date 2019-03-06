#pragma once
#include "stdafx.h"
#include "state.h"

class STATE_ATTACKMOVE : public STATE
{
private:


public:
	STATE_ATTACKMOVE();
	~STATE_ATTACKMOVE();

	virtual void start()	override;
	virtual void update()	override;

};