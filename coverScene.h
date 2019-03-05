#pragma once
#include "gameNode.h"
#include "stdafx.h"

class SCENECOVER : public gameNode
{
private:


public:
	SCENECOVER();
	~SCENECOVER();

	virtual HRESULT init()	override;
	virtual void release()	override;
	virtual void update()	override;
	virtual void render()	override;

};