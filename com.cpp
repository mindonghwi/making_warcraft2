#include "stdafx.h"
#include "com.h"

COM::COM()
{
}

COM::~COM()
{
}

void COM::update()
{
	_pUnitMgr->selectedUnit();
	dragSelect();

	//�ϱ����� ���� ȸ���� ��������Ѵ�
	//����ȸ���� �� �������� �ϱ������� ������ ������� ��
	//�ϱ��� �Ѹ��� ������ ������� �Ѵ�.
	//���� �ϱ����� ��ä�븦 ��Ų��
	//����ȸ�������� �ϱ��� 7~ 10�������� �̴���.
	
	_pUnitMgr->update();
	_pBuildMgr->update();

}
