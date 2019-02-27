#include "stdafx.h"
#include "oliPatch.h"

OILPATCH::OILPATCH()
{
}

OILPATCH::~OILPATCH()
{
}

void OILPATCH::init(int nLeft, int nTop)
{
	OBJECT::setPosX(static_cast<float>(nLeft + 32 + 16));
	OBJECT::setPosY(static_cast<float>(nTop + 32 + 16));
	OBJECT::setWidth(96);
	OBJECT::setHeight(96);
	OBJECT::setImage(IMAGEMANAGER->findImage("oil"));
}

void OILPATCH::update()
{
	_pCamera->pushRenderObject(this);

}

void OILPATCH::release()
{
}

void OILPATCH::render(HDC hdc)
{
	OBJECT::getImage()->renderCenter(hdc, static_cast<int>(OBJECT::getPosX()), static_cast<int>(OBJECT::getPosY()));
}
