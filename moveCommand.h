#pragma once
#include "command.h"

class COMMAND_MOVE : public COMMAND
{
private:

public:
	COMMAND_MOVE();
	~COMMAND_MOVE();

	virtual void	commandUnit(float fPosX, float fPosY)	override;								//�̵� ���ڵ�
	virtual void	init(E_COMMAND eCommand, UNIT* pUnit)	override;
	virtual void	start()		override;

};

//Ŀ�ǵ� ť�� ���� ó������ �̰� �װ� ����̴�.
