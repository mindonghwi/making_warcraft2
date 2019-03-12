#pragma once

#include "stdafx.h"
#include "buildMgr.h"
#include "resources.h"

class PLAYER;
class UNIT;

class COMMAND {
	//�÷��̾ Ŀ�ǵ带 ������.
	//�׿����� ����� �޴� ���ֵ��� ���°� ���Ѵ�.
	//Ŀ�ǵ尡 �������� �ش� ������ �ൿ�� ���¸� ��ȭ��Ų��.

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
	UNIT*				_pUnit;		//�ش� Ŀ�ǵ带 �޴� ����
public:
	COMMAND();
	virtual ~COMMAND();

	//Ŀ�ǵ� ������ 1. init 2. commandUnit
	virtual	void	commandUnit();														//��ž Ȧ��
	virtual void	commandUnit(float fPosX, float fPosY);								//�̵� ���ڵ�
	virtual void	commandUnit(float fPosX, float fPosY,BUILDMGR::E_BUILDS eBuild);	//�����
	virtual void	commandUnit(UNIT* pUnit);											//�� ����
	virtual	void	commandUnit(float fPosX, float fPosY, float fAngle);				//�̵����߰���
	virtual void	commandUnit(RESOURCES* pResources);									//�ڿ�ä���
	
	virtual void	init(E_COMMAND eCommand,UNIT* pUnit)	abstract;

	virtual void	start()		abstract;

	inline	void	setCommand(E_COMMAND eCommand) { _eCommand = eCommand; }
	inline	E_COMMAND	getCommand() { return _eCommand; }
	inline	void	setUnit(UNIT* pUnit) { _pUnit = pUnit; }
};

