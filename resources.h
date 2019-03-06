#pragma once
#include "object.h"
#include "stdafx.h"

class RESOURCES : public OBJECT
{
protected:

	int	_nResourceCount;
	CAMERA*		_pCamera;

public:
	RESOURCES();
	virtual ~RESOURCES();

	virtual void init(int nLeft, int nTop)	abstract;
	virtual void update()					abstract;
	virtual void release()					abstract;
	virtual void render(HDC hdc)			abstract;

	void	linkCamera(CAMERA* pCamera) { _pCamera = pCamera; }

public:
	inline void	setResourceCount(int nResourceCount) { _nResourceCount = nResourceCount; }
	inline	int	getResourceCount() { return _nResourceCount; }
};
