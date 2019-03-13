#include "stdafx.h"
#include "attackCommand.h"
#include "unit.h"

COMMAND_ATTACK::COMMAND_ATTACK()
{
}

COMMAND_ATTACK::~COMMAND_ATTACK()
{
}

void COMMAND_ATTACK::commandUnit(OBJECT * pTarget)
{
	COMMAND::commandUnit(pTarget);
}

void COMMAND_ATTACK::init(E_COMMAND eCommand, UNIT * pUnit)
{
	COMMAND::setCommand(eCommand);
	COMMAND::setUnit(pUnit);
}

void COMMAND_ATTACK::start()
{
	_pUnit->attack(_pTarget);
}
