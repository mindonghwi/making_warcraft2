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

public:

	//커맨더 쓸수 있는거 정리해본것
	//virtual void Idle();
	//virtual void Attack();
	//virtual void move();
	//virtual void patrol();
	//virtual void hold();
	//virtual void harvestGold();
	//virtual void harvestTree();
	//virtual void harvestOil();
	//virtual void moveAttack();
	//virtual void special();
	//virtual void magic(); 기사는 3개 드워프가1개 마법사가 5개
	


	//상태를 정리해보자
	//정지 -> 정지
	//이동 -> 걷는다. 난다
	//공격이동 -> 공격이동
	//홀드 -> 홀드
	//패트롤 -> 순찰
	//금자원 채집중
	//오일자원 채집중
	//공격 -> 마법공격, 일반공격(사거리기준)
	//나무자원 채집중

};