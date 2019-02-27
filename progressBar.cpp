#include "stdafx.h"
#include "progressBar.h"


progressBar::progressBar()
{
}


progressBar::~progressBar()
{
}

HRESULT progressBar::init(float x, float y, int width, int height)
{
	_x = x;
	_y = y;

	_rcProgress = RectMake(x, y, width, height);

	_progressBarTop = IMAGEMANAGER->addImage("frontBar", "hpBarTop.bmp", x, y, width, height, true, Mins::getMazenta());
	_progressBarBottom = IMAGEMANAGER->addImage("backBar", "hpBarBottom.bmp", x, y, width, height, true, Mins::getMazenta());

	//프로그레스 바 이미지의 크기가 가로크기가 된다.
	_width = static_cast<float>(_progressBarBottom->GetWidth());

	return S_OK;
}

void progressBar::release()
{
}

void progressBar::update()
{
	_rcProgress = RectMakeCenter(_x, _y, _progressBarTop->GetWidth(), _progressBarTop->GetHeight());
}

void progressBar::render()
{
	//렌더는 그려주는 순서 영향을 받는다. 그려지는 순서대로 앞으로 나온다
	IMAGEMANAGER->render("backBar", getMemDC(),
		_rcProgress.left + _progressBarBottom->GetWidth() / 2,
		static_cast<int>(_y) + _progressBarBottom->GetHeight() / 2, 0, 0,
		_progressBarBottom->GetWidth(), _progressBarBottom->GetHeight());

	//앞에 그려지는 게이지의 가로크기를 조절한다.
	IMAGEMANAGER->render("frontBar", getMemDC(),
		_rcProgress.left + _progressBarBottom->GetWidth() / 2,
		static_cast<int>(_y) + _progressBarBottom->GetHeight() / 2, 0, 0,
		static_cast<int>(_width), _progressBarBottom->GetHeight());



}

void progressBar::setGauge(float currentGauge, float maxGauge)
{
	//수치가 들어오면 계산해준다.
	_width = (currentGauge / maxGauge) * _progressBarBottom->GetWidth();
}
