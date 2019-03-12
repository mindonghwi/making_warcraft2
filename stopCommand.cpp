#include "stdafx.h"
#include "stopCommand.h"
#include "unit.h"
COMMAND_STOP::COMMAND_STOP()
{
}

COMMAND_STOP::~COMMAND_STOP()
{
}

void COMMAND_STOP::commandUnit()
{
	COMMAND::commandUnit();
	
}

void COMMAND_STOP::init(E_COMMAND eCommand, UNIT* pUnit)
{
	COMMAND::setCommand(eCommand);
	COMMAND::setUnit(pUnit);
}

void COMMAND_STOP::start()
{
	_pUnit->commandIdle();

}
