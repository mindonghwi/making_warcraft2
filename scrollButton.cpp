#include "stdafx.h"
#include "scrollButton.h"

SCROLLBUTTON::SCROLLBUTTON()
{
}

SCROLLBUTTON::~SCROLLBUTTON()
{
}

HRESULT SCROLLBUTTON::init(int nLeft, int nTop, int nWidth, int nHeight, int nReserve)
{
	//버튼들 초기화
	_vButtons.clear();
	_vButtons.reserve(nReserve);

	//스크롤박스 위치 잡기
	_nLeft = nLeft;
	_nTop = nTop;
	_nWidth = nWidth;
	_nHeight = nHeight;
	_nBtnHeight = nHeight;
	//보이는 박스사이즈, 진짜 스크롤박스 사이즈
	_rcViewBox = RectMake(_nLeft, _nTop, _nWidth, _nHeight);
	_rcScrollBox = RectMake(_nLeft, _nTop, _nWidth, _nHeight);

	_direction = SCROLLBUTTONDIRECTION::DISABLE;

	_nTopBtnIndex = 0;

	return E_NOTIMPL;
}

HRESULT SCROLLBUTTON::addBtn(const char * imageName, POINT btnDownFramePoint, POINT btnUpFramePoint, function<void(void)> cbFunction)
{
	_vButtons.push_back(new button);
	_vButtons.back()->init(imageName, _nLeft, _nTop + _nHeight - _nBtnHeight, btnDownFramePoint, btnUpFramePoint, cbFunction);
	_vButtons.back()->setScrollNum(static_cast<int>(_vButtons.size())-1);

	_nHeight += _nBtnHeight;
	_rcScrollBox = RectMake(_nLeft, _nTop, _nWidth, _nHeight);
	return S_OK;
}

HRESULT SCROLLBUTTON::addBtn(const char * imageName, function<void(void)> cbFunction)
{
	_vButtons.push_back(new button);
	_vButtons.back()->init(imageName, _nLeft, _nTop + _nHeight - _nBtnHeight, cbFunction);

	_nHeight += _nBtnHeight;
	_rcScrollBox = RectMake(_nLeft, _nTop, _nWidth, _nHeight);

	return S_OK;
}

void SCROLLBUTTON::release()
{
	for (int i = 0; i < static_cast<int>(_vButtons.size()); i++)
	{
		button* pBtn = _vButtons.back();
		pBtn->release();
		_vButtons.pop_back();
		delete pBtn;
		pBtn = nullptr;	
	}

}

void SCROLLBUTTON::update()
{
	//스크롤 박스가 비 활성화 상태에서
	if (_direction != SCROLLBUTTONDIRECTION::ACTIVE)
	{
		if (PtInRect(&_rcViewBox, _ptMouse))
		{
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
			{
				_direction = SCROLLBUTTONDIRECTION::ACTIVE;
				initSelected();
				readyStateBtn();
			}
		}
	}
	else if (_direction == SCROLLBUTTONDIRECTION::ACTIVE)
	{
		if (PtInRect(&_rcScrollBox, _ptMouse))
		{
			for (int i = 0; i < static_cast<int>(_vButtons.size()); i++)
			{
				_vButtons[i]->update();
				if (_vButtons[i]->getIsSelected())
				{
					_direction = SCROLLBUTTONDIRECTION::DISABLE;
					_nTopBtnIndex = _vButtons[i]->getScrollNum();
					changeVectorTop(i);
					
				}
			}
		}
		else
		{
			if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON))
			{
				_direction = SCROLLBUTTONDIRECTION::DISABLE;
				initSelected();
			}
		}
	}
}

void SCROLLBUTTON::render(HDC hdc)
{
	//스크롤 박스가 비 활성화 상태에서
	if (_direction != SCROLLBUTTONDIRECTION::ACTIVE)
	{
		_vButtons.front()->render(hdc);
	}
	else if (_direction == SCROLLBUTTONDIRECTION::ACTIVE)
	{
		for (int i = 0; i < static_cast<int>(_vButtons.size()); i++)
		{
			_vButtons[i]->render(hdc);
		}
	}
}

void SCROLLBUTTON::changeVectorTop(int nChangeIndex)
{
	button* pBtn = _vButtons.front();
	float fPosX = 0.0f;
	float fPosY = 0.0f;

	fPosX = pBtn->getX();
	fPosY = pBtn->getY();

	_vButtons[0] = _vButtons[nChangeIndex];

	_vButtons[nChangeIndex] = pBtn;
	_vButtons[nChangeIndex]->setX(_vButtons[0]->getX());
	_vButtons[nChangeIndex]->setY(_vButtons[0]->getY());

	_vButtons[0]->setX(fPosX);
	_vButtons[0]->setY(fPosY);
	
	_vButtons[nChangeIndex]->reSettingRect();
	_vButtons[0]->reSettingRect();
	
	
	pBtn = nullptr;
}

void SCROLLBUTTON::initSelected()
{
	for (int i = 0; i < static_cast<int>(_vButtons.size()); i++)
	{
		_vButtons[i]->setIsSelected(false);
	}
}

void SCROLLBUTTON::readyStateBtn()
{
	for (int i = 0; i < static_cast<int>(_vButtons.size()); i++)
	{
		_vButtons[i]->setDirection(BUTTONDIRECTION::BUTTONDIRECTION_DOWN);
	}
}
