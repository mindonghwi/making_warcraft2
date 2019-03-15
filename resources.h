#pragma once
#include "object.h"
#include "stdafx.h"

class RESOURCES : public OBJECT
{
protected:

	int	_nResourceCount;
	CAMERA*		_pCamera;
	int	_nHarvestCount;
	int	_nMaxHarvestCount;
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
	
	//getter
	inline	int	getHarvestCount() { return _nHarvestCount; }
	inline	int	getMaxHarvestCount() { return _nMaxHarvestCount; }

	inline	void	setHarvestCount(int nAmount) { _nHarvestCount = nAmount; }
	inline	void	setMaxHarvestCount(int nAmount) { _nMaxHarvestCount = nAmount; }

	inline	void	addHarvestCount(int nAmount) { _nHarvestCount += nAmount; }
	inline	void	addMaxHarvestCount(int nAmount) { _nMaxHarvestCount += nAmount; }

	inline	void	SubTractHarvestCount(int nAmount) { _nHarvestCount -= nAmount; }
	inline	void	SubTractMaxHarvestCount(int nAmount) { _nMaxHarvestCount -= nAmount; }

	bool	Isharvested();
};
