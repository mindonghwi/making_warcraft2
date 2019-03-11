#pragma once
#include "build.h"
#include "stdafx.h"

class CAMERA;
class MAP;


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
		E_SHIPYARD,		//������
		E_FOUNDRY,		//������
		E_OIL_REFINERY,
		E_OIL_PLATFORM,
		E_GNOMISH_INVENTOR,	//���߸��
		E_STABLE,
		E_CHURCH,
		E_MAGE_TOWER,
		E_GRYPHON_AVIARY,
		E_MAX
	};



private:
	int			_arConsumptionResource[static_cast<const int>(E_BUILDS::E_MAX)][static_cast<const int>(E_RESOURCE::E_MAX)];//�������µ� �ʿ��� �ڿ�
	int			_nBuildLevel;

	CAMERA*		_pCamera;
	MAP*		_pMap;
public:
	BUILDMGR();
	~BUILDMGR();

	void	init();
	void	update();
	void	release();
	void	buildBuilding(BUILDMGR::E_BUILDS eBuild);
private:
	void	allocateBuildResource();


	//linker
	inline	void	setLinkCamera(CAMERA* pCamera) { _pCamera = pCamera; }
	inline	void	setLinkMap(MAP* pMap) { _pMap = pMap; }

};
