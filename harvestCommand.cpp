#include "stdafx.h"
#include "harvestCommand.h"
#include "unit.h"

COMMAND_HARVEST::COMMAND_HARVEST()
{
}

COMMAND_HARVEST::~COMMAND_HARVEST()
{
}

void COMMAND_HARVEST::commandUnit(RESOURCES * pResources)
{
	COMMAND::commandUnit(pResources);
}

void COMMAND_HARVEST::init(E_COMMAND eCommand, UNIT * pUnit)
{
	COMMAND::setCommand(eCommand);
	COMMAND::setUnit(pUnit);
}

void COMMAND_HARVEST::start()
{
	_pUnit->commandHarvest();
}
