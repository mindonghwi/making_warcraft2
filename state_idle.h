#pragma once
#include "stdafx.h"
#include "state.h"

class STATE_IDLE : public STATE
{
private:


public:
	STATE_IDLE();
	~STATE_IDLE();

	virtual void start()	override;
	virtual void update()	override;

};