#include "stdafx.h"
#include "command.h"
#include "unit.h"

COMMAND::COMMAND()
{
}

COMMAND::~COMMAND()
{
}

void COMMAND::commandUnit()
{
	_fPosX = 0.0f;
	_fPosY = 0.0f;
	_pTarget = nullptr;
	_eBuild = E_BUILDS::E_MAX;
	_fAngle = 0.0f;
	_pResources = nullptr;
}

void COMMAND::commandUnit(float fPosX, float fPosY)
{
	_fPosX = fPosX;
	_fPosY = fPosY;
	_pTarget = nullptr;
	_eBuild = E_BUILDS::E_MAX;
	_fAngle = 0.0f;
	_pResources = nullptr;
}

void COMMAND::commandUnit(float fPosX, float fPosY,E_BUILDS eBuild)
{
	_fPosX = fPosX;
	_fPosY = fPosY;
	_pTarget = nullptr;
	_eBuild = eBuild;
	_fAngle = 0.0f;
	_pResources = nullptr;

}

void COMMAND::commandUnit(OBJECT * pTarget)
{
	_fPosX = pTarget->getPosX();
	_fPosY = pTarget->getPosY();
	_pTarget = pTarget;
	_eBuild = E_BUILDS::E_MAX;
	_fAngle = 0.0f;
	_pResources = nullptr;
}


void COMMAND::commandUnit(float fPosX, float fPosY, float fAngle)
{
	_fPosX = fPosX;
	_fPosY = fPosY;
	_pTarget = nullptr;
	_eBuild = E_BUILDS::E_MAX;
	_fAngle = fAngle;
	_pResources = nullptr;

}

void COMMAND::commandUnit(RESOURCES * pResources)
{
	_fPosX = pResources->getPosX();
	_fPosY = pResources->getPosY();
	_pTarget = nullptr;
	_eBuild = E_BUILDS::E_MAX;
	_fAngle = 0.0f;
	_pResources = pResources;

}

