#pragma once
#include "command.h"

class COMMAND_RETURN_HARVEST : public COMMAND
{
private:
	//�������� �������� ���� �ڿ� ĳ�� ������ �ǹ� ã�Ƽ� ���´������ �ְ� �ٽ� ä��Ŀ�ǵ� ��������
public:
	COMMAND_RETURN_HARVEST();
	~COMMAND_RETURN_HARVEST();

	virtual void	commandUnit(RESOURCES* pResources)		override;			//�ڿ�ä���
	virtual void	init(E_COMMAND eCommand, UNIT* pUnit)	override;
	virtual void	start()		override;

};

//Ŀ�ǵ� ť�� ���� ó������ �̰� �װ� ����̴�.
