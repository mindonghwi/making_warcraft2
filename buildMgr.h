#pragma once
#include "build.h"
#include "stdafx.h"


class CAMERA;
class MAP;
class UNITMGR;
class PLAYER;
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

	enum E_UNITMASK
	{
		E_WORKMAN		= 0x001,
		E_FOOTMAN		= 0x002,
		E_ARCHER		= 0x004,
		E_BALLISTA		= 0x008,
		E_KNIGHT		= 0x010,
		E_MAGICIAN		= 0x020,
		E_BOMBER		= 0x040,
		E_RECONNAISSANCE = 0x080,	//정찰병
		E_OILTANKER		= 0x100,
		E_GALLEYS		= 0x200,			//작은 공격배
		E_TRANSPORT		= 0x400,
		E_BATTLESHIP	= 0x800,
		E_SUBMARIN		= 0x1000,
		E_FLYER			= 0x2000,
	};

private:
	int			_arConsumptionResource[static_cast<const int>(E_BUILDS::E_MAX)][static_cast<const int>(E_RESOURCE::E_MAX)];//지어지는데 필요한 자원
	int			_arBuildsWidth[static_cast<const int>(E_BUILDS::E_MAX)];
	int			_arBuildsHeight[static_cast<const int>(E_BUILDS::E_MAX)];
	float		_arBuildTime[static_cast<const int>(E_BUILDS::E_MAX)];


	int			_nBuildLevel;

	CAMERA*		_pCamera;
	MAP*		_pMap;


	list<BUILD*>	_listBuild;

	UNITMGR*		_pUnitMgr;

	BUILD*			_pSelected;
	PLAYER*			_pPlayer;

public:
	BUILDMGR();
	~BUILDMGR();

	void	init();
	void	update();
	void	release();
	void	buildBuilding(BUILDMGR::E_BUILDS eBuild, float fPosX,float fPosY);
	bool	bIsGroundCheck(E_BUILDS eBuilds,float fPosX,float fPosY);
	void	render(HDC hdc);

private:
	void	allocateBuildResource();
	void	allocateBuildSize();
	void	allocateBuildTime();
public:
	//linker
	inline	void	setLinkCamera(CAMERA* pCamera) { _pCamera = pCamera; }
	inline	void	setLinkMap(MAP* pMap) { _pMap = pMap; }
	inline	void	setLinkUnitMgr(UNITMGR* pUnitMgr) { _pUnitMgr = pUnitMgr; }
	inline	void	setLinkPlayer(PLAYER* pPlayer) { _pPlayer = pPlayer; }

	//getter
	inline	int		getConsumptionResource(E_BUILDS eBuilds,E_RESOURCE eResource){return _arConsumptionResource[static_cast<int>(eBuilds)][static_cast<int>(eResource)]; }
	inline	float	getBuildTime(E_BUILDS eBuilds) { return _arBuildTime[static_cast<int>(eBuilds)]; }
	inline	int		getBuildCount() { return static_cast<int>(_listBuild.size()); }
	

	void	releaseSelected();
	void	selectedBuild(RECT rcDrag);

};
