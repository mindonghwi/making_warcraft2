#pragma once
#include "stdafx.h"
#include "state.h"

//������� ���� ���� �ִ� �͵��� ó���� ���̴�.
//�������� �������� ���⿡ ��� �� ���̴�.
//�ϱ����� ä���� ����� �ð��̴�.
class STATE_SPECIAL : public STATE
{
private:


public:
	STATE_SPECIAL();
	~STATE_SPECIAL();

	virtual void start()	override;
	virtual void update()	override;

};