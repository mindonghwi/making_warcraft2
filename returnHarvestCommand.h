#pragma once
#include "command.h"

class COMMAND_RETURN_HARVEST : public COMMAND
{
private:
	//여서부터 만들어야함 지금 자원 캐고 다차면 건물 찾아서 가는대까지함 넣고 다시 채취커맨드 날려야함
public:
	COMMAND_RETURN_HARVEST();
	~COMMAND_RETURN_HARVEST();

	virtual void	commandUnit(RESOURCES* pResources)		override;			//자원채취용
	virtual void	init(E_COMMAND eCommand, UNIT* pUnit)	override;
	virtual void	start()		override;

};

//커맨드 큐를 만들어서 처리하자 이건 그게 방법이다.
