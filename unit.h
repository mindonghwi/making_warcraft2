#pragma once
#include "stdafx.h"
#include "object.h"
#include "state.h"
#include "behavier.h"


class UNIT : public OBJECT {
public:
	enum class E_STATENUM
	{
		E_IDLE = 0,
		E_MOVE,
		E_PATROL,
		E_ATTACK,
		E_ATTACK_MOVE,
		E_HOLD,
		E_SPECIAL_01,		//스페셜의 늘어날수 있기에 방지 코드 ex) 채집도 하고 터지기도 하고 하면
		E_MAX
	};

	enum class E_BEHAVIERNUM
	{
		E_NONE = 0,		//대기
		E_ATTACK,		
		E_MOVE,			
		E_HARVEST,		
		E_MAGIC,		//마법사-> 마법, 드워프->자폭, 기사-> 마법
		E_MAX
	};

protected:
	int		_nHp;
	int		_nAttack;
	int		_nDefence;

	float	_fSpeed;
	float	_fSearchRange;
	float	_fAttackRange;		//
	float	_fAttackSpeedps;	//초당 몇번 공격하는지

	//상태들이 불러온다. 상태 패턴
	STATE*			_arState[static_cast<const int>(UNIT::E_STATENUM::E_MAX)];
	//행동들을 불러온다. 스트래티지 패턴
	BEHAVIER*		_arBeHavier[static_cast<const int>(UNIT::E_BEHAVIERNUM::E_MAX)];

	STATE*			_pCurrentState;
	BEHAVIER*		_pCurrentBeHavier;
public:
	UNIT();
	virtual ~UNIT();

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
	inline	void	setCurrentState(UNIT::E_STATENUM eStateNum) { _pCurrentState = _arState[static_cast<int>(eStateNum)]; }
	inline	void	setCurrentBehavir(UNIT::E_BEHAVIERNUM eBehavier) { _pCurrentBeHavier = _arBeHavier[static_cast<int>(eBehavier)]; }



	//getter
	inline	int		getHp()				{ return _nHp; }
	inline	int		getAttack()			{ return _nAttack; }
	inline	int		getDefence()		{ return _nDefence; }
	inline	float	getSpeed()			{ return _fSpeed; }
	inline	float	getSearchRange()	{ return _fSearchRange; }
	inline	float	getAttackRange()	{ return _fAttackRange; }
	inline	float	getAttackSpeedps()	{ return _fAttackSpeedps; }

	inline	void	getCurrentState() { _pCurrentState; }
	inline	void	getCurrentBehavir() { _pCurrentBeHavier; }
	
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