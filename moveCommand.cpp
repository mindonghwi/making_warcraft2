#include "stdafx.h"
#include "moveCommand.h"
#include "unit.h"

COMMAND_MOVE::COMMAND_MOVE()
{
}

COMMAND_MOVE::~COMMAND_MOVE()
{
}

void COMMAND_MOVE::commandUnit(float fPosX, float fPosY)
{
	COMMAND::commandUnit(fPosX, fPosY);
}

void COMMAND_MOVE::init(E_COMMAND eCommand, UNIT * pUnit)
{
	COMMAND::setCommand(eCommand);
	COMMAND::setUnit(pUnit);
}

void COMMAND_MOVE::start()
{
	_pUnit->commandMove(_fPosX, _fPosY);

}
