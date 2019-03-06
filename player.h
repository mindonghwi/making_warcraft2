#pragma once
#include "stdafx.h"
#include "command.h"
#include "unit.h"


class PLAYER
{
private:
	//선택된 애들만 가리키 벡터
	vector<UNIT**>		_vSeletedUnit;

	//플레이어가 가지는 모든 유닛
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