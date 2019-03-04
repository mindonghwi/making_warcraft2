#pragma once
#include "stdafx.h"
#include "object.h"

class UNIT : public OBJECT {
private:
	int		_nHp;
	int		_nAttack;
	int		_nDefence;

	float	_fSpeed;
	float	_fSearchRange;
	float	_fAttackRange;		//
	float	_fAttackSpeedps;	//초당 몇번 공격하는지


public:
	UNIT();
	~UNIT();

	//그냥 초기화
	virtual void init(int nPosX, int nPosY, int nWidth, int nHeight);

	//만들때 사용
	virtual void create(int nPosX,int nPosY,int nHp, float nSpeed, int nAttack, int nDefence, float fSearchRange, float fAttackRange, float fAttackSpeedps);
	
	virtual void update()			abstract;
	virtual void release()			abstract;
	virtual void render(HDC hdc)	abstract;


public:
	//setter
	inline	void	setHp(int nAmount)				{ _nHp = nAmount; }
	inline	void	setAttack(int nAmount)			{ _nAttack = nAmount; }
	inline	void	setDefence(int nAmount)			{ _nDefence = nAmount; }
	inline	void	setSpeed(float fAmount)			{ _fSpeed = fAmount; }
	inline	void	setSearchRange(float fAmount)	{ _fSearchRange = fAmount; }
	inline	void	setAttackRange(float fAmount)	{ _fAttackRange = fAmount; }
	inline	void	setAttackSpeedps(float fAmount) { _fAttackSpeedps = fAmount; }

	//getter
	inline	int		getHp()				{ return _nHp; }
	inline	int		getAttack()			{ return _nAttack; }
	inline	int		getDefence()		{ return _nDefence; }
	inline	float	getSpeed()			{ return _fSpeed; }
	inline	float	getSearchRange()	{ return _fSearchRange; }
	inline	float	getAttackRange()	{ return _fAttackRange; }
	inline	float	getAttackSpeedps()	{ return _fAttackSpeedps; }


};