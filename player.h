#pragma once
#include "stdafx.h"
#include "command.h"
#include "unit.h"
#include "camera.h"
#include "unitMGr.h"
#include "buildMgr.h"
#include "command.h"


class ASTAR;
class MAP;
class RESOURCEMGR;
class BULLETMGR;
class PLAYER
{
public:
	enum E_BUILDTYPE
	{
		E_NONE,
		E_B,
		E_V,
		E_MAX
	};

protected:
	int		_arResource[static_cast<const int>(E_RESOURCE::E_MAX)];
	int		_nPopulation;
	int		_nMaxPopulation;
	CAMERA*		_pCamera;


	POINT	_ptCameraPtMouse;


	ASTAR*		_pAstar;
	UNITMGR*	_pUnitMgr;
	BUILDMGR*	_pBuildMgr;
	MAP*		_pMap;
	RESOURCEMGR*	_pResourceMgr;

	//drag
	RECT	_rcDragArea;		//drag REct
	int		_nDragLeft;			//drag left
	int		_nDragTop;			//drag top
	bool	_bIsDrag;			//drag Status

	E_BUILDTYPE	_eBuildType;
	E_BUILDS	_eBuilds;


	PLAYER*		_pOpponent;

	BULLETMGR*	_pBulletMgr;
public:
	PLAYER();
	~PLAYER();

	virtual void init(float fPosX,float fPosY);
	virtual void update();
	virtual void release();
	virtual void render(HDC hdc);


	bool createUnit(UNIT::E_UNIT eUnit);

protected:
	virtual void selectedUnit();
	virtual void commandSelectUnit();
	 
	virtual void commandBuild();
	virtual void commandAttack();
	virtual void commandHarvest();
	virtual void initDrag();
	virtual void dragSelect();
	virtual void readjustDragRect();

public:
	//linker
	inline	void	setLinkCamera(CAMERA* pCamera) { _pCamera = pCamera; }
	inline	void	setLinkAstar(ASTAR* pAstar) { _pAstar = pAstar; }
	inline	void	setLinkMap(MAP* pMap) { _pMap = (pMap); }
	inline	void	setLinkResourceMgr(RESOURCEMGR* pResourceMgr) { _pResourceMgr = pResourceMgr; }
	inline	void	setLinkBulletMgr(BULLETMGR* pBulletMgr) { _pBulletMgr = pBulletMgr; }


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
	inline	BUILDMGR*	getBuildMgr() { return _pBuildMgr; }

	//adder
	inline	void	addGold(int nGold) { _arResource[static_cast<int>(E_RESOURCE::E_GOLD)] += nGold; }
	inline	void	addTree(int nTree) { _arResource[static_cast<int>(E_RESOURCE::E_TREE)] += nTree; }
	inline	void	addOil(int nOil) { _arResource[static_cast<int>(E_RESOURCE::E_OIL)] += nOil; }
	inline	void	addPopulation(int nPopulation) { _nPopulation += nPopulation; }
	inline	void	addMaxPopulation(int nMaxPopulation) { _nMaxPopulation += nMaxPopulation; }

};