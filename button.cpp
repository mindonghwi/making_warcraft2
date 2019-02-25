#include "stdafx.h"
#include "button.h"


button::button()
{
}


button::~button()
{
}

HRESULT button::init(const char * imageName, int x, int y, POINT btnDownFramePoint, POINT btnUpFramePoint, function<void(void)> cbFunction)
{
	_callbackFunction = move(cbFunction);

	_direction = BUTTONDIRECTION_NULL;

	_x = static_cast<float>(x);
	_y = static_cast<float>(y);

	_btnUpFramePoint = btnUpFramePoint;
	_btnDownFramePoint = btnDownFramePoint;

	_imageName = imageName;
	_image = IMAGEMANAGER->findImage(imageName);

	_rc = RectMakeCenter(x, y, _image->getFrameWidth(), _image->getFrameHeight());


	return S_OK;
}



void button::release()
{
}

void button::update()
{
	if (PtInRect(&_rc, _ptMouse))
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			_direction = BUTTONDIRECTION_DOWN;
		}
		else if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON) && _direction == BUTTONDIRECTION_DOWN)
		{
			_direction = BUTTONDIRECTION_UP;
			_callbackFunction();
		}
	}
	else _direction = BUTTONDIRECTION_NULL;


}

void button::render(HDC hdc)
{
	switch (_direction)
	{
		case BUTTONDIRECTION_NULL:	case BUTTONDIRECTION_UP:
			_image->frameRender(hdc, _rc.left, _rc.top,
				_btnUpFramePoint.x, _btnUpFramePoint.y);
		break;
		case BUTTONDIRECTION_DOWN:
			_image->frameRender(hdc, _rc.left, _rc.top,
				_btnDownFramePoint.x, _btnDownFramePoint.y);
		break;
	
	}
}
