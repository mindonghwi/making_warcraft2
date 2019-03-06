#pragma once
#include "stdafx.h"
#include "object.h"
#include "state.h"
#include "behavier.h"
#include "camera.h"
#include "aStar.h"

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


	enum class E_DIRECTION
	{
		E_RIGHT,
		E_RIGHT_TOP,
		E_TOP,
		E_LEFT_TOP,
		E_LEFT,
		E_LEFT_BOTTOM,
		E_BOTTOM,
		E_RIGHT_BOTTOM,
		E_DEATH,				//������ ���⼺�� ������
		E_MAX
	};

	enum class E_STATE
	{
		E_IDLE = 0,
		E_MOVE,
		E_ATTACK,
		E_DEATH,
		E_MAX
	};

	enum class E_UNIT
	{
		E_WORKMAN = 0,
		E_FOOTMAN,
		E_ARCHER,
		E_BALLISTA,
		E_KNIGHT,
		E_MAGICIAN,
		E_BOMBER,
		E_RECONNAISSANCE,	//������
		E_OILTANKER,
		E_GALLEYS,			//���� ���ݹ�
		E_TRANSPORT,
		E_BATTLESHIP,
		E_FLYER,
		E_MAX
	};

	enum class E_HARVEST
	{
		E_NONE = 0,
		E_GOLD,
		E_TREE,
		E_OIL,
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

	int				_arStateStartIndex[static_cast<const int>(UNIT::E_STATE::E_MAX)];	//������ ���� �ε���
	int				_arStateEndIndex[static_cast<const int>(UNIT::E_STATE::E_MAX)];		//������ ������ �ε���
	E_DIRECTION		_eDirection;
	float			_arFramePerSeconds[static_cast<const int>(UNIT::E_STATE::E_MAX)];
	E_UNIT			_eUnit;

	int				_nFrameX;
	E_HARVEST		_eHarvest;

	CAMERA*			_pCamera;

	ASTAR*			_pAstar;

public:
	UNIT();
	virtual ~UNIT();

	//�׳� �ʱ�ȭ
	virtual void init(int nPosX, int nPosY, int nWidth, int nHeight);

	//���鶧 ���
	virtual void create(int nPosX, int nPosY, int nHp, float nSpeed, int nAttack, int nDefence, float fSearchRange, float fAttackRange, float fAttackSpeedps);

	virtual void update()			abstract;
	virtual void release()			abstract;
	virtual void render(HDC hdc)	abstract;


public:
	//setter
	inline	void	setHp(int nAmount) { _nHp = nAmount; }
	inline	void	setAttack(int nAmount) { _nAttack = nAmount; }
	inline	void	setDefence(int nAmount) { _nDefence = nAmount; }
	inline	void	setSpeed(float fAmount) { _fSpeed = fAmount; }
	inline	void	setSearchRange(float fAmount) { _fSearchRange = fAmount; }
	inline	void	setAttackRange(float fAmount) { _fAttackRange = fAmount; }
	inline	void	setAttackSpeedps(float fAmount) { _fAttackSpeedps = fAmount; }

	//���¿� �ൿ ����
	inline	void	setCurrentState(UNIT::E_STATENUM eStateNum) { _pCurrentState = _arState[static_cast<int>(eStateNum)]; }
	inline	void	setCurrentBehavir(UNIT::E_BEHAVIERNUM eBehavier) { _pCurrentBeHavier = _arBeHavier[static_cast<int>(eBehavier)]; }

	//������������ �˾ƾ��ϴϱ�
	inline	void	setUnit(UNIT::E_UNIT eUnit) { _eUnit = eUnit; }

	//�ִϸ��̼ǿ�
	inline	void	setFPS(UNIT::E_STATE eState, float fFps) { _arFramePerSeconds[static_cast<int>(eState)] = fFps; }
	inline	void	setStartIndex(UNIT::E_STATE eState, int nIndex) { _arStateStartIndex[static_cast<int>(eState)] = nIndex; }
	inline	void	setEndIndex(UNIT::E_STATE eState, int nIndex) { _arStateEndIndex[static_cast<int>(eState)] = nIndex; }
	inline	void	setFrameX(int nFrameX) { _nFrameX = nFrameX; }

	//����ִ� �ڿ�
	inline	void	setHarvest(UNIT::E_HARVEST eHarvest) { _eHarvest = eHarvest; }

	inline	void	setLinkCamera(CAMERA* pCamera) { _pCamera = pCamera; }
	inline	void	setLinkAStar(ASTAR*	pAstar) { _pAstar = pAstar; }

	//getter
	inline	int		getHp() { return _nHp; }
	inline	int		getAttack() { return _nAttack; }
	inline	int		getDefence() { return _nDefence; }
	inline	float	getSpeed() { return _fSpeed; }
	inline	float	getSearchRange() { return _fSearchRange; }
	inline	float	getAttackRange() { return _fAttackRange; }
	inline	float	getAttackSpeedps() { return _fAttackSpeedps; }

	//�ִϸ��̼ǿ�
	inline	float	getFPS(UNIT::E_STATE eState) { return _arFramePerSeconds[static_cast<int>(eState)]; }
	inline	int		getStartIndex(UNIT::E_STATE eState) { return _arStateStartIndex[static_cast<int>(eState)]; }
	inline	int		getEndIndex(UNIT::E_STATE eState) { return _arStateEndIndex[static_cast<int>(eState)]; }
	inline	int		getFrameX() { return _nFrameX; }
	//���¿� �ൿ ����
	inline	STATE*		getCurrentState() { return _pCurrentState; }
	inline	BEHAVIER*	getCurrentBehavir() { return _pCurrentBeHavier; }

	//������������ �˾ƾ��ϴϱ�
	inline	UNIT::E_UNIT	getUnit() { return _eUnit; }

	//����ִ� �ڿ�
	inline	UNIT::E_HARVEST	getHarvest() { return _eHarvest; }



public:
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

	void	addFrameX(UNIT::E_STATE eState);

};