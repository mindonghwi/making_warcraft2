#pragma once
#include "command.h"

class COMMAND_HARVEST: public COMMAND
{
private:

public:
	COMMAND_HARVEST();
	~COMMAND_HARVEST();

	virtual void	commandUnit(RESOURCES* pResources)		override;			//�ڿ�ä���
	virtual void	init(E_COMMAND eCommand, UNIT* pUnit)	override;
	virtual void	start()		override;

};

//Ŀ�ǵ� ť�� ���� ó������ �̰� �װ� ����̴�.
