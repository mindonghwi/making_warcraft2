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
	float		_fTimer;
public:
	STATE();
	~STATE();

	virtual void start()	abstract;
	virtual void update()	abstract;

	inline void	setUnit(UNIT* pUnit) { _pUnit = pUnit; }
};