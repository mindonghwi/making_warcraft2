#pragma once
#include "stdafx.h"
#include "state.h"

class STATE_PATROL : public STATE
{
private:


public:
	STATE_PATROL();
	~STATE_PATROL();

	virtual void update()	override;

};