#pragma once

#include "stdafx.h"
#include "buildMgr.h"
#include "resources.h"

class PLAYER;
class UNIT;

class COMMAND {
	//플레이어가 커맨드를 내린다.
	//그에따른 명령을 받는 유닛들의 상태가 변한다.
	//커맨드가 내려오면 해당 유닛의 행동과 상태를 변화시킨다.

public:
	enum class E_COMMAND
	{
		E_STOP			= 0x00,
		E_HOLD			= 0x01,
		E_MOVE			= 0x02,
		E_ATTACK		= 0x04,
		E_BUILD			= 0x08,
		E_HARVEST		= 0x10,
		E_HEAL			= 0x20,
		E_BLIZZARD		= 0x40,
		E_RANGEATTACT	= 0x80
	};

	enum{E_COMMANDCOUNT = 9};
protected:
	float				_fPosX;
	float				_fPosY;
	UNIT*				_pTarget;
	BUILDMGR::E_BUILDS	_eBuild;
	float				_fAngle;
	RESOURCES*			_pResources;
	E_COMMAND			_eCommand;
	UNIT*				_pUnit;		//해당 커맨드를 받는 유닛
public:
	COMMAND();
	virtual ~COMMAND();

	//커맨드 사용순서 1. init 2. commandUnit
	virtual	void	commandUnit();														//스탑 홀드
	virtual void	commandUnit(float fPosX, float fPosY);								//이동 블리자드
	virtual void	commandUnit(float fPosX, float fPosY,BUILDMGR::E_BUILDS eBuild);	//빌드용
	virtual void	commandUnit(UNIT* pUnit);											//힐 공격
	virtual	void	commandUnit(float fPosX, float fPosY, float fAngle);				//이동폭발공격
	virtual void	commandUnit(RESOURCES* pResources);									//자원채취용
	
	virtual void	init(E_COMMAND eCommand,UNIT* pUnit)	abstract;

	virtual void	start()		abstract;

	inline	void	setCommand(E_COMMAND eCommand) { _eCommand = eCommand; }
	inline	E_COMMAND	getCommand() { return _eCommand; }
	inline	void	setUnit(UNIT* pUnit) { _pUnit = pUnit; }
};

