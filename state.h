#pragma once
//플레이어 커맨더 정리부터
#include "stdafx.h"
#include "resources.h"
#include "object.h"

class UNIT;
class BEHAVIER_ATTACK;

class STATE {
protected:
	UNIT*		_pUnit;

public:
	STATE();
	~STATE();

	virtual void update()	abstract;


};