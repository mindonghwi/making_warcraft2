#pragma once

#include "stdafx.h"
class PLAYER;

class COMMAND {
	//플레이어가 커맨드를 내린다.
	//그에따른 명령을 받는 유닛들의 상태가 변한다.
	
public:
	virtual	void	commandUnit(PLAYER pPlayer)	abstract;


};