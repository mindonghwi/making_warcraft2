#include "stdafx.h"
#include "buildCommand.h"
#include "unit.h"

COMMAND_BUILD::COMMAND_BUILD()
{
}

COMMAND_BUILD::~COMMAND_BUILD()
{
}

void COMMAND_BUILD::commandUnit(float fPosX, float fPosY, BUILDMGR::E_BUILDS eBuild)
{
	COMMAND::commandUnit(fPosX, fPosY,eBuild);
}

void COMMAND_BUILD::init(E_COMMAND eCommand, UNIT * pUnit)
{
	COMMAND::setCommand(eCommand);
	COMMAND::setUnit(pUnit);
}

void COMMAND_BUILD::start()
{
	_pUnit->build(_fPosX, _fPosY, _eBuild);
}
