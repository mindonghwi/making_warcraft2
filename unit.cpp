#include "stdafx.h"
#include "unit.h"

UNIT::UNIT()
{
}

UNIT::~UNIT()
{
}

void UNIT::init(int nPosX, int nPosY, int nWidth, int nHeight)
{
	OBJECT::init(static_cast<float>(nPosX), static_cast<float>(nPosY), nWidth, nHeight);
	OBJECT::settingRect();

	setHp(0);
	setAttack(0);
	setDefence(0);
	setSpeed(0.0f);
	setSearchRange(0.0f);
	setAttackRange(0.0f);
	setAttackSpeedps(0.0f);
}

void UNIT::create(int nPosX, int nPosY, int nHp, float fSpeed, int nAttack, int nDefence, float fSearchRange, float fAttackRange, float fAttackSpeedps)
{
	OBJECT::setPosX(static_cast<float>(nPosX));
	OBJECT::setPosY(static_cast<float>(nPosY));
	setHp(nHp);
	setAttack(nAttack);
	setDefence(nDefence);
	setSpeed(fSpeed);
	setSearchRange(fSearchRange);
	setAttackRange(fAttackRange);
	setAttackSpeedps(fAttackSpeedps);
}

void UNIT::update()
{
}

void UNIT::release()
{
}

void UNIT::render(HDC hdc)
{
}
