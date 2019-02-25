#include "stdafx.h"
#include "gameNode.h"


gameNode::gameNode()
{
}


gameNode::~gameNode()
{
}

HRESULT gameNode::init()
{
	_hdc = GetDC(_hWnd);
	_managerInit = false;

	return S_OK;
}

HRESULT gameNode::init(bool managerInit)
{
	_hdc = GetDC(_hWnd);
	_managerInit = managerInit;

	if (_managerInit)
	{
		SetTimer(_hWnd, 1, 10, NULL);
		KEYMANAGER->init();
		IMAGEMANAGER->init();
		TIMEMANAGER->init();
		SOUNDMANAGER->init();
		SCENEMANAGER->init();
		KEYANIMANAGER->init();
		EFFECTMGR->init();
	}

	return S_OK;
}

void gameNode::release()
{
	if (_managerInit)
	{
		KillTimer(_hWnd, 1);

		KEYMANAGER->release();
		KEYMANAGER->releaseSingleton();

		IMAGEMANAGER->release();
		IMAGEMANAGER->releaseSingleton();

		TIMEMANAGER->release();
		TIMEMANAGER->releaseSingleton();

		EFFECTMGR->release();
		EFFECTMGR->releaseSingleton();


		SOUNDMANAGER->release();
		SOUNDMANAGER->releaseSingleton();

		SCENEMANAGER->release();
		SCENEMANAGER->releaseSingleton();

		KEYANIMANAGER->release();
		KEYANIMANAGER->releaseSingleton();
	}

	ReleaseDC(_hWnd, _hdc);
}

void gameNode::update()
{
	SOUNDMANAGER->update();
	KEYMANAGER->update();
	EFFECTMGR->update();
}

void gameNode::render()
{
}



LRESULT gameNode::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage)
	{
		case WM_CREATE:

		break;
		case WM_PAINT:
		{
			this->render();
		}
		break;

		case WM_MOUSEMOVE:
			_ptMouse.x = static_cast<long>(static_cast<float>(LOWORD(lParam)));
			_ptMouse.y = static_cast<long>(static_cast<float>(HIWORD(lParam)));

		break;

		case WM_LBUTTONDOWN:
			_leftButtonDown = true;
		break;

		case WM_LBUTTONUP:
			_leftButtonDown = false;
		break;

		case WM_COMMAND:

		break;
		
		case WM_DESTROY:
			PostQuitMessage(0);
		return 0;
	}


	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}
