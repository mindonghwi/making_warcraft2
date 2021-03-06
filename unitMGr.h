#pragma once
#include "stdafx.h"
#include "command.h"
#include "unit.h"
#include "camera.h"
#include "command.h"
class MAP;
class BUILDMGR;
class RESOURCEMGR;
class PLAYER;
class RESOURCES;
class BULLETMGR;
class UNITMGR
{
private:
	//선택된 애들만 가리키 벡터
	vector<UNIT**>		_vSeletedUnit;

	//플레이어가 가지는 모든 유닛
	list<UNIT*>			_listUnit;

	CAMERA*				_pCamera;

	int					_arUnitPopulation[static_cast<const int>(UNIT::E_UNIT::E_MAX)];
	int					_arUnitResource[static_cast<const int>(UNIT::E_UNIT::E_MAX)][static_cast<int>(E_RESOURCE::E_MAX)];	//자원은 3개

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

	BUILDMGR*		_pBuildMgr;


	map<COMMAND::E_COMMAND, queue<COMMAND*>>	_mCommandPool;

	RESOURCEMGR*	_pResourceMgr;
	PLAYER*			_pPlayer;
	BULLETMGR*		_pBulletMgr;

	PLAYER*		_pOpponent;

public:
	UNITMGR();
	~UNITMGR();


	void init();
	bool createUnit(UNIT::E_UNIT eUnit, float fPosX, float fPosY);
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

	void moveCommand(float fPosX,float fPosY);
	void buildCommand(float fPosX, float fPosY,E_BUILDS eBuilds);

	void addCommandPool(COMMAND::E_COMMAND eCommand, int nCount);
	void returnPool(COMMAND* pCommand);

	void commandAttack(OBJECT* pObject);
	void commandMoveAttack(float fPosX, float fPosY);
	void commandReAttack(UNIT* pUnit,OBJECT* pObject);
	void commandAatackNonMove(UNIT* pUnit,OBJECT* pObject);
	void commandAttackHold(UNIT* pUnit, OBJECT* pObject);

	void clearCommandSelectedUnit();


	void commandHarvest(RESOURCES* pResource);
	void commandHarvestSingle(RESOURCES* pResource, UNIT* pUnit);

	void commandMoveSingle(float fPosX, float fPosY, UNIT* pUnit);
	void removeSelectedUnit(UNIT* pUnit);


	bool getUnitCollisionBullet(float fPosX, float fPosY, int nAttack);

	void commandHold();

	void removeSelected(UNIT* pUnit);
	void clearMoveAttack();

	UNIT*	getSelectedUnitFirst();

public:
	//linker
	inline	void	setLinkCamera(CAMERA* pCamera) { _pCamera = pCamera; }
	inline	void	setLinkAstar(ASTAR* pAstar) { _pAstar = pAstar; }
	inline	void	setLinkMap(MAP* pMap) { _pMap = pMap; }
	inline	void	setLinkBuildMgr(BUILDMGR* pBuildMgr) { _pBuildMgr = pBuildMgr; }
	inline	void	setLinkResourceMgr(RESOURCEMGR* pResourceMgr) { _pResourceMgr = pResourceMgr; }
	inline	void	setLinkMyPlayer(PLAYER* pPlayer) { _pPlayer = pPlayer; }
	inline	void	setLinkBulletMgr(BULLETMGR* pBulletMgr) { _pBulletMgr = pBulletMgr; }

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

	UNIT*	getSelectedUnit(int nIndex);
	inline	int		getUnitSelectedCount() { return static_cast<int>(_vSeletedUnit.size()); }


	inline	PLAYER*		getOpponent() { return _pOpponent; }
	inline	void	setOpponent(PLAYER* pPlayer) { _pOpponent = pPlayer; }


public:
	//com AI
	UNIT* getUnit(UNIT::E_UNIT eUnit);
	void	commandBuildAi(float fPosX, float fPosY, E_BUILDS eBuilds,UNIT* pUnit);
	UNIT*	searchIdleUnit(UNIT::E_UNIT eUnit);
	UNIT*	searchRestUnit(UNIT::E_UNIT eUnit);

	void	commandAttackAi(float fPosX, float fPosY);
	void	commandMoveAttackAi(float fPosX, float fPosY,UNIT* pUnit);

	void	commandHarvestAi(E_RESOURCE eResource);
};