#pragma once
#include "command.h"

class COMMAND_BUILD : public COMMAND
{
private:

public:
	COMMAND_BUILD();
	~COMMAND_BUILD();

	virtual void	commandUnit(float fPosX, float fPosY, E_BUILDS eBuild) override;	//빌드용
	virtual void	init(E_COMMAND eCommand, UNIT* pUnit)	override;
	virtual void	start()		override;

};

//커맨드 큐를 만들어서 처리하자 이건 그게 방법이다.
