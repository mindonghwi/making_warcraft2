#pragma once
#include "stdafx.h"
#include "command.h"
#include "unit.h"
#include "camera.h"
#include "unitMGr.h"
#include "buildMgr.h"

class ASTAR;
class MAP;
class PLAYER
{
public:


private:
	//선택된 애들만 가리키 벡터
	vector<UNIT**>		_vSeletedUnit;

	//플레이어가 가지는 모든 유닛
	list<UNIT*>			_listUnit;


	int		_arResource[static_cast<const int>(E_RESOURCE::E_MAX)];
	int		_nPopulation;
	int		_nMaxPopulation;
	CAMERA*		_pCamera;


	POINT	_ptCameraPtMouse;


	ASTAR*		_pAstar;
	UNITMGR*	_pUnitMgr;
	BUILDMGR*	_pBuildMgr;
	MAP*		_pMap;


	//drag
	RECT	_rcDragArea;		//drag REct
	int		_nDragLeft;			//drag left
	int		_nDragTop;			//drag top
	bool	_bIsDrag;			//drag Status
public:
	PLAYER();
	~PLAYER();

	void init();
	void update();
	void release();
	void render(HDC hdc);


	bool createUnit(UNIT::E_UNIT eUnit);


	

private:
	void selectedUnit();
	void commandSelectUnit();

	void commandBuild();

	void initDrag();
	void dragSelect();
	void readjustDragRect();
public:
	//linker
	inline	void	setLinkCamera(CAMERA* pCamera) { _pCamera = pCamera; }
	inline	void	setLinkAstar(ASTAR* pAstar) { _pAstar = pAstar; }
	inline	void	setLinkMap(MAP* pMap) { _pMap = (pMap); }
	
	//setter
	inline	void	setGold(int nGold) { _arResource[static_cast<int>(E_RESOURCE::E_GOLD)] = nGold; }
	inline	void	setTree(int nTree) { _arResource[static_cast<int>(E_RESOURCE::E_TREE)] = nTree; }
	inline	void	setOil(int nOil) { _arResource[static_cast<int>(E_RESOURCE::E_OIL)] = nOil; }
	inline	void	setPopulation(int nPopulation) { _nPopulation = nPopulation; }
	inline	void	setMaxPopulation(int nMaxPopulation) { _nMaxPopulation = nMaxPopulation; }


	//getter
	inline	int			getGold() {	return _arResource[static_cast<int>(E_RESOURCE::E_GOLD)]; }
	inline	int			getTree() { return _arResource[static_cast<int>(E_RESOURCE::E_TREE)]; }
	inline	int			getOil() { return  _arResource[static_cast<int>(E_RESOURCE::E_OIL)]; }
	inline	int			getPopulation() { return _nPopulation; }
	inline	int			getMaxPopulation() { return _nMaxPopulation; }
	inline	UNITMGR*	getUnitMgr() { return _pUnitMgr; }
	//adder
	inline	void	addGold(int nGold) { _arResource[static_cast<int>(E_RESOURCE::E_GOLD)] += nGold; }
	inline	void	addTree(int nTree) { _arResource[static_cast<int>(E_RESOURCE::E_TREE)] += nTree; }
	inline	void	addOil(int nOil) { _arResource[static_cast<int>(E_RESOURCE::E_OIL)] += nOil; }
	inline	void	addPopulation(int nPopulation) { _nPopulation += nPopulation; }
	inline	void	addMaxPopulation(int nMaxPopulation) { _nMaxPopulation += nMaxPopulation; }

};