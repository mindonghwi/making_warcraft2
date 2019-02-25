#pragma once

#include "stdafx.h"

namespace Mins {

	//원의 rect을 받아온다 중심X 중심Y 반지름
	inline RECT GetcircleRect(int nPosX, int nPosY, int nRadius) {
		RECT rcTemp;
		rcTemp.left = nPosX - nRadius;
		rcTemp.right = nPosX + nRadius;
		rcTemp.top = nPosY - nRadius;
		rcTemp.bottom = nPosY + nRadius;

		return rcTemp;
	}

	//원과 원충돌을 알려주는 함수 첫원의 x y 반지름 두번쨰 원의 x y 반지름
	inline bool IsCollisionCirtoCir(int nDstPosX, int nDstPosY, int nDstRadius, int nSrcPosX, int nSrcPosY, int nSrcRadius) {
		int nDisX = nDstPosX - nSrcPosX;
		int nDisY = nDstPosY - nSrcPosY;
		int nDisRR = nDstRadius + nSrcRadius;


		if (nDisX * nDisX + nDisY * nDisY <= nDisRR * nDisRR)
		{
			return true;
		}
		return false;
	}

	//원과 점 충돌을 알려주는 함수 첫원의 x, y, 반지름 , 점의 x, 점의 y 
	inline bool IsCollisionCirtoPt(int nDstPosX, int nDstPosY, int nDstRadius, int nSrcX, int nSrcY) {
		int nDisX = nDstPosX - nSrcX;
		int nDisY = nDstPosY - nSrcY;

		if (nDisX * nDisX + nDisY * nDisY <= nDstRadius * nDstRadius)
		{
			return true;
		}
		return false;
	}

	//원과 사각형 충돌 확인 함수	원의 x, 원의 y, 원의 반지름, 사각형의 중심 x, 사각형의 중심 y, 사각형의 가로, 사각형의 세로
	inline bool IsCollisionCirRect(int nCirPosX, int nCirPosY, int nCirRadius, int nRectPosX, int nRectPosY, int nRectWidth, int nRectHeight) {

		//가로세로선에 충돌
		if ((nCirPosX >= nRectPosX - nRectWidth / 2 && nCirPosX <= nRectPosX + nRectWidth / 2) ||
			((nCirPosY >= nRectPosY - nRectHeight / 2 && nCirPosY <= nRectPosY + nRectHeight / 2)))
		{
			//사각형을 원의 반지름 만큼 확장시킨다
			RECT rcCollision;
			rcCollision.bottom = nRectPosY + nRectHeight / 2 + nCirRadius;
			rcCollision.top = nRectPosY - nRectHeight / 2 - nCirRadius;
			rcCollision.left = nRectPosX - nRectWidth / 2 - nCirRadius;
			rcCollision.right = nRectPosX + nRectWidth / 2 + nCirRadius;

			//원의 중심 포인터를 만든다
			POINT ptTemp;
			ptTemp.x = nCirPosX;
			ptTemp.y = nCirPosY;

			//포인터가 확장 사각형에 있으면
			if (PtInRect(&rcCollision, ptTemp))
			{
				return true;
			}
		}
		else {
			//left-top
			if (IsCollisionCirtoPt(nCirPosX, nCirPosY, nCirRadius, nRectPosX - nRectWidth / 2, nRectPosY - nRectHeight / 2))
			{
				return true;
			}
			//right- top
			if (IsCollisionCirtoPt(nCirPosX, nCirPosY, nCirRadius, nRectPosX + nRectWidth / 2, nRectPosY - nRectHeight / 2))
			{
				return true;
			}
			//left - bottom
			if (IsCollisionCirtoPt(nCirPosX, nCirPosY, nCirRadius, nRectPosX - nRectWidth / 2, nRectPosY + nRectHeight / 2))
			{
				return true;
			}
			//right - bottom
			if (IsCollisionCirtoPt(nCirPosX, nCirPosY, nCirRadius, nRectPosX + nRectWidth / 2, nRectPosY + nRectHeight / 2))
			{
				return true;
			}
		}

		return false;
	}

	//원과 사격형 충돌
	inline bool IsCollisionCirRect(int nCirPosX, int nCirPosY, int nCirRadius,LPCRECT rc) {

		//가로세로선에 충돌
		if ((nCirPosX >= rc->left && nCirPosX <= rc->right) ||
			((nCirPosY >= rc->top && nCirPosY <= rc->bottom)))
		{
			//사각형을 원의 반지름 만큼 확장시킨다
			RECT rcCollision;
			rcCollision.bottom = rc->bottom + nCirRadius;
			rcCollision.top = rc->top - nCirRadius;
			rcCollision.left = rc->left - nCirRadius;
			rcCollision.right = rc->right + nCirRadius;

			//원의 중심 포인터를 만든다
			POINT ptTemp;
			ptTemp.x = nCirPosX;
			ptTemp.y = nCirPosY;

			//포인터가 확장 사각형에 있으면
			if (PtInRect(&rcCollision, ptTemp))
			{
				return true;
			}
		}
		else {
			//left-top
			if (IsCollisionCirtoPt(nCirPosX, nCirPosY, nCirRadius, rc->left, rc->top))
			{
				return true;
			}
			//right- top
			if (IsCollisionCirtoPt(nCirPosX, nCirPosY, nCirRadius, rc->right, rc->top))
			{
				return true;
			}
			//left - bottom
			if (IsCollisionCirtoPt(nCirPosX, nCirPosY, nCirRadius, rc->left, rc->bottom))
			{
				return true;
			}
			//right - bottom
			if (IsCollisionCirtoPt(nCirPosX, nCirPosY, nCirRadius, rc->right, rc->bottom))
			{
				return true;
			}
		}

		return false;
	}

	//충돌 사각형 원, 원 밀어내기
	inline void pushCirtoRect(float nCirPosX, float nCirPosY, float nCirRadius,float& fAngle, LPCRECT rc) {

		//가로세로선에 충돌
		if ((nCirPosX >= rc->left && nCirPosX <= rc->right) ||
			((nCirPosY >= rc->top && nCirPosY <= rc->bottom)))
		{
			//사각형을 원의 반지름 만큼 확장시킨다
			RECT rcCollision;
			rcCollision.bottom = rc->bottom + (long)nCirRadius;
			rcCollision.top = rc->top - (long)nCirRadius;
			rcCollision.left = rc->left - (long)nCirRadius;
			rcCollision.right = rc->right + (long)nCirRadius;

			//원의 중심 포인터를 만든다
			POINT ptTemp;
			ptTemp.x = (long)nCirPosX;
			ptTemp.y = (long)nCirPosY;

			//포인터가 확장 사각형에 있으면
			if (PtInRect(&rcCollision, ptTemp))
			{
				if (nCirPosX >= rc->left && nCirPosX <= rc->right)
				{
					fAngle = PI2 - fAngle;
				}
				else if (nCirPosY >= rc->top && nCirPosY <= rc->bottom) {
					fAngle = PI - fAngle;
				}
			}
		}
		else {
			//left-top
			if (IsCollisionCirtoPt((int)nCirPosX, (int)nCirPosY, (int)nCirRadius, rc->left, rc->top))
			{
				fAngle = PI + fAngle;
			}
			//right- top
			if (IsCollisionCirtoPt((int)nCirPosX, (int)nCirPosY, (int)nCirRadius, rc->right, rc->top))
			{
				fAngle = PI + fAngle;
			}
			//left - bottom
			if (IsCollisionCirtoPt((int)nCirPosX, (int)nCirPosY, (int)nCirRadius, rc->left, rc->bottom))
			{
				fAngle = PI + fAngle;
			}
			//right - bottom
			if (IsCollisionCirtoPt((int)nCirPosX, (int)nCirPosY, (int)nCirRadius, rc->right, rc->bottom))
			{
				fAngle = PI + fAngle;
			}
		}
	}


	//사각형 밀어내기(하나는 고정) dst사각형 중점 x, y, 가로, 세로, src사각형(고정) 중점 x, y, 가로, 세로
	inline void pushRect(int & nDstPosX, int & nDstPosY, int nDstWidth, int nDstHeight, const int nSrcPosX, const int nSrcPosY, const int nSrcWidth, const int nSrcHeight) {
		RECT rcDstRect = { nDstPosX - nDstWidth / 2,
							nDstPosY - nDstHeight / 2,
							nDstPosX + nDstWidth / 2,
							nDstPosY + nDstHeight / 2 };

		RECT rcSrcRect = { nSrcPosX - nSrcWidth / 2,
			nSrcPosY - nSrcHeight / 2,
			nSrcPosX + nSrcWidth / 2,
			nSrcPosY + nSrcHeight / 2 };

		RECT rcTemp;

		if (IntersectRect(&rcTemp, &rcDstRect, &rcSrcRect)) {
			
			//충돌한 사각형 면적의 가로길이가 세로길이 보다 클때
			if (rcTemp.right - rcTemp.left > rcTemp.bottom - rcTemp.top)
			{
				//위에서 충돌
				if (rcTemp.top == rcSrcRect.top)
				{
					nDstPosY -= rcTemp.bottom - rcTemp.top;
				}
				//아래에서 충돌
				else if (rcTemp.bottom == rcSrcRect.bottom) {
					nDstPosY += rcTemp.bottom - rcTemp.top;
				}
			}
			else if (rcTemp.right - rcTemp.left > rcTemp.bottom - rcTemp.top)
			{
				//좌측에서 충돌
				if (rcTemp.left == rcSrcRect.left)
				{
					nDstPosX -= rcTemp.right - rcTemp.left;
				}
				//우측에서 충돌
				else if (rcTemp.right == rcSrcRect.right) {
					nDstPosX += rcTemp.right - rcTemp.left;
				}
			}
			else
			{
				//정확한 모서리 충돌
				//좌상충돌
				if (rcTemp.top == rcSrcRect.top && rcTemp.left == rcSrcRect.left)
				{
					nDstPosY -= rcTemp.bottom - rcTemp.top;
					nDstPosX -= rcTemp.right - rcTemp.left;
				}//우상충돌
				else if (rcTemp.top == rcSrcRect.top && rcTemp.right == rcSrcRect.right) {
					nDstPosX += rcTemp.right - rcTemp.left;
					nDstPosY -= rcTemp.bottom - rcTemp.top;
				}//좌하충돌
				else if (rcTemp.bottom == rcSrcRect.bottom && rcTemp.left == rcSrcRect.left) {
					nDstPosY += rcTemp.bottom - rcTemp.top;
					nDstPosX -= rcTemp.right - rcTemp.left;
				}//우하충돌
				else if (rcTemp.bottom == rcSrcRect.bottom && rcTemp.right == rcSrcRect.right) {
					nDstPosY += rcTemp.bottom - rcTemp.top;
					nDstPosX += rcTemp.right - rcTemp.left;
				}
			}
		}

	}

	//사각형 밀어내기(하나는 고정) dst사각형 중점 x, y, 가로, 세로, src사각형(고정) 중점 x, y, 가로, 세로
	inline void pushRects(float & nDstPosX, float & nDstPosY, int nDstWidth, int nDstHeight,  int nSrcPosX,  int nSrcPosY,  int nSrcWidth,  int nSrcHeight) {
		RECT rcDstRect = { (int)nDstPosX - nDstWidth / 2,
			(int)nDstPosY - nDstHeight / 2,
			(int)nDstPosX + nDstWidth / 2,
			(int)nDstPosY + nDstHeight / 2 };

		RECT rcSrcRect = { nSrcPosX - nSrcWidth / 2,
			nSrcPosY - nSrcHeight / 2,
			nSrcPosX + nSrcWidth / 2,
			nSrcPosY + nSrcHeight / 2 };

		RECT rcTemp;

		if (IntersectRect(&rcTemp, &rcDstRect, &rcSrcRect)) {

			//충돌한 사각형 면적의 가로길이가 세로길이 보다 클때
			if (rcTemp.right - rcTemp.left >= rcTemp.bottom - rcTemp.top)
			{
				//위에서 충돌
				if (rcTemp.top == rcSrcRect.top)
				{
					nDstPosY -= rcTemp.bottom - rcTemp.top;
				}
				//아래에서 충돌
				else if (rcTemp.bottom == rcSrcRect.bottom) {
					nDstPosY += rcTemp.bottom - rcTemp.top;
				}
			}
			else if (rcTemp.right - rcTemp.left > rcTemp.bottom - rcTemp.top)
			{
				//좌측에서 충돌
				if (rcTemp.left == rcSrcRect.left)
				{
					nDstPosX -= rcTemp.right - rcTemp.left;
				}
				//우측에서 충돌
				else if (rcTemp.right == rcSrcRect.right) {
					nDstPosX += rcTemp.right - rcTemp.left;
				}
			}
			else
			{
				//정확한 모서리 충돌
				//좌상충돌
				if (rcTemp.top == rcSrcRect.top && rcTemp.left == rcSrcRect.left)
				{
					nDstPosY -= rcTemp.bottom - rcTemp.top;
					nDstPosX -= rcTemp.right - rcTemp.left;
				}//우상충돌
				else if (rcTemp.top == rcSrcRect.top && rcTemp.right == rcSrcRect.right) {
					nDstPosX += rcTemp.right - rcTemp.left;
					nDstPosY -= rcTemp.bottom - rcTemp.top;
				}//좌하충돌
				else if (rcTemp.bottom == rcSrcRect.bottom && rcTemp.left == rcSrcRect.left) {
					nDstPosY += rcTemp.bottom - rcTemp.top;
					nDstPosX -= rcTemp.right - rcTemp.left;
				}//우하충돌
				else if (rcTemp.bottom == rcSrcRect.bottom && rcTemp.right == rcSrcRect.right) {
					nDstPosY += rcTemp.bottom - rcTemp.top;
					nDstPosX += rcTemp.right - rcTemp.left;
				}
			}
		}

	}

	//사각형 밀어내기(하나는 고정) dst사각형 중점 x, y, 가로, 세로, src사각형(고정) 중점 x, y, 가로, 세로
	inline void pushRect(LPRECT pDstRect, const LPRECT pSrcRect) {
		
		RECT rcTemp;

		if (IntersectRect(&rcTemp, pDstRect, pSrcRect)) {

			//충돌한 사각형 면적의 가로길이가 세로길이 보다 클때
			if (rcTemp.right - rcTemp.left > rcTemp.bottom - rcTemp.top)
			{
				//위에서 충돌
				if (rcTemp.top == pSrcRect->top)
				{
					pDstRect->top -= rcTemp.bottom - rcTemp.top;
					pDstRect->bottom -= rcTemp.bottom - rcTemp.top;

				}
				//아래에서 충돌
				else if (rcTemp.bottom == pSrcRect->bottom) {
					pDstRect->top += rcTemp.bottom - rcTemp.top;
					pDstRect->bottom += rcTemp.bottom - rcTemp.top;
				}
			}
			else if (rcTemp.right - rcTemp.left > rcTemp.bottom - rcTemp.top)
			{
				//좌측에서 충돌
				if (rcTemp.left == pSrcRect->left)
				{
					pDstRect->left -= rcTemp.right - rcTemp.left;
					pDstRect->right -= rcTemp.right - rcTemp.left;
				}
				//우측에서 충돌
				else if (rcTemp.right == pSrcRect->right) {
					pDstRect->left += rcTemp.right - rcTemp.left;
					pDstRect->right += rcTemp.right - rcTemp.left;
				}
			}
			else
			{
				//정확한 모서리 충돌
				//좌상충돌
				if (rcTemp.top == pSrcRect->top && rcTemp.left == pSrcRect->left)
				{
					pDstRect->top -= rcTemp.bottom - rcTemp.top;
					pDstRect->bottom -= rcTemp.bottom - rcTemp.top;
					pDstRect->left -= rcTemp.right - rcTemp.left;
					pDstRect->right -= rcTemp.right - rcTemp.left;
				}//우상충돌
				else if (rcTemp.top == pSrcRect->top && rcTemp.right == pSrcRect->right) {
					pDstRect->left += rcTemp.right - rcTemp.left;
					pDstRect->right += rcTemp.right - rcTemp.left;
					pDstRect->top -= rcTemp.bottom - rcTemp.top;
					pDstRect->bottom -= rcTemp.bottom - rcTemp.top;
				}//좌하충돌
				else if (rcTemp.bottom == pSrcRect->bottom && rcTemp.left == pSrcRect->left) {
					pDstRect->top += rcTemp.bottom - rcTemp.top;
					pDstRect->bottom += rcTemp.bottom - rcTemp.top;
					pDstRect->left -= rcTemp.right - rcTemp.left;
					pDstRect->right -= rcTemp.right - rcTemp.left;
				}//우하충돌
				else if (rcTemp.bottom == pSrcRect->bottom && rcTemp.right == pSrcRect->right) {
					pDstRect->top += rcTemp.bottom - rcTemp.top;
					pDstRect->bottom += rcTemp.bottom - rcTemp.top;
					pDstRect->left += rcTemp.right - rcTemp.left;
					pDstRect->right += rcTemp.right - rcTemp.left;
				}
			}
		}
	}

	inline float presentPowerY(float fAngle, float fSpeed) {
		return -sinf(fAngle) * fSpeed;
	}

	inline float presentPowerX(float fAngle, float fSpeed) {
		return cosf(fAngle) * fSpeed;
	}


	inline void FYshuffle(int* pDstArray, int nLength) {
		
		for (int i = nLength - 1; i > 0; i--)
		{
			int nTmpIndex = randomFunction::getSingleton()->getInt(i);
			int nTmp = pDstArray[i];
			pDstArray[i] = pDstArray[nTmpIndex];
			pDstArray[nTmpIndex] = nTmp;
		}

	}

	//360도에서 10도씩 나눌때 가장 근접한 각도를 알려준다. 
	// PI2 / 36.0f * 반환값   
	inline int getNearAnglePI2(float fAngle) {
		int nResult(0);

		while (PI2 / 36.0f * static_cast<float>(nResult) < fAngle)
		{
			nResult++;
		}

		float fDst = PI2 / 36.0f * static_cast<float>(nResult);
		
		if (fabsf(fDst - fAngle) <= FLT_EPSILON || nResult == 0)
		{
			return nResult;
		}
		else {
			float fSrc = PI2 / 36.0f * static_cast<float>(nResult - 1);
			
			if (fabsf(fDst - fAngle) < fabsf(fSrc - fAngle))
			{
				return nResult;
			}
			else
			{
				return nResult - 1;
			}
		}

	}

	//360도에서 10도씩 나눌때 가장 근접한 각도를 PI단위로 변환해서 알려준다 
	// PI2 / 36.0f * 반환값 반환값이 18보다 클 경우 -18해서 준다  
	inline int getNearAnglePI(float fAngle) {
		int nResult(0);

		while (PI2 / 36.0f * static_cast<float>(nResult) < fAngle)
		{
			nResult++;
		}

		float fDst = PI2 / 36.0f * static_cast<float>(nResult);

		if (fabsf(fDst - fAngle) <= FLT_EPSILON || nResult == 0)
		{
			if (nResult >= 18)
			{
				nResult -= 18;
			}
			return nResult;
		}
		else {
			float fSrc = PI2 / 36.0f * static_cast<float>(nResult - 1);

			if (fabsf(fDst - fAngle) < fabsf(fSrc - fAngle))
			{
				if (nResult >= 18)
				{
					nResult -= 18;
				}
			}
			else
			{
				if (nResult >= 19)
				{
					nResult -= 19;
				}
			}
			return nResult;
		}
	}


	inline int getNearAngleSBullet(float fAngle)
	{
		int nResult(0);

		while (fAngle > PI2)
		{
			fAngle = fAngle - PI2;
		}



		if (fAngle >= PI)
		{
			fAngle -= PI;
		}

		while (PI / 18.0f * static_cast<float>(nResult) < fAngle)
		{
			nResult++;
		}

		float fDst = PI / 18.0f * static_cast<float>(nResult);

		if (fabsf(fDst - fAngle) <= FLT_EPSILON)
		{
			if (nResult < 0)
			{
				nResult = 0;
			}
			if (nResult >= 18)
			{
				nResult = 0;
			}
			return nResult;
		}
		else {
			float fSrc = PI / 18.0f * static_cast<float>(nResult - 1);

			if (fabsf(fDst - fAngle) < fabsf(fSrc - fAngle))
			{
				if (nResult >= 18)
				{
					nResult = 0;
				}
				if (nResult < 0)
				{
					nResult = 0;
				}

				return nResult;
			}
			else
			{
				if (nResult >= 18)
				{
					nResult = 0;
				}
				if (nResult < 0)
				{
					nResult = 0;
				}
				return nResult;
			}

			if (nResult < 0)
			{
				nResult = 0;
			}
			return nResult;
		}

	}



	inline float getDoubleDistance(float fDstX, float fDstY, float fSrcX, float fSrcY) {
		return (fDstX - fSrcX) * (fDstX - fSrcX) + (fDstY - fSrcY) * (fDstY - fSrcY);
	}


	inline DWORD getMazenta() {
		DWORD dwColor;
		dwColor = ((COLORREF)(((BYTE)(0xff) | ((WORD)((BYTE)(0x00)) << 8)) | (((DWORD)(BYTE)(0xff)) << 16)));
		return dwColor;
	}


	inline float	getDoubleDis(float fDstX, float fDstY, float fSrcX, float fSrcY)
	{
		return (fDstX - fSrcX)*(fDstX - fSrcX) + (fDstY - fSrcY)*(fDstY - fSrcY);
	}


	//사각형 충돌 (사각형1 중심 x , 중심 y, 가로, 세로, 사각형2 중심x, 중심y, 가로, 세로)
	inline bool	isCollisionRectRect(int nDstX, int nDstY, int nDstWidth, int nDstHeight, int nSrcX, int nSrcY, int nSrcWidth, int nSrcHeight) {

		RECT rcDst = RectMakeCenter(nDstX, nDstY, nDstWidth, nDstHeight);
		RECT rcSrc = RectMakeCenter(nSrcX, nSrcY, nSrcWidth, nSrcHeight);

		RECT rcTmp;
		if (IntersectRect(&rcTmp,&rcDst,&rcSrc))
		{
			return true;
		}
		else {
			return false;
		}
	}


}

