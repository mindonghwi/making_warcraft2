#pragma once
#include "singletonBase.h"
#include <bitset>

using namespace std;

#define KEYMAX 256 //키가 눌러지는 모든 포함조건이 256임

class keyManager : public singletonBase<keyManager>
{
private:
	enum {KEYMAXCOUNT = 256};

	enum class KEYINPUT{
		KEY_STAY_UP = 0,		//키가 안눌린 상태로 머물고 있다.
		KEY_UP,					//키가 올라왔다.
		KEY_STAY_DOWN,			//키가 눌린 상태이다.
		KEY_DOWN,				//키가 눌렸다.
		MAX
	};

private:
	bitset<KEYMAX> _keyUp;
	bitset<KEYMAX> _keyDown;

	
	bool _isDBCLbutton;
	bool _isDBCRButton;

	KEYINPUT	_arKey[KEYMAXCOUNT];
	bool		_arKeyDouble[KEYMAXCOUNT];
	int			_arKeyDownCount[KEYMAXCOUNT];
	float		_fDoubleClickTime;
	
private:
	void	initKeyDouble();

public:
	keyManager();
	~keyManager();

	HRESULT init();
	void release();
	void update();
	//키를 한번만 누르면
	bool isOnceKeyDown(int key);
	//키를 눌렀다 떼면
	bool isOnceKeyUp(int key);
	//키를 계속 누르고 있으면
	bool isStayKeyDown(int key);
	//토글이면은 계속 체크되고있는 상태 아닌가요? ㅎㅎㅎㅎㅎ
	bool isToggleKey(int key);

	bool isKeyDown(int key);

	bitset<KEYMAX> getKeyUp() { return _keyUp; }
	bitset<KEYMAX> getKeyDown() { return _keyDown; }

	void setKeyDown(int key, bool state) { _keyDown.set(key, state); }
	void setKeyUp(int key, bool state) { _keyUp.set(key, state); }

	bool isDBClickLButton();
	bool isDBClickRButton();

	bool isDBClickKey(int key);

	bool TranslateMessage(const MSG * pMSG);
};

