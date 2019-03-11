#pragma once
#include "stdafx.h"
#include "command.h"
#include "unit.h"
#include "camera.h"

class MAP;

class UNITMGR
{
private:
	//���õ� �ֵ鸸 ����Ű ����
	vector<UNIT**>		_vSeletedUnit;

	//�÷��̾ ������ ��� ����
	list<UNIT*>			_listUnit;

	CAMERA*				_pCamera;

	int					_arUnitPopulation[static_cast<const int>(UNIT::E_UNIT::E_MAX)];
	int					_arUnitResource[static_cast<const int>(UNIT::E_UNIT::E_MAX)][static_cast<int>(E_RESOURCE::E_MAX)];	//�ڿ��� 3��

	int					_arUnitHp[static_cast<const int>(UNIT::E_UNIT::E_MAX)];
	int					_arUnitDefence[static_cast<const int>(UNIT::E_UNIT::E_MAX)];
	int					_arUnitMinimalAttack[static_cast<const int>(UNIT::E_UNIT::E_MAX)];
	int					_arUnitAttack[static_cast<const int>(UNIT::E_UNIT::E_MAX)];
	int					_arUnitProductionTime[static_cast<const int>(UNIT::E_UNIT::E_MAX)];
	float				_arUnitSpeed[static_cast<const int>(UNIT::E_UNIT::E_MAX)];
	float				_arSearchRange[static_cast<const int>(UNIT::E_UNIT::E_MAX)];
	float				_arAttackRange[static_cast<const int>(UNIT::E_UNIT::E_MAX)];
	float				_arAttackSpeed[static_cast<const int>(UNIT::E_UNIT::E_MAX)];



	POINT				_ptCameraPtMouse;

	ASTAR*				_pAstar;

	int				_arIntervalMove[25][2];
	MAP*			_pMap;

	int				_nCount;
public:
	UNITMGR();
	~UNITMGR();


	void init();
	bool createUnit(UNIT::E_UNIT eUnit,float fPosX,float fPosY);
	void update();
	void release();
	void render(HDC hdc);

	void selectedUnit();
	void commandSelectUnit();

	void allocateUnitPopulation();
	void allocateUnitResource();
	void allocateUnitStatus();

	void dragSelect(RECT rcDragRect);

	void clearSelectedUnit();
	void	allocateIntervalMove();

public:
	//linker
	inline	void	setLinkCamera(CAMERA* pCamera) { _pCamera = pCamera; }
	inline	void	setLinkAstar(ASTAR* pAstar) { _pAstar = pAstar; }
	inline	void	setLinkMap(MAP* pMap) { _pMap = pMap; }

	//getter
	inline	int		getHp(UNIT::E_UNIT eUnit) { return _arUnitHp[static_cast<int>(eUnit)]; }
	inline	int		getAttack(UNIT::E_UNIT eUnit) { return _arUnitAttack[static_cast<int>(eUnit)]; }
	inline	int		getDefence(UNIT::E_UNIT eUnit) { return _arUnitDefence[static_cast<int>(eUnit)]; }
	inline	float	getSpeed(UNIT::E_UNIT eUnit) { return _arUnitSpeed[static_cast<int>(eUnit)]; }
	inline	float	getSearchRange(UNIT::E_UNIT eUnit) { return _arSearchRange[static_cast<int>(eUnit)]; }
	inline	float	getAttackRange(UNIT::E_UNIT eUnit) { return _arAttackRange[static_cast<int>(eUnit)]; }
	inline	float	getAttackSpeedps(UNIT::E_UNIT eUnit) { return _arAttackSpeed[static_cast<int>(eUnit)]; }
	inline	int		getMiniMalAttack(UNIT::E_UNIT eUnit) { return _arUnitMinimalAttack[static_cast<int>(eUnit)]; }

	inline	int		getUnitPopulation(UNIT::E_UNIT eUnit) { return _arUnitPopulation[static_cast<int>(eUnit)]; }
	inline	int		getUnitResource(UNIT::E_UNIT eUnit, E_RESOURCE eResouce) { return _arUnitResource[static_cast<int>(eUnit)][static_cast<int>(eResouce)]; }

	inline	int		getIntervalX(int nIndex) { return _arIntervalMove[nIndex][0]; }
	inline	int		getIntervalY(int nIndex) { return _arIntervalMove[nIndex][1]; }


	UNIT*	getUnit(int nIndex);
	inline	int		getUnitCount() { return static_cast<int>(_listUnit.size()); }
};