#pragma once
#include "stdafx.h"
#include "object.h"
#include "state.h"
#include "behavier.h"
#include "camera.h"
#include "aStar.h"
#include "buildMgr.h"

#include "command.h"
class PLAYER;
class RESOURCEMGR;
class BUILDMGR;
class COMMAND;
class UNITMGR;
class MAP;
class BULLETMGR;

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
		E_NONE,
		E_MAX
	};

	enum class E_BEHAVIERNUM
	{
		E_NONE = 0,		//대기
		E_ATTACK,
		E_MOVE,
		E_HARVEST,
		E_MAGIC,		//마법사-> 마법, 드워프->자폭, 기사-> 마법
		E_HOLD,
		E_TRANSPORTOUT,
		E_TRANSPORTIN,
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
		E_DEATH,				//죽음은 방향성이 없으니
		E_MAX
	};

	enum class E_STATE
	{
		E_IDLE = 0,
		E_MOVE,
		E_ATTACK,
		E_DEATH,
		E_NONE,
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
		E_RECONNAISSANCE,	//정찰병
		E_OILTANKER,
		E_GALLEYS,			//작은 공격배
		E_TRANSPORT,
		E_BATTLESHIP,
		E_SUBMARIN,
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
	int		_nAttack;
	int		_nDefence;

	float	_fSpeed;
	float	_fSearchRange;
	float	_fAttackRange;		//
	float	_fAttackSpeedps;	//초당 몇번 공격하는지
	int		_nMinimalAttack;
	//상태들이 불러온다. 상태 패턴
	STATE*			_arState[static_cast<const int>(UNIT::E_STATENUM::E_MAX)];
	//행동들을 불러온다. 스트래티지 패턴
	BEHAVIER*		_arBeHavier[static_cast<const int>(UNIT::E_BEHAVIERNUM::E_MAX)];

	STATE*			_pCurrentState;
	BEHAVIER*		_pCurrentBeHavier;

	int				_arStateStartIndex[static_cast<const int>(UNIT::E_STATE::E_MAX)];	//상태의 시작 인덱스
	int				_arStateEndIndex[static_cast<const int>(UNIT::E_STATE::E_MAX)];		//상태의 끝나는 인덱스
	E_DIRECTION		_eDirection;
	float			_arFramePerSeconds[static_cast<const int>(UNIT::E_STATE::E_MAX)];
	E_UNIT			_eUnit;

	int				_nFrameX;
	E_HARVEST		_eHarvest;

	CAMERA*			_pCamera;

	ASTAR*			_pAstar;


	RECT			_rcCollision;

	int				_nPopulation;

	bool			_bIsSelected;	//선택되었는지 아닌지

	vector<vector<int>>	_vvMovePoint;	//x,y좌표를 가지고 있는 리스트
	int					_nMoveVectorIndex;//움직이는 포인트 인덱스

	bool				_bIsMoving;//이동중인지

	float				_fDirAngle;
	float				_travelRange;

	float				_fMoveSpeed;

	float					_fEndX;
	float					_fEndY;
	int					_nIndexNum;


	E_BEHAVIERNUM		_eBehavier;


	BUILDMGR*			_pBuildMgr;

	//build
	bool				_bNormalBuildingOn;
	E_BUILDS	_eBuilds;
	
	
	unsigned int			_nCommand;
	queue<COMMAND*>			_queWaitCommand;
	
	UNITMGR*				_pUnitMgr;

	bool				_bIsBannedSelected;


	MAP*				_pMap;

	OBJECT*				_pTarget;

	RESOURCEMGR*	_pResourceMgr;
	PLAYER*			_pPlayer;
	int				_nMaxHp;
	BULLETMGR*		_pBulletMgr;

	PLAYER*		_pOpponent;

	bool		_bIsHold;
	bool		_bIsMoveAttack;
public:
	UNIT();
	virtual ~UNIT();

	//그냥 초기화
	virtual void init(int nPosX, int nPosY, int nWidth, int nHeight, int nIndexNum);

	//만들때 사용
	virtual void create(int nPosX, int nPosY, int nHp, float nSpeed, int nAttack, int nDefence, float fSearchRange, float fAttackRange, float fAttackSpeedps,int nMinimalAttack);

	virtual void update()			abstract;
	virtual void release();
	virtual void render(HDC hdc)	abstract;
	virtual void updateBehavier()	abstract;
	virtual	void renderSelected(HDC hdc) abstract;

	virtual void commandMove(float fEndPosX, float fEndPosY);

	virtual void command();
	
	virtual void setMovePoints(float fEndPosX,float fEndPosY);
	virtual void setMovePoints(float fEndPosX, float fEndPosY, ASTAR::MOVEHEIGHT eMoveHeight);
	virtual void Move();

	virtual void build(float fPosX,float fPosY,E_BUILDS eBuilds);
	virtual void commandBuild();
	bool moveTo();

	void moveToDir();

	virtual void commandIdle();

	void addCommand(COMMAND* pCommand);
	void clearCommand();


	virtual void attack(OBJECT* pObject);
	void targetDirection();

	virtual	void harvestResources();
	virtual void commandHarvest();
	virtual void commandReturnHarvest();

	virtual bool IsNearResources();

	virtual void updateRect();

	virtual	void removeMapUnitData();
	virtual	void addMapUnitData();


	virtual	void fireBullet();

	virtual void searchOppent();

	virtual void commandHold();

	virtual void commandTransport();		//대기하는 것
	virtual void commandTransportIn();		//탑승
	virtual void commandTransportOut(int nMapIndexX, int nMapIndexY);		//하역
public:
	//setter
	inline	void	setHp(int nAmount) { OBJECT::setHp(nAmount); }
	inline	void	setAttack(int nAmount) { _nAttack = nAmount; }
	inline	void	setDefence(int nAmount) { _nDefence = nAmount; }
	inline	void	setSpeed(float fAmount) { _fSpeed = fAmount; }
	inline	void	setSearchRange(float fAmount) { _fSearchRange = fAmount; }
	inline	void	setAttackRange(float fAmount) { _fAttackRange = fAmount; }
	inline	void	setAttackSpeedps(float fAmount) { _fAttackSpeedps = fAmount; }
	inline	void	setDirAngle(float fAngle) { _fDirAngle = fAngle; }
	inline	void	setMiniMalAttack(int fAmount) { _nMinimalAttack = fAmount; }
	inline	void	setBuildingOn(bool bIsBuildingOn){ _bNormalBuildingOn = bIsBuildingOn;}
	inline	void	setBuildType(E_BUILDS eBuilds){_eBuilds = eBuilds;}
	inline	void	setMaxHp(int nMaxHp) { _nMaxHp = nMaxHp; }


	//상태와 행동 패턴
	inline	void	setCurrentState(UNIT::E_STATENUM eStateNum) { _pCurrentState = _arState[static_cast<int>(eStateNum)]; }
	inline	void	setCurrentBehavir(UNIT::E_BEHAVIERNUM eBehavier) { _pCurrentBeHavier = _arBeHavier[static_cast<int>(eBehavier)]; }

	//무슨유닛인지 알아야하니깐
	inline	void	setUnit(UNIT::E_UNIT eUnit) { _eUnit = eUnit; }

	//애니메이션용
	inline	void	setFPS(UNIT::E_STATE eState, float fFps) { _arFramePerSeconds[static_cast<int>(eState)] = fFps; }
	inline	void	setStartIndex(UNIT::E_STATE eState, int nIndex) { _arStateStartIndex[static_cast<int>(eState)] = nIndex; }
	inline	void	setEndIndex(UNIT::E_STATE eState, int nIndex) { _arStateEndIndex[static_cast<int>(eState)] = nIndex; }
	inline	void	setFrameX(int nFrameX) { _nFrameX = nFrameX; }

	//들고있는 자원
	inline	void	setHarvest(UNIT::E_HARVEST eHarvest) { _eHarvest = eHarvest; }

	//linker
	inline	void	setLinkCamera(CAMERA* pCamera) { _pCamera = pCamera; }
	inline	void	setLinkAStar(ASTAR*	pAstar) { _pAstar = pAstar; }
	inline	void	setLinkBuildMgr(BUILDMGR* pBuildMgr) {_pBuildMgr = pBuildMgr; }
	inline	void	setLinkUnitMgr(UNITMGR*	pUnitMgr) { _pUnitMgr = pUnitMgr; }
	inline	void	setLinkMap(MAP* pMap) { _pMap = pMap; }
	inline	void	setLinkResourceMgr(RESOURCEMGR* pResourceMgr) { _pResourceMgr = pResourceMgr; }
	inline	void	setLinkMyPlayer(PLAYER* pPlayer) { _pPlayer = pPlayer; }
	inline	void	setLinkBulletMgr(BULLETMGR* pBulletMgr) { _pBulletMgr = pBulletMgr; }

	inline	MAP*	getMap() { return _pMap; }

	inline	void	setCollisionRect(int nLeft, int nRight, int nWidth, int nHeight) { _rcCollision = RectMake(nLeft, nRight, nWidth, nHeight); }
	inline	void	setCollisionRect(RECT& rcTmp) { _rcCollision = rcTmp; }
	inline	void	setCollisionRect(float fPosX, float fPosY, int nWidth, int nHeight) { _rcCollision = RectMakeCenter(fPosX, fPosY, nWidth, nHeight); }

	//유닛이 차지하는 인구수
	inline	void	setPopulation(int nPopulation) { _nPopulation = nPopulation; }

	inline	void	setSelected(bool bIsSelected) { _bIsSelected = bIsSelected; }

	inline	void	setMoveIndex(int nIndex) { _nMoveVectorIndex = nIndex; }
	inline	void	setBehavier(UNIT::E_BEHAVIERNUM eBehavier) { _eBehavier = eBehavier; }
	

	//선택 가능 여부
	inline	void	setIsBannedSelect(bool bIsBannedSelect) { _bIsBannedSelected = bIsBannedSelect; }
	inline	bool	getIsBannedSelect() {return _bIsBannedSelected; }

	//getter
	inline	int		getHp() { return OBJECT::getHp(); }
	inline	int		getAttack() { return _nAttack; }
	inline	int		getDefence() { return _nDefence; }
	inline	float	getSpeed() { return _fSpeed; }
	inline	float	getSearchRange() { return _fSearchRange; }
	inline	float	getAttackRange() { return _fAttackRange; }
	inline	float	getAttackSpeedps() { return _fAttackSpeedps; }
	inline	int		getMiniMalAttack() { return _nMinimalAttack; }
	inline	int		getMaxHp() { return _nMaxHp; }

	//애니메이션용
	inline	float	getFPS(UNIT::E_STATE eState) { return _arFramePerSeconds[static_cast<int>(eState)]; }
	inline	int		getStartIndex(UNIT::E_STATE eState) { return _arStateStartIndex[static_cast<int>(eState)]; }
	inline	int		getEndIndex(UNIT::E_STATE eState) { return _arStateEndIndex[static_cast<int>(eState)]; }
	inline	int		getFrameX() { return _nFrameX; }
	//상태와 행동 패턴
	inline	STATE*		getCurrentState() { return _pCurrentState; }
	inline	BEHAVIER*	getCurrentBehavir() { return _pCurrentBeHavier; }

	//무슨유닛인지 알아야하니깐
	inline	UNIT::E_UNIT	getUnit() { return _eUnit; }

	//들고있는 자원
	inline	UNIT::E_HARVEST	getHarvest() { return _eHarvest; }

	inline	LPRECT	getCollisionRect() { return &_rcCollision; }
	inline	LPCRECT	getConstCollisionRect() { return &_rcCollision; }

	//유닛이 차지하는 인구수
	inline	int		getPopulation() { return _nPopulation; }

	inline	bool	getSelected() { return _bIsSelected; }

	inline	int		getMoveIndex() { return _nMoveVectorIndex; }

	inline	float	getDirAngle() {return _fDirAngle; }


	inline	UNIT::E_DIRECTION	getDirection() { return _eDirection; }
	inline	float	getMoveSpeed() {return _fMoveSpeed;	}

	inline	bool	getIsMovePointEmpty() { return _vvMovePoint.empty(); }

	inline	int		getMoveToPointX() { return _vvMovePoint[_nMoveVectorIndex][0]; }
	inline	int		getMoveToPointY() { return _vvMovePoint[_nMoveVectorIndex][1]; }

	inline	int		getMoveToPointEndX() {return _vvMovePoint.back().front(); }
	inline	int		getMoveToPointEndY() {return _vvMovePoint.back().back(); }

	inline	bool	getIsMoveAstar() { return _bIsMoving; }
	inline	int		getIndexNum() { return _nIndexNum; }
	inline	UNIT::E_BEHAVIERNUM	getBehavier() { return _eBehavier; }

	inline	bool	getBuildingOn() { return _bNormalBuildingOn; }
	inline	E_BUILDS	getBuildType() { return _eBuilds ; }


	//전투관련
	inline	OBJECT*	getTarget() { return _pTarget; }
	inline	void	setTarget(OBJECT* pObject) { _pTarget = pObject; }
	inline	UNITMGR*	getMyUnitMgr() {return _pUnitMgr;}

	inline	BUILDMGR*	getMyBuildMgr() {return _pBuildMgr;}
	

	inline	float	getEndPosX() {return _fEndX;}
	inline	float	getEndPosY() { return _fEndY;}

public:
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

	void	addFrameX(UNIT::E_STATE eState);
	virtual void	decreaseHp(int nHp);
	inline	PLAYER*		getOpponent() { return _pOpponent; }
	inline	void	setOpponent(PLAYER* pPlayer) { _pOpponent = pPlayer; }

	inline	bool	isHold() { return _bIsHold; }
	inline	void	setIsHold(bool bIsHold) { _bIsHold = bIsHold; }


	inline	void	setMoveAttack(bool bIsMoveAttack) { _bIsMoveAttack = bIsMoveAttack; }
	inline	bool	getMoveAttack() { return _bIsMoveAttack; }

public:

	inline	bool	getCommandQueEmpty() { return _queWaitCommand.empty(); }
};