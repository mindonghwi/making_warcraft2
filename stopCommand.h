#pragma once
#include "command.h"

class COMMAND_STOP : public COMMAND
{
private:

public:
	COMMAND_STOP();
	~COMMAND_STOP();

	virtual	void	commandUnit()	override;


};