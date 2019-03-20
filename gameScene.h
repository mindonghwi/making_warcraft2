#pragma once
#include "gameNode.h"
#include "map.h"
#include "camera.h"

#include "resourceMgr.h"

#include "player.h"
#include "UIMGR.h"
#include "bulletMgr.h"

class SCENEGAME : public gameNode
{
private:
	MAP*			_pMap;
	CAMERA*			_pCamera;
	RESOURCEMGR*	_pResourceMgr;
	ASTAR*			_pAstar;

	PLAYER*			_pPlayer;

	UIMGR*			_pUiMgr;
	
	BULLETMGR*		_pBulletMgr;
	
	PLAYER*			_pCom;

public:
	SCENEGAME();
	~SCENEGAME();

	virtual HRESULT init()	override;
	virtual void release()	override;
	virtual void update()	override;
	virtual void render()	override;
};