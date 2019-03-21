#pragma once
#include "stdafx.h"
#include "state.h"



class STATE_NONE : public STATE
{
private:

public:
	STATE_NONE();
	~STATE_NONE();

	virtual void start()	override;
	virtual void update()	override;

};