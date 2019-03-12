#pragma once
#include "command.h"

class COMMAND_MOVE : public COMMAND
{
private:

public:
	COMMAND_MOVE();
	~COMMAND_MOVE();

	virtual void	commandUnit(float fPosX, float fPosY)	override;								//이동 블리자드
	virtual void	init(E_COMMAND eCommand, UNIT* pUnit)	override;
	virtual void	start()		override;

};

//커맨드 큐를 만들어서 처리하자 이건 그게 방법이다.
