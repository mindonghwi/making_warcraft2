#pragma once
#include "stdafx.h"
#include "object.h"

class CAMERA;
class UNITMGR;
class BUILDMGR;
class PLAYER;
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
	int		_nHp;
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
	BUILDMGR*		_pBuildBgr;
	PLAYER*			_pPlayer;

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

	inline	void	setLinkCamera(CAMERA* pCamera) { _pCamera = pCamera; }
	inline	void	setLinkUnitMgr(UNITMGR* pUnitMgr) { _pUnitMgr = pUnitMgr; }
	inline	void	setLinkUnitMgr(BUILDMGR* pBuildBgr) { _pBuildBgr = pBuildBgr; }
	inline	void	setLinkPlayer(PLAYER* pPlayer) { _pPlayer = pPlayer; }


};
