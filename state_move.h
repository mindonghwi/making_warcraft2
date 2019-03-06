#pragma once
#include "stdafx.h"
#include "state.h"

class STATE_MOVE : public STATE
{
private:


public:
	STATE_MOVE();
	~STATE_MOVE();

	virtual void update()	override;

};