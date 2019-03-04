#pragma once
#include "gameNode.h"

enum BUTTONDIRECTION
{
	BUTTONDIRECTION_NULL,
	BUTTONDIRECTION_UP,
	BUTTONDIRECTION_DOWN
};

class button 
{
private:
	BUTTONDIRECTION _direction;	//��ư�� ���� �̳ѹ�

	const char* _imageName;
	image* _image;
	RECT _rc;

	float _x, _y;		//��ġ ��ǥ
	POINT _btnDownFramePoint;
	POINT _btnUpFramePoint;

	function<void(void)> _callbackFunction;



public:
	button();
	~button();

	HRESULT init(const char* imageName, int x, int y,
		POINT btnDownFramePoint, POINT btnUpFramePoint,
		function<void(void)> cbFunction);

	HRESULT init(const char* imageName, int x, int y,
		function<void(void)> cbFunction);



	void release();
	void update();
	void render(HDC hdc);
};

