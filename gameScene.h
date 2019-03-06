#pragma once
#include "gameNode.h"
#include "map.h"
#include "camera.h"
#include "goldMine.h"
#include "tree.h"
#include "oliPatch.h"


class SCENEGAME : public gameNode
{
private:
	MAP*		_pMap;
	CAMERA*		_pCamera;


	list<GOLDMINE*> _listGoldMine;
	list<TREE*>		_listTree;
	list<OILPATCH*>	_listOilPatch;

public:
	SCENEGAME();
	~SCENEGAME();

	virtual HRESULT init()	override;
	virtual void release()	override;
	virtual void update()	override;
	virtual void render()	override;
};