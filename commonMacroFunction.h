#pragma once

//=====================================
// ## 18.11.20 ## 매크로를 모아두자 ##
//=====================================

inline POINT PointMake(int x, int y)
{
	POINT pt = { x, y };

	return pt;
}

inline void LineMake(HDC hdc, int startX, int startY, int endX, int endY)
{
	MoveToEx(hdc, startX, startY, NULL);
	LineTo(hdc, endX, endY);
}

//================= 렉트 관련 함수 ========================
//    렉트를 만든다(레프트, 탑, 가로크기, 세로크기)
inline RECT RectMake(int x, int y, int width, int height)
{
	RECT rc = { x, y, x + width, y + height };

	return rc;
}

//    렉트를 만든다(레프트, 탑, 가로크기, 세로크기)
inline RECT RectMake(float x, float y, int width, int height)
{
	RECT rc = { static_cast<int>(x), static_cast<int>(y), static_cast<int>(x) + width, static_cast<int>(y) + height };

	return rc;
}

//    렉트를 만든다(중점X좌표, 중점Y좌표, 가로크기, 세로크기)
inline RECT RectMakeCenter(int x, int y, int width, int height)
{
	RECT rc = { x - (width / 2), y - (height / 2), x + (width / 2), y + (height / 2) };

	return rc;
}
//    렉트를 만든다(중점X좌표, 중점Y좌표, 가로크기, 세로크기)
inline RECT RectMakeCenter(float x, float y, int width, int height)
{
	RECT rc = { static_cast<int>(x) - (width / 2),  static_cast<int>(y) - (height / 2), static_cast<int>(x) + (width / 2),  static_cast<int>(y) + (height / 2) };

	return rc;
}



//================= 사각형 관련 함수 ======================
//          사각형 생성함수(뿌려줄DC, left, top, 가로크기, 세로크기
inline void RectangleMake(HDC hdc, int x, int y, int width, int height)
{
	Rectangle(hdc, x, y, x + width, y + height);
}

inline void RectangleMakeCenter(HDC hdc, int x, int y, int width, int height)
{
	Rectangle(hdc, x - (width / 2), y - (height / 2), x + (width / 2), y + (height / 2));
}

inline void Rectangle(HDC hdc,RECT& rc)
{
	Rectangle(hdc, rc.left, rc.top, rc.right, rc.bottom);
}

//====================== 동 그 라 미 관련 ===============================
//        원 생성함수 (hdc, left, top, 가로크기, 세로크기)
inline void EllipseMake(HDC hdc, int x, int y, int width, int height)
{
	Ellipse(hdc, x, y, x + width, y + height);
}
//        원 생성함수 (hdc, 센터좌표 X, 센터좌표 Y, 가로크기, 세로크기)
inline void EllipseMakeCenter(HDC hdc, int x, int y, int width, int height)
{
	Ellipse(hdc, x - (width / 2), y - (height / 2), x + (width / 2), y + (height / 2));
}

inline void Ellipse(HDC hdc, RECT& rc)
{
	Ellipse(hdc, rc.left, rc.top, rc.right, rc.bottom);
}
