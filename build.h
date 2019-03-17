#pragma once
#include "stdafx.h"
#include "object.h"

class CAMERA;
class UNITMGR;
class BUILDMGR;
class PLAYER;
class MAP;
class BUILD : public OBJECT
{
public:
	enum class E_STATE
	{
		E_CREATING = 0,
		E_ISON,
		E_DESTROY,
		E_MAX
	};


protected:
	float	_fBuildingTimer;	//지어지는데 걸리는 시간
	float	_fTimer;
	float	_fHp;
	int		_nMaxHp;
	int		_nCreateDamage;
	float	_fHpTimer;
	float	_fOffsetHpTimer;
	int		_nBuildLevel;
	int		_nFrameX;
	int		_nMaxFrameX;
	float	_fOffsetFrame;
	BUILD::E_STATE _eState;
	CAMERA*		_pCamera;

	float	_fRayPointX;
	float	_fRayPointY;

	unsigned int		_nUnitMask;
	UNITMGR*		_pUnitMgr;
	BUILDMGR*		_pBuildMgr;
	PLAYER*			_pPlayer;
	MAP*			_pMap;

	bool			_bIsProduce;
	E_BUILDS	_eBuilds;

	int				_eUnitType;
public:
	BUILD();
	virtual ~BUILD();

	virtual void create(int nLeft, int ntop, int nWidth, int nHeight, int nHp, float fBuildingTimer,int nFrameCount, const string& strImgKey);
	virtual void update()			override;
	virtual void release()			override;
	virtual void render(HDC hdc)	override;

	virtual void selectRender(HDC hdc);

	virtual	void creatingUpdate();

	virtual void createUnit();
	virtual void commandProduce();
	
	virtual void upgradeBuild();
	
	virtual void destroyBuild();

	inline	void	setLinkCamera(CAMERA* pCamera) { _pCamera = pCamera; }
	inline	void	setLinkUnitMgr(UNITMGR* pUnitMgr) { _pUnitMgr = pUnitMgr; }
	inline	void	setLinkBuildMgr(BUILDMGR* pBuildBgr) { _pBuildMgr = pBuildBgr; }
	inline	void	setLinkPlayer(PLAYER* pPlayer) { _pPlayer = pPlayer; }
	inline	void	setLinkMap(MAP* pMap) { _pMap = pMap; }

	inline	E_BUILDS	getBuildsTpye() { return _eBuilds; }

	inline int		getMaxHp() { return _nMaxHp; }

	inline	E_STATE	getState() { return _eState; }
};
