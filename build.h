#pragma once
#include "stdafx.h"
#include "object.h"


class CAMERA;

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

public:
	BUILD();
	virtual ~BUILD();

	virtual void create(float fPosX, float fPosY, int nWidth, int nHeight, int nHp, float fBuildingTimer,int nFrameCount, const string& strImgKey);
	virtual void update()			override;
	virtual void release()			override;
	virtual void render(HDC hdc)	override;

	virtual	void creatingUpdate();

	inline	void	setLinkCamera(CAMERA* pCamera) { _pCamera = pCamera; }


};
