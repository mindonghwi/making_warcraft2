#include "stdafx.h"
#include "keyManager.h"




keyManager::keyManager()
{
}


keyManager::~keyManager()
{
}
void keyManager::initKeyDouble()
{
	for (int i = 0; i < KEYMAXCOUNT; i++)
	{
		_arKeyDouble[i] = false;
		_arKeyDownCount[i] = 0;
	}
}

HRESULT keyManager::init()
{
	for (int i = 0; i < KEYMAX; i++)
	{
		//모든 키는 현재 안눌려진 상태이다.
		this->getKeyUp().set(i, false);
	}

	for (int i = 0; i < KEYMAXCOUNT; i++)
	{
		_arKey[i] = KEYINPUT::KEY_STAY_UP;
	}
	initKeyDouble();
	_fDoubleClickTime = 0.0f;

	return S_OK;
}

void keyManager::release()
{
}

void keyManager::update()
{
	//더블클릭 초기화
	if (_fDoubleClickTime == 0.0f)
	{
		initKeyDouble();
	}

	//인풋 관리
	for (int i = 0; i < KEYMAXCOUNT; i++)
	{
		if (_arKey[i] == KEYINPUT::KEY_STAY_UP)
		{
			if ((GetAsyncKeyState(i) & 0x8000))	//키가 눌린 상태이면
			{
				_arKey[i] = KEYINPUT::KEY_DOWN;			//키가 눌린 상태로 변경
				_arKeyDownCount[i]++;
			}
			else {
				_arKey[i] = KEYINPUT::KEY_STAY_UP;		//아니면 안눌린 상태 그대로 유지
			}
		}
		else if (_arKey[i] == KEYINPUT::KEY_DOWN)
		{
			if ((GetAsyncKeyState(i) & 0x8000))	//키가 눌린 상태이면
			{
				_arKey[i] = KEYINPUT::KEY_STAY_DOWN;	//키가 눌린 상태로 변경
			}
			else {
				_arKey[i] = KEYINPUT::KEY_UP;		//아니면 안눌린 상태 그대로 유지
			}
		}
		else if (_arKey[i] == KEYINPUT::KEY_STAY_DOWN)
		{
			if ((GetAsyncKeyState(i) & 0x8000))	//키가 눌린 상태이면
			{
				_arKey[i] = KEYINPUT::KEY_STAY_DOWN;	//키가 눌린 상태로 변경
			}
			else {
				_arKey[i] = KEYINPUT::KEY_UP;		//아니면 안눌린 상태 그대로 유지
			}
		}
		else if (_arKey[i] == KEYINPUT::KEY_UP)
		{
			if ((GetAsyncKeyState(i) & 0x8000))	//키가 눌린 상태이면
			{
				_arKey[i] = KEYINPUT::KEY_DOWN;			//키가 눌린 상태로 변경
				_arKeyDownCount[i]++;
			}
			else {
				_arKey[i] = KEYINPUT::KEY_STAY_UP;		//아니면 안눌린 상태 그대로 유지
			}
		}
	}

	
	//0.5초동안 같은 키가 2번 이상이면 더블클릭으로 인정
	//스테이는 제외한다!!
	_fDoubleClickTime += TIMEMANAGER->getElapsedTime();
	if (_fDoubleClickTime > 0.5f)
	{
		for (int i = 0; i < KEYMAXCOUNT; i++)
		{

			if (_arKeyDownCount[i] >= 2)
			{
				_arKeyDouble[i] = true;
			}
			_arKeyDownCount[i] = 0;
		}

		_fDoubleClickTime = 0.0f;
	}
}


bool keyManager::isOnceKeyDown(int key)
{
	//GetASyncKeyState		키보드 상태를 체크하는데 비동기화
	//GetKeyState			키보드 상태를 체크하는데 동기화

	//if (GetAsyncKeyState(key) & 0x8000)
	//{
	//	if (!this->getKeyDown()[key])
	//	{
	//		this->setKeyDown(key, true);
	//		return true;
	//	}
	//}

	//else this->setKeyDown(key, false);

	
	if (_arKey[key] == KEYINPUT::KEY_DOWN)
	{
		return true;
	}

	return false;
}

bool keyManager::isOnceKeyUp(int key)
{
	//if (GetAsyncKeyState(key) & 0x8000)
	//{
	//	this->setKeyUp(key, true);
	//}
	//else
	//{
	//	if (this->getKeyUp()[key])
	//	{
	//		this->setKeyUp(key, false);
	//		return true;
	//	}

	//}

	//return false;
	if (_arKey[key] == KEYINPUT::KEY_UP)
	{
		return true;
	}

	return false;
}

bool keyManager::isStayKeyDown(int key)
{
	//if (GetAsyncKeyState(key) & 0x8000) return true;

	//return false;

	if (_arKey[key] == KEYINPUT::KEY_STAY_DOWN)
	{
		return true;
	}

	return false;
}

bool keyManager::isToggleKey(int key)
{
	if (GetKeyState(key) & 0x0001) return true;

	return false;
}

bool keyManager::isKeyDown(int key)
{
	if (_arKey[key] == KEYINPUT::KEY_DOWN)
	{
		return true;
	}
	if (_arKey[key] == KEYINPUT::KEY_STAY_DOWN)
	{
		return true;
	}
	return false;
}

bool keyManager::isDBClickLButton()
{
	if (_isDBCLbutton  == true)
	{
		_isDBCLbutton = false;
		return true;
	}
	
	return false;
}

bool keyManager::isDBClickRButton()
{
	if (_isDBCRButton == true)
	{
		_isDBCRButton = false;
		return true;
	}
	return false;
}

bool keyManager::isDBClickKey(int key)
{
	if (_arKeyDouble[key])
	{
		return true;
	}
	return false;
}

bool keyManager::TranslateMessage(const MSG * pMSG)
{
	switch (pMSG->message)
	{
		
	case WM_LBUTTONDBLCLK:
		_isDBCLbutton = true;
		return true;
	case WM_RBUTTONDBLCLK:
		_isDBCRButton = true;
		return true;
	}

	return false;
}
