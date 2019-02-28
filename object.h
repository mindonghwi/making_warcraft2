#pragma once

#include "stdafx.h"


class OBJECT abstract {


protected:
	float		_posX;		//중심좌표 x
	float		_posY;		//중심좌표 y
	int			_width;		//가로길이
	int			_height;	//세로길이
	int			_left;		//사각형 왼쪽
	int			_top;		//사각형 위
	image*		_pImg;		//이미지 설정
	RECT		_rc;		//사각형
	int			_posZ;		//zoder용

public:
	//x,y가로길이 세로길이 초기화
	virtual void init(float posX, float posY, int width, int height);

	//자식들에서 재정의 필수
	virtual void update()			abstract;
	virtual void release()			abstract;
	virtual void render(HDC hdc)	abstract;

	void setImage(image* pImage);
	int getLeft();
	int getTop();

	void settingRect();

public:
	//get set inline모음
	inline float getPosX() { return _posX; }
	inline float getPosY() { return _posY; }
	inline int getWidth() { return _width; }
	inline int getHeight() { return _height; }
	inline image* getImage() { return _pImg; }
	inline int getPosZ() { return _posZ; }

	inline void setPosX(float posX) { _posX = posX; }
	inline void setPosY(float posY) { _posY = posY; }
	inline void setWidth(int width) { _width = width; }
	inline void setHeight(int height) { _height = height; }
	inline void	setPosZ(int posZ) { _posZ = posZ; }

	
};

