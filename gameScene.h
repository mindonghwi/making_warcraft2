#pragma once
#include "gameNode.h"
#include "map.h"
#include "camera.h"

#include "resourceMgr.h"

//test
#include "workMan.h"

class SCENEGAME : public gameNode
{
private:
	MAP*			_pMap;
	CAMERA*			_pCamera;
	RESOURCEMGR*	_pResourceMgr;
	ASTAR*			_pAstar;

	WORKMAN*		_pWorkMan;

public:
	SCENEGAME();
	~SCENEGAME();

	virtual HRESULT init()	override;
	virtual void release()	override;
	virtual void update()	override;
	virtual void render()	override;
};