#pragma once
#include "command.h"

class COMMAND_ATTACK : public COMMAND
{
private:

public:
	COMMAND_ATTACK();
	~COMMAND_ATTACK();

	virtual void	commandUnit(OBJECT* pTarget)			override;	//Шњ АјАн
	virtual void	init(E_COMMAND eCommand, UNIT* pUnit)	override;
	virtual void	start()		override;

};
