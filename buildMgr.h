#pragma once
#include "build.h"
#include "stdafx.h"
#include "town.h"


class CAMERA;
class MAP;
class UNITMGR;

class BUILDMGR
{
public:
	enum class E_BUILDS
	{
		E_TOWN = 0,
		E_KEEP,
		E_CASTLE,
		E_FARM,
		E_BARRACKS,
		E_LUMBER_MILL,
		E_BLACK_SMITH,
		E_SCOUT_TOWER,
		E_GUARD_TOWER,
		E_CANNON_TOWER,
		E_SHIPYARD,		//조선소
		E_FOUNDRY,		//주조소
		E_OIL_REFINERY,
		E_OIL_PLATFORM,
		E_GNOMISH_INVENTOR,	//노움발명소
		E_STABLE,
		E_CHURCH,
		E_MAGE_TOWER,
		E_GRYPHON_AVIARY,
		E_MAX
	};



private:
	int			_arConsumptionResource[static_cast<const int>(E_BUILDS::E_MAX)][static_cast<const int>(E_RESOURCE::E_MAX)];//지어지는데 필요한 자원
	int			_arBuildsWidth[static_cast<const int>(E_BUILDS::E_MAX)];
	int			_arBuildsHeight[static_cast<const int>(E_BUILDS::E_MAX)];

	int			_nBuildLevel;

	CAMERA*		_pCamera;
	MAP*		_pMap;


	list<BUILD*>	_listBuild;

	UNITMGR*		_pUnitMgr;
public:
	BUILDMGR();
	~BUILDMGR();

	void	init();
	void	update();
	void	release();
	void	buildBuilding(BUILDMGR::E_BUILDS eBuild, float fPosX,float fPosY);

	bool	bIsGroundCheck(float fPosX,float fPosY);
	
private:
	void	allocateBuildResource();
	void	allocateBuildSize();
public:
	//linker
	inline	void	setLinkCamera(CAMERA* pCamera) { _pCamera = pCamera; }
	inline	void	setLinkMap(MAP* pMap) { _pMap = pMap; }
	inline	void	setLinkUnitMgr(UNITMGR* pUnitMgr) { _pUnitMgr = pUnitMgr; }
	inline	int		getConsumptionResource(E_BUILDS eBuilds,E_RESOURCE eResource){return _arConsumptionResource[static_cast<int>(eBuilds)][static_cast<int>(eResource)]; }
};
