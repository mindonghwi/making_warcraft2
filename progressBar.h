#pragma once
#include "gameNode.h"

class progressBar : public gameNode
{
private:
	RECT _rcProgress;		//프로그레스 바 렉트
	float _x, _y;			//프로그레스 바 좌표
	float _width;			//가로크기

	image* _progressBarTop;
	image* _progressBarBottom;

public:
	progressBar();
	~progressBar();

	HRESULT init(float x, float y, int width, int height);
	void release();
	void update();
	void render();

	void setGauge(float currentGauge, float maxGauge);

	void setX(float x) { _x = x; }
	void setY(float y) { _y = y; }

};

