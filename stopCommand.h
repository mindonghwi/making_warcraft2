#pragma once
#include "command.h"

class COMMAND_STOP : public COMMAND
{
private:

public:
	COMMAND_STOP();
	~COMMAND_STOP();

	virtual	void	commandUnit()	override;
	virtual void	init(E_COMMAND eCommand, UNIT* pUnit)	override;
	virtual void	start()		override;

};

//커맨드 큐를 만들어서 처리하자 이건 그게 방법이다.
