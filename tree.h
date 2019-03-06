#pragma once
#include "stdafx.h"
#include "object.h"
#include "tile.h"
#include "camera.h"
#include "resources.h"


class TREE : public RESOURCES
{
private:
	int	_nResourceCount;
	CAMERA*		_pCamera;

public:
	TREE();
	~TREE();

	void	init(int nLeft, int nTop);
	virtual void update()			override;
	virtual void release()			override;
	virtual void render(HDC hdc)	override;

	void	linkCamera(CAMERA* pCamera) { _pCamera = pCamera; }

public:
	inline void	setResourceCount(int nResourceCount) { _nResourceCount = nResourceCount; }
	inline	int	getResourceCount() { return _nResourceCount; }
};
