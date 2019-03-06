#pragma once
#include "stdafx.h"
#include "command.h"
#include "unit.h"


class PLAYER
{
private:
	//���õ� �ֵ鸸 ����Ű ����
	vector<UNIT**>		_vSeletedUnit;

	//�÷��̾ ������ ��� ����
	list<UNIT*>			_listUnit;

	int		_nGold;
	int		_nTree;
	int		_nOil;
	int		_nPopulation;


public:
	PLAYER();
	~PLAYER();

	void init();

};