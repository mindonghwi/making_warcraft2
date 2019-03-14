#pragma once
#include "command.h"

class COMMAND_HARVEST: public COMMAND
{
private:

public:
	COMMAND_HARVEST();
	~COMMAND_HARVEST();

	virtual void	commandUnit(RESOURCES* pResources)		override;			//자원채취용
	virtual void	init(E_COMMAND eCommand, UNIT* pUnit)	override;
	virtual void	start()		override;

};

//커맨드 큐를 만들어서 처리하자 이건 그게 방법이다.
