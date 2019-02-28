#include "stdafx.h"
#include "rock.h"

ROCK::ROCK()
{
}

ROCK::~ROCK()
{
}

void ROCK::init(int nLeft, int nTop)
{
	OBJECT::setPosX(static_cast<float>(nLeft + 32 + 16));
	OBJECT::setPosY(static_cast<float>(nTop + 32 + 16));
	OBJECT::setWidth(96);
	OBJECT::setHeight(96);
	OBJECT::settingRect();
	OBJECT::setImage(IMAGEMANAGER->findImage("goldMine"));
}

void ROCK::update()
{
}

void ROCK::release()
{
}

void ROCK::render(HDC hdc)
{
}
