#pragma once
//�÷��̾� Ŀ�Ǵ� ��������
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