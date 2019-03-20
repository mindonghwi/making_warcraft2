#include "stdafx.h"
#include "holdCommand.h"
#include "unit.h"

COMMAND_HOLD::COMMAND_HOLD()
{
}

COMMAND_HOLD::~COMMAND_HOLD()
{
}

void COMMAND_HOLD::commandUnit()
{
	COMMAND::commandUnit();

}

void COMMAND_HOLD::init(E_COMMAND eCommand, UNIT * pUnit)
{
	COMMAND::setCommand(eCommand);
	COMMAND::setUnit(pUnit);
}

void COMMAND_HOLD::start()
{
	_pUnit->commandHold();

}
