#pragma once
#include "gameNode.h"
#include "button.h"
#include "stdafx.h"

enum SCROLLBUTTONDIRECTION
{
	DISABLE,
	ACTIVE
};

class SCROLLBUTTON
{
private:
	SCROLLBUTTONDIRECTION _direction;	//버튼의 상태 이넘문

	RECT _rcViewBox;
	RECT _rcScrollBox;
	int _nLeft;
	int _nTop;
	int _nWidth;
	int _nHeight;
	int _nTopBtnIndex;

	int _nBtnHeight;
	vector<button*>	_vButtons;
	
public:
	SCROLLBUTTON();
	~SCROLLBUTTON();

	HRESULT init(int nLeft, int nTop, int nWidth,int nHeight, int nReserve);

	HRESULT addBtn(const char* imageName,
		POINT btnDownFramePoint, POINT btnUpFramePoint,
		function<void(void)> cbFunction);

	HRESULT addBtn(const char* imageName,
		function<void(void)> cbFunction);


	void release();
	void update();
	void render(HDC hdc);

	void changeVectorTop(int nChangeIndex);

	void initSelected();
	void readyStateBtn();
};

