#pragma once
#include "command.h"

class COMMAND_BUILD : public COMMAND
{
private:

public:
	COMMAND_BUILD();
	~COMMAND_BUILD();

	virtual void	commandUnit(float fPosX, float fPosY, E_BUILDS eBuild) override;	//�����
	virtual void	init(E_COMMAND eCommand, UNIT* pUnit)	override;
	virtual void	start()		override;

};

//Ŀ�ǵ� ť�� ���� ó������ �̰� �װ� ����̴�.
