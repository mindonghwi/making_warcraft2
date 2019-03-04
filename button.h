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
	BUTTONDIRECTION _direction;	//버튼의 상태 이넘문

	const char* _imageName;
	image* _image;
	RECT _rc;

	float _x, _y;		//위치 좌표
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

