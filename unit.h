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
		E_SPECIAL_01,		//������� �þ�� �ֱ⿡ ���� �ڵ� ex) ä���� �ϰ� �����⵵ �ϰ� �ϸ�
		E_MAX
	};

	enum class E_BEHAVIERNUM
	{
		E_NONE = 0,		//���
		E_ATTACK,		
		E_MOVE,			
		E_HARVEST,		
		E_MAGIC,		//������-> ����, �����->����, ���-> ����
		E_MAX
	};

protected:
	int		_nHp;
	int		_nAttack;
	int		_nDefence;

	float	_fSpeed;
	float	_fSearchRange;
	float	_fAttackRange;		//
	float	_fAttackSpeedps;	//�ʴ� ��� �����ϴ���

	//���µ��� �ҷ��´�. ���� ����
	STATE*			_arState[static_cast<const int>(UNIT::E_STATENUM::E_MAX)];
	//�ൿ���� �ҷ��´�. ��Ʈ��Ƽ�� ����
	BEHAVIER*		_arBeHavier[static_cast<const int>(UNIT::E_BEHAVIERNUM::E_MAX)];

	STATE*			_pCurrentState;
	BEHAVIER*		_pCurrentBeHavier;
public:
	UNIT();
	virtual ~UNIT();

	//�׳� �ʱ�ȭ
	virtual void init(int nPosX, int nPosY, int nWidth, int nHeight);

	//���鶧 ���
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

	//Ŀ�Ǵ� ���� �ִ°� �����غ���
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
	//virtual void magic(); ���� 3�� �������1�� �����簡 5��
	


	//���¸� �����غ���
	//���� -> ����
	//�̵� -> �ȴ´�. ����
	//�����̵� -> �����̵�
	//Ȧ�� -> Ȧ��
	//��Ʈ�� -> ����
	//���ڿ� ä����
	//�����ڿ� ä����
	//���� -> ��������, �Ϲݰ���(��Ÿ�����)
	//�����ڿ� ä����

};