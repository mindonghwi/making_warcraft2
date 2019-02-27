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

	//���α׷��� �� �̹����� ũ�Ⱑ ����ũ�Ⱑ �ȴ�.
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
	//������ �׷��ִ� ���� ������ �޴´�. �׷����� ������� ������ ���´�
	IMAGEMANAGER->render("backBar", getMemDC(),
		_rcProgress.left + _progressBarBottom->GetWidth() / 2,
		static_cast<int>(_y) + _progressBarBottom->GetHeight() / 2, 0, 0,
		_progressBarBottom->GetWidth(), _progressBarBottom->GetHeight());

	//�տ� �׷����� �������� ����ũ�⸦ �����Ѵ�.
	IMAGEMANAGER->render("frontBar", getMemDC(),
		_rcProgress.left + _progressBarBottom->GetWidth() / 2,
		static_cast<int>(_y) + _progressBarBottom->GetHeight() / 2, 0, 0,
		static_cast<int>(_width), _progressBarBottom->GetHeight());



}

void progressBar::setGauge(float currentGauge, float maxGauge)
{
	//��ġ�� ������ ������ش�.
	_width = (currentGauge / maxGauge) * _progressBarBottom->GetWidth();
}
