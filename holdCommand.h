#pragma once
#include "command.h"

class COMMAND_HOLD : public COMMAND
{
private:

public:
	COMMAND_HOLD();
	~COMMAND_HOLD();

	virtual	void	commandUnit()	override;
	virtual void	init(E_COMMAND eCommand, UNIT* pUnit)	override;
	virtual void	start()		override;

};

//Ŀ�ǵ� ť�� ���� ó������ �̰� �װ� ����̴�.
