#include "stdafx.h"
#include "com.h"

COM::COM()
{
}

COM::~COM()
{
}

void COM::update()
{
	_pUnitMgr->selectedUnit();
	dragSelect();

	//일군한테 마을 회관을 지으라고한다
	//마을회관이 다 지어지면 일군ㄴ한테 유닛을 뽑으라고 함
	//일군중 한명에게 농장을 지으라고 한다.
	//남은 일군한테 금채취를 시킨다
	//마을회관에서는 일군이 7~ 10마리까지 뽑느다.
	
	_pUnitMgr->update();
	_pBuildMgr->update();

}
