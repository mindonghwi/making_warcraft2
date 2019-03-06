#pragma once
//플레이어 커맨더 정리부터
#include "stdafx.h"
#include "unit.h"
#include "resources.h"
#include "object.h"

class STATE {
protected:
	UNIT*		_pUnit;

public:
	virtual void update()	abstract;

};