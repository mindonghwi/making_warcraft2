#pragma once

#include "stdafx.h"
class PLAYER;

class COMMAND {
	//�÷��̾ Ŀ�ǵ带 ������.
	//�׿����� ����� �޴� ���ֵ��� ���°� ���Ѵ�.
	
public:
	virtual	void	commandUnit(PLAYER pPlayer)	abstract;


};