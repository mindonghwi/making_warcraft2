#pragma once
#include "image.h"

//백버퍼 전역 선언
static image* _backBuffer = IMAGEMANAGER->addImage("backBuffer", WINSIZEX, WINSIZEY);


class gameNode
{
private:
	HDC _hdc;
	//매니저를 이닛할껀지 여부
	bool _managerInit;

public:
	gameNode();
	virtual ~gameNode();

	int _ctrSelect;			//컨트롤 버튼 이넘문과 연결하기 위함

	//마소 전용 -> 디버그 모드에서 초기화가 잘되었는지 에러가 났는지 여부 등을
	//S_OK, E_FAIL, SUCCEDED 등으로 알랴줌.
	virtual HRESULT init();
	virtual HRESULT init(bool managerInit);
	virtual void release();
	virtual void update();
	virtual void render();



	LRESULT MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

	image* getBackBuffer() { return _backBuffer; }

	//DC 접근자
	HDC getMemDC() { return _backBuffer->getMemDC(); }
	HDC getHDC() { return _hdc; }

};

