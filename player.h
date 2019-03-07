#pragma once
#include "stdafx.h"
#include "command.h"
#include "unit.h"
#include "camera.h"

class ASTAR;

class PLAYER
{
public:
	enum class E_RESOURCE
	{
		E_GOLD = 0,
		E_TREE,
		E_OIL,
		E_MAX
	};

private:
	//선택된 애들만 가리키 벡터
	vector<UNIT**>		_vSeletedUnit;

	//플레이어가 가지는 모든 유닛
	list<UNIT*>			_listUnit;


	int		_arResource[static_cast<const int>(PLAYER::E_RESOURCE::E_MAX)];
	int		_nPopulation;
	int		_nMaxPopulation;
	CAMERA*		_pCamera;

	int		_arUnitPopulation[static_cast<const int>(UNIT::E_UNIT::E_MAX)];
	int		_arUnitResource[static_cast<const int>(UNIT::E_UNIT::E_MAX)][static_cast<int>(PLAYER::E_RESOURCE::E_MAX)];	//자원은 3개

	POINT	_ptCameraPtMouse;


	ASTAR*	_pAstar;

public:
	PLAYER();
	~PLAYER();

	void init();
	void update();
	void release();
	void render(HDC hdc);


	bool createUnit(UNIT::E_UNIT eUnit);

	void allocateUnitPopulation();
	void allocateUnitResource();

	void selectedUnit();
	void commandSelectUnit();

public:
	//linker
	inline	void	setLinkCamera(CAMERA* pCamera) { _pCamera = pCamera; }
	inline	void	setLinkAstar(ASTAR* pAstar) { _pAstar = pAstar; }

	
	//setter
	inline	void	setGold(int nGold) { _arResource[static_cast<int>(PLAYER::E_RESOURCE::E_GOLD)] = nGold; }
	inline	void	setTree(int nTree) { _arResource[static_cast<int>(PLAYER::E_RESOURCE::E_TREE)] = nTree; }
	inline	void	setOil(int nOil) { _arResource[static_cast<int>(PLAYER::E_RESOURCE::E_OIL)] = nOil; }
	inline	void	setPopulation(int nPopulation) { _nPopulation = nPopulation; }
	inline	void	setMaxPopulation(int nMaxPopulation) { _nMaxPopulation = nMaxPopulation; }


	//getter
	inline	int		getGold() {	return _arResource[static_cast<int>(PLAYER::E_RESOURCE::E_GOLD)]; }
	inline	int		getTree() { return _arResource[static_cast<int>(PLAYER::E_RESOURCE::E_TREE)]; }
	inline	int		getOil() { return  _arResource[static_cast<int>(PLAYER::E_RESOURCE::E_OIL)]; }
	inline	int		getPopulation() { return _nPopulation; }
	inline	int		getMaxPopulation() { return _nMaxPopulation; }

	//adder
	inline	void	addGold(int nGold) { _arResource[static_cast<int>(PLAYER::E_RESOURCE::E_GOLD)] += nGold; }
	inline	void	addTree(int nTree) { _arResource[static_cast<int>(PLAYER::E_RESOURCE::E_TREE)] += nTree; }
	inline	void	addOil(int nOil) { _arResource[static_cast<int>(PLAYER::E_RESOURCE::E_OIL)] += nOil; }
	inline	void	addPopulation(int nPopulation) { _nPopulation += nPopulation; }
	inline	void	addMaxPopulation(int nMaxPopulation) { _nMaxPopulation += nMaxPopulation; }

};