#pragma once
//�÷��̾� Ŀ�Ǵ� ��������
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