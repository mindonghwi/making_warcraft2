#include "stdafx.h"
#include "aStar.h"
#include "player.h"
#include "unit.h"
#include "unitMGr.h"
#include "buildMgr.h"
#include "build.h"

ASTAR::TILENODE * ASTAR::getNode(int nIndex)
{
	list<TILENODE*>::iterator iter = _listMaximumPath.begin();
	for (int i = 0; i < nIndex; i++)
	{
		iter++;
	}

	return *iter;
}

void ASTAR::setLinkUnitMgr(PLAYER * _pPlayer)
{
	_pUnitMgr = _pPlayer->getUnitMgr();
	_pBuildMgr = _pPlayer->getBuildMgr();
}



void ASTAR::initMap()
{
	for (int j = 0; j < _nTileSizeY; j++)
	{
		for (int i = 0; i < _nTileSizeX; i++)
		{
			_vvTile[j][i]->nIndexX = i;
			_vvTile[j][i]->nIndexY = j;
			_vvTile[j][i]->nPathCurrentToEnd = 0;
			_vvTile[j][i]->nPathStartToCurrent = 0;
			_vvTile[j][i]->nPathToatalCost = 0;
			_vvTile[j][i]->parrentNode = nullptr;
		}
	}
}



ASTAR::ASTAR()
{
}

ASTAR::~ASTAR()
{
}

void ASTAR::init(int nSearchLength, MAP * pMap)
{
	_nSearchLength = nSearchLength;

	//이상한것 넣는 xx들을 방지하기 위한
	if (_nSearchLength < 7)
	{
		_nSearchLength = 4;
	}
	else
	{
		_nSearchLength = 8;
	}


	_pMap = pMap;

	_vvTile.resize(_pMap->getMapCountY());

	for (int j = 0; j < _vvTile.size(); j++)
	{
		for (int i = 0; i < _pMap->getMapCountX(); i++)
		{
			_vvTile[j].push_back(new TILENODE);
			_vvTile[j][i]->nIndexX = i;
			_vvTile[j][i]->nIndexY = j;
			_vvTile[j][i]->nPathCurrentToEnd = 0;
			_vvTile[j][i]->nPathStartToCurrent = 0;
			_vvTile[j][i]->nPathToatalCost = 0;
			_vvTile[j][i]->parrentNode = nullptr;
		}
	}

	_nTileSizeX = _pMap->getMapCountX();
	_nTileSizeY = _pMap->getMapCountY();
}



void ASTAR::startFinder(int nStartIndexX, int nStartIndexY, int nEndIndexX, int nEndIndexY, MOVEHEIGHT eMoveHeight)
{
	//시작점을 만든다.
	//부모노드는 없다
	//시작 중심점을 잡는다.
	//코스트를 계산한다.
	_nStartIndexX = nStartIndexX;
	_nStartIndexY = nStartIndexY;
	_nEndIndexX = nEndIndexX;
	_nEndIndexY = nEndIndexY;

	_eMoveHeight = eMoveHeight;

	_listOpendNode.clear();
	_listClosedyPath.clear();
	_listMaximumPath.clear();
	initMap();
	//시작 노드 만들기
	//TILENODE* pNode = new TILENODE();
	//pNode->nIndexX = _nStartIndexX;
	//pNode->nIndexY = _nStartIndexY;
	//pNode->nPathCurrentToEnd = 0;
	//pNode->nPathStartToCurrent = 0;
	//pNode->nPathToatalCost = 0;
	//pNode->parrentNode = nullptr;

	//열린 좌표에 넣는데 우선순위를 주자
	_listOpendNode.push_back(_vvTile[_nStartIndexY][_nStartIndexX]);

}

void ASTAR::startFinder(float fStartPosX, float fStartPosY, float fEndPosX, float fEndPosY, MOVEHEIGHT eMoveHeight)
{
	//시작점을 만든다.
	//부모노드는 없다
	//시작 중심점을 잡는다.
	//코스트를 계산한다.
	_nStartIndexX = static_cast<int>(fStartPosX) / TILESIZE;
	_nStartIndexY = static_cast<int>(fStartPosY) / TILESIZE;
	_nEndIndexX = static_cast<int>(fEndPosX) / TILESIZE;
	_nEndIndexY = static_cast<int>(fEndPosY) / TILESIZE;

	_eMoveHeight = eMoveHeight;

	_listOpendNode.clear();
	_listClosedyPath.clear();
	_listMaximumPath.clear();
	initMap();
	//시작 노드 만들기
	//TILENODE* pNode = new TILENODE();
	//pNode->nIndexX = _nStartIndexX;
	//pNode->nIndexY = _nStartIndexY;
	//pNode->nPathCurrentToEnd = 0;
	//pNode->nPathStartToCurrent = 0;
	//pNode->nPathToatalCost = 0;
	//pNode->parrentNode = nullptr;
	if (_eMoveHeight == MOVEHEIGHT::WATER)
	{
		initMap();

	}

	//만약 그 위치에 무언가 못가게 하는 것이 있으면
	int nCount = 0;
	int nIndex = 0;
	int nGo = 1;
	int nIndexCount = 0;
	bool bIsOnObject = true;

	//빌드도 아니고 논도 아니면 돌려

	//while (//(_eMoveHeight == MOVEHEIGHT::GROUND && _pMap->getTile(_nEndIndexX, _nEndIndexY)->getTerrian() == TILE::E_TERRIAN::WATER)
	//	//|| (_eMoveHeight == MOVEHEIGHT::GROUND && _pMap->getTile(_nEndIndexX, _nEndIndexY)->getTerrian() == TILE::E_TERRIAN::DIRT_WATER)
	//	//|| (_eMoveHeight == MOVEHEIGHT::GROUND && _pMap->getTile(_nEndIndexX, _nEndIndexY)->getTerrian() == TILE::E_TERRIAN::ROCK)
	//	nCount< 25&&((_eMoveHeight == MOVEHEIGHT::GROUND && _pMap->getTile(_nEndIndexX, _nEndIndexY)->getObject() != TILE::E_OBJECT::E_NONE)&&
	//	(_eMoveHeight == MOVEHEIGHT::GROUND && _pMap->getTile(_nEndIndexX, _nEndIndexY)->getObject() != TILE::E_OBJECT::E_BUILDING)
	//	|| bIsOnObject))
	//{
	//	bIsOnObject = false;
	//
	//
	//	RECT rcTmp;
	//	for (int i = 0; i < _pUnitMgr->getUnitCount(); i++)
	//	{
	//		if (_pUnitMgr->getUnit(i)->getPosX() - fStartPosX < FLT_EPSILON
	//			&& _pUnitMgr->getUnit(i)->getPosY() - fStartPosY < FLT_EPSILON)
	//		{
	//		}
	//		else
	//		{
	//			RECT rc = _pMap->getTile(_nEndIndexX, _nEndIndexY)->getRectTile();
	//			RECT rc2 = * _pUnitMgr->getUnit(i)->getCollisionRect();
	//			rc2.left += 10;
	//			rc2.top += 10;
	//			rc2.right -= 10;
	//			rc2.bottom -= 10;
	//
	//			if (IntersectRect(&rcTmp, &rc, &rc2))
	//			{
	//				bIsOnObject = true;
	//				break;
	//			}
	//			else
	//			{
	//				if (!_pUnitMgr->getUnit(i)->getIsMovePointEmpty())
	//				{
	//					if (_nEndIndexX == _pUnitMgr->getUnit(i)->getMoveToPointEndX() && _pUnitMgr->getUnit(i)->getMoveToPointEndY() == _nEndIndexY)
	//					{
	//						bIsOnObject = true;
	//						break;
	//					}
	//				}
	//			}
	//		}
	//	}
	//
	//	if (!bIsOnObject)
	//	{
	//		//com
	//
	//	}
	//
	//
	//	if (_eMoveHeight == MOVEHEIGHT::GROUND && _pMap->getTile(_nEndIndexX, _nEndIndexY)->getObject() != TILE::E_OBJECT::E_NONE)
	//	{
	//		bIsOnObject = true;
	//	}
	//
	//	if (bIsOnObject)
	//	{
	//		_nEndIndexX += _pUnitMgr->getIntervalX(nCount);
	//		_nEndIndexY += _pUnitMgr->getIntervalY(nCount);
	//	}
	//	nCount++;
	//}


	int nAddSubChangeCount = 2;
	int nAddSubChangeIndex = 0;
	int nInterval = -1;
	//x y xx yy xxx yyy xxxx yyyy
	int nMapChangeCount = 1;
	int nMapChangeIndex = 0;

	int nIntervalsX = 0;
	int nIntervalsY = 0;
	nIntervalsX = nInterval;




	while (((_eMoveHeight == MOVEHEIGHT::GROUND && _pMap->getTile(_nEndIndexX, _nEndIndexY)->getObject() != TILE::E_OBJECT::E_NONE)&&
		(_eMoveHeight == MOVEHEIGHT::GROUND && _pMap->getTile(_nEndIndexX, _nEndIndexY)->getObject() != TILE::E_OBJECT::E_BUILDING)
		|| bIsOnObject) )//&& _nEndIndexX == 0 && _nEndIndexX == TILECOUNTX-1 && _nEndIndexY == 0 && _nEndIndexY == TILECOUNTY - 1)
	{
		bIsOnObject = false;
	

		RECT rcTmp;
		for (int i = 0; i < _pUnitMgr->getUnitCount(); i++)
		{
			if (_pUnitMgr->getUnit(i)->getPosX() - fStartPosX < FLT_EPSILON
				&& _pUnitMgr->getUnit(i)->getPosY() - fStartPosY < FLT_EPSILON)
			{
			}
			else
			{
				RECT rc = _pMap->getTile(_nEndIndexX, _nEndIndexY)->getRectTile();
				RECT rc2 = * _pUnitMgr->getUnit(i)->getCollisionRect();
				rc2.left += 10;
				rc2.top += 10;
				rc2.right -= 10;
				rc2.bottom -= 10;
	
				if (IntersectRect(&rcTmp, &rc, &rc2))
				{
					bIsOnObject = true;
					break;
				}
				else
				{
					if (!_pUnitMgr->getUnit(i)->getIsMovePointEmpty())
					{
						if (_nEndIndexX == _pUnitMgr->getUnit(i)->getMoveToPointEndX() && _pUnitMgr->getUnit(i)->getMoveToPointEndY() == _nEndIndexY)
						{
							bIsOnObject = true;
							break;
						}
					}
				}
			}
		}
	
		if (!bIsOnObject)
		{
			//com
	
		}
	
	
		if (_eMoveHeight == MOVEHEIGHT::GROUND && _pMap->getTile(_nEndIndexX, _nEndIndexY)->getObject() != TILE::E_OBJECT::E_NONE)
		{
			bIsOnObject = true;
		}
	
		if (bIsOnObject)
		{
			_nEndIndexX += nIntervalsX;
			_nEndIndexY += nIntervalsY;

			nAddSubChangeIndex++;

			nMapChangeIndex++;

			if (nMapChangeIndex == nMapChangeCount)
			{
				//좌표를 더해주는게 변한다
				int nTmp = nIntervalsX;
				nIntervalsX = nIntervalsY;
				nIntervalsY = nTmp;

				nMapChangeIndex = 0;
			}

			if (nAddSubChangeCount == nAddSubChangeIndex)
			{
				nAddSubChangeCount += 2;
				nAddSubChangeIndex = 0;

				nInterval *= -1;

				if (nIntervalsX == 0)
				{
					nIntervalsY *= -1;
				}
				else
				{
					nIntervalsX *= -1;
				}
				nMapChangeCount++;

			}

		}
		nCount++;
	}



	//열린 좌표에 넣는데 우선순위를 주자
	_listOpendNode.push_back(_vvTile[_nStartIndexY][_nStartIndexX]);




}

void ASTAR::startFinderArray(float fStartPosX, float fStartPosY, float fEndPosX, float fEndPosY, MOVEHEIGHT eMoveHeight, int* nIndex)
{
	_nStartIndexX = static_cast<int>(fStartPosX) / TILESIZE;
	_nStartIndexY = static_cast<int>(fStartPosY) / TILESIZE;
	_nEndIndexX = static_cast<int>(fEndPosX) / TILESIZE;
	_nEndIndexY = static_cast<int>(fEndPosY) / TILESIZE;


	_eMoveHeight = eMoveHeight;

	_listOpendNode.clear();
	_listClosedyPath.clear();
	_listMaximumPath.clear();
	initMap();
	//시작 노드 만들기
	//TILENODE* pNode = new TILENODE();
	//pNode->nIndexX = _nStartIndexX;
	//pNode->nIndexY = _nStartIndexY;
	//pNode->nPathCurrentToEnd = 0;
	//pNode->nPathStartToCurrent = 0;
	//pNode->nPathToatalCost = 0;
	//pNode->parrentNode = nullptr;

	//열린 좌표에 넣는데 우선순위를 주자

	_nEndIndexX += _pUnitMgr->getIntervalX(*nIndex);
	_nEndIndexY += _pUnitMgr->getIntervalY(*nIndex);
	while ((_nEndIndexX < 1 || _nEndIndexX < 1 || _nEndIndexX >= _nTileSizeX - 1 || _nEndIndexX >= _nTileSizeY - 1 ||
		(_eMoveHeight == MOVEHEIGHT::GROUND && _pMap->getTile(_nEndIndexX, _nEndIndexY)->getTerrian() == TILE::E_TERRIAN::DIRT_WATER) ||
		(_eMoveHeight == MOVEHEIGHT::GROUND && _pMap->getTile(_nEndIndexX, _nEndIndexY)->getTerrian() == TILE::E_TERRIAN::WATER) //||
		//(_eMoveHeight == MOVEHEIGHT::GROUND && _pMap->getTile(_nEndIndexX, _nEndIndexY)->getObject() != TILE::E_OBJECT::E_NONE)
		))
	{
		if (*nIndex >= 25)
		{
			break;
		}
		else
		{
			_nEndIndexX -= _pUnitMgr->getIntervalX(*nIndex);
			_nEndIndexY -= _pUnitMgr->getIntervalY(*nIndex);
			(*nIndex)++;
			_nEndIndexX += _pUnitMgr->getIntervalX(*nIndex);
			_nEndIndexY += _pUnitMgr->getIntervalY(*nIndex);
		}

	}


	_listOpendNode.push_back(_vvTile[_nStartIndexY][_nStartIndexX]);

}



void ASTAR::pathFinder()
{
	//8점의 좌표를 탐색
	//열린좌표에 넣는데
	//열린 좌표에 넣는데 우선순위를 주자
	//닫힌 좌표에 있으면 넣지 않는다.
	//열린좌표에 같은 값이 있으면 코스트를 비교하여 작은 애한테 부모와 코스트를 바꾸어서 대입
	//앤드면 이제 부모들을 쭉 불러와서 길을 만든다.. 이건 메이크 패스
	//앤드가 아니면 다시 재귀적으로 돌린다.
	if (_listOpendNode.empty())
	{
		list<TILENODE*>::iterator iter = _listClosedyPath.begin();
		list<TILENODE*>::iterator end = _listClosedyPath.end();
		TILENODE* pNode;
		pNode = *iter;
		//가장 가까운 노드를 탐색한다.
		while (iter != end)
		{
			int nDst = abs(pNode->nIndexX - _nEndIndexX) + abs(pNode->nIndexY - _nEndIndexY);
			int nSrc = abs((*iter)->nIndexX - _nEndIndexX) + abs((*iter)->nIndexY - _nEndIndexY);
			if (nDst > nSrc)
			{
				pNode = *iter;
			}
			iter++;
		}


		//가장 가까운 노드에서 길을 만든다
		while (pNode != nullptr) {
			_listMaximumPath.push_front(pNode);

			pNode = pNode->parrentNode;
		}

		return;
	}


	TILENODE* pNode = _listOpendNode.front();
	_listClosedyPath.push_back(pNode);
	_listOpendNode.pop_front();

	//8점 좌표탐색
	for (int i = 0; i < _nSearchLength; i++)
	{
		int nIntervalPosX = pNode->nIndexX + _arInterval[i][static_cast<int>(POS::POSX)];
		int nIntervalPosY = pNode->nIndexY + _arInterval[i][static_cast<int>(POS::POSY)];

		if (nIntervalPosX < 1) continue;
		if (nIntervalPosY < 1) continue;
		if (nIntervalPosX >= _nTileSizeX - 1) continue;
		if (nIntervalPosY >= _nTileSizeY - 1) continue;
		//나중가서는 터리안이나 오브젝트로 처리
		//if (_pMap->getTile(nIntervalPosX, nIntervalPosY)->getIsWall()) continue;
		if (_eMoveHeight == MOVEHEIGHT::GROUND && _pMap->getTile(nIntervalPosX, nIntervalPosY)->getTerrian() != TILE::E_TERRIAN::GROUND
			&& _pMap->getTile(nIntervalPosX, nIntervalPosY)->getTerrian() != TILE::E_TERRIAN::DIRT) continue;

		if (_eMoveHeight == MOVEHEIGHT::GROUND && _pMap->getTile(nIntervalPosX, nIntervalPosY)->getTerrian() == TILE::E_TERRIAN::DIRT)
		{
			int nCount = 0;
			for (int j = 0; j < 4; j++)
			{
				int nTmpEdgePosX = nIntervalPosX + _arInterval[j][static_cast<int>(POS::POSX)];
				int nTmpEdgePosY = nIntervalPosY + _arInterval[j][static_cast<int>(POS::POSY)];

				if (_pMap->getTile(nTmpEdgePosX, nTmpEdgePosY)->getTerrian() == TILE::E_TERRIAN::WATER
					|| _pMap->getTile(nTmpEdgePosX, nTmpEdgePosY)->getTerrian() == TILE::E_TERRIAN::ROCK)
				{
					nCount++;
				}

			}
			if (nCount >= 2)
			{
				continue;
			}
		}


		if (_eMoveHeight == MOVEHEIGHT::WATER && _pMap->getTile(nIntervalPosX, nIntervalPosY)->getTerrian() != TILE::E_TERRIAN::WATER) continue;
		if (_eMoveHeight == MOVEHEIGHT::GROUND && _pMap->getTile(nIntervalPosX, nIntervalPosY)->getObject() != TILE::E_OBJECT::E_NONE && _pMap->getTile(nIntervalPosX, nIntervalPosY)->getObject() != TILE::E_OBJECT::E_UNIT)continue;

		//유닛
		//bool bIsObject = false;
		//for (int i = 0; i < _pUnitMgr->getUnitCount(); i++)
		//{
		//	RECT rcTmp;

		//	RECT rc = _pMap->getTile(nIntervalPosX, nIntervalPosY)->getRectTile();
		//	RECT rc2 = * _pUnitMgr->getUnit(i)->getCollisionRect();
		//	rc2.left += 5;
		//	rc2.top += 5;
		//	rc2.right -= 5;
		//	rc2.bottom -= 5;

		//	if (IntersectRect(&rcTmp, &rc, &rc2))
		//	{
		//		//if (!_pUnitMgr->getUnit(i)->getIsMoveAstar())
		//		{
		//			bIsObject = true;
		//			break;
		//		}
		//	}
		//}

		//if (bIsObject) continue;

		////건물
		//bIsObject = false;
		//for (int i = 0; i < _pBuildMgr->getBuildCount(); i++)
		//{
		//	RECT rcTmp;

		//	RECT rc = _pMap->getTile(nIntervalPosX, nIntervalPosY)->getRectTile();
		//	RECT rc2 = * _pUnitMgr->getUnit(i)->getCollisionRect();
		//	rc2.left += 5;
		//	rc2.top += 5;
		//	rc2.right -= 5;
		//	rc2.bottom -= 5;

		//	if (IntersectRect(&rcTmp, &rc, &rc2))
		//	{
		//		//if (!_pUnitMgr->getUnit(i)->getIsMoveAstar())
		//		{
		//			bIsObject = true;
		//			break;
		//		}
		//	}
		//}
		//if (bIsObject) continue;



		//유닛들이 통과하면 안된다.
		//유닛이 만들어지면 플레이어의 유닛과 COM의 유닛들과 통과를 막는다.
		//if (_pUnitMgr->)
		//{
		//
		//}

		bool bIsSearch = false;
		list<TILENODE*>::iterator iter = _listOpendNode.begin();
		//list<TILENODE*>::iterator end = ;
		//////////open에 있으면 
		while (iter != _listOpendNode.end())
		{
			if ((*iter)->nIndexX == nIntervalPosX && (*iter)->nIndexY == nIntervalPosY)
			{
				if ((*iter)->nPathStartToCurrent > pNode->nPathStartToCurrent + _arHuristic[i])
				{
					//바꾸고 다시 정렬해야한다.
					_vvTile[nIntervalPosY][nIntervalPosX]->nIndexX = nIntervalPosX;
					_vvTile[nIntervalPosY][nIntervalPosX]->nIndexY = nIntervalPosY;
					_vvTile[nIntervalPosY][nIntervalPosX]->nPathStartToCurrent = pNode->nPathStartToCurrent + _arHuristic[i];
					_vvTile[nIntervalPosY][nIntervalPosX]->nPathCurrentToEnd = abs(nIntervalPosX - _nEndIndexX) + abs(nIntervalPosY - _nEndIndexY);
					_vvTile[nIntervalPosY][nIntervalPosX]->nPathCurrentToEnd *= _arHuristic[i];
					_vvTile[nIntervalPosY][nIntervalPosX]->nPathToatalCost = _vvTile[nIntervalPosY][nIntervalPosX]->nPathStartToCurrent + _vvTile[nIntervalPosY][nIntervalPosX]->nPathCurrentToEnd;
					_vvTile[nIntervalPosY][nIntervalPosX]->parrentNode = pNode;


					iter = _listOpendNode.erase(iter);

					while (iter != _listOpendNode.end() && (*iter)->nPathToatalCost < _vvTile[nIntervalPosY][nIntervalPosX]->nPathToatalCost) {
						iter++;
					}
					_listOpendNode.insert(iter, _vvTile[nIntervalPosY][nIntervalPosX]);
				}

				bIsSearch = true;
				break;
			}
			iter++;
		}
		if (bIsSearch) continue;
		bIsSearch = false;

		//클로즈에 있으면 넘겨야한다.
		iter = _listClosedyPath.begin();
		//end = _listClosedyPath.end();
		while (iter != _listClosedyPath.end())
		{
			if ((*iter)->nIndexX == nIntervalPosX && (*iter)->nIndexY == nIntervalPosY) {
				bIsSearch = true;
				break;
			}
			iter++;
		}
		if (bIsSearch) continue;

		_vvTile[nIntervalPosY][nIntervalPosX]->nIndexX = nIntervalPosX;
		_vvTile[nIntervalPosY][nIntervalPosX]->nIndexY = nIntervalPosY;
		_vvTile[nIntervalPosY][nIntervalPosX]->nPathStartToCurrent = pNode->nPathStartToCurrent + _arHuristic[i];
		_vvTile[nIntervalPosY][nIntervalPosX]->nPathCurrentToEnd = abs(nIntervalPosX - _nEndIndexX) + abs(nIntervalPosY - _nEndIndexY);
		_vvTile[nIntervalPosY][nIntervalPosX]->nPathCurrentToEnd *= _arHuristic[i];
		_vvTile[nIntervalPosY][nIntervalPosX]->nPathToatalCost = _vvTile[nIntervalPosY][nIntervalPosX]->nPathStartToCurrent + _vvTile[nIntervalPosY][nIntervalPosX]->nPathCurrentToEnd;
		_vvTile[nIntervalPosY][nIntervalPosX]->parrentNode = pNode;

		if (nIntervalPosX == _nEndIndexX && nIntervalPosY == _nEndIndexY)
		{
			//찾았다
			_listMaximumPath.push_front(_vvTile[nIntervalPosY][nIntervalPosX]);

			TILENODE* pTmp = _vvTile[nIntervalPosY][nIntervalPosX]->parrentNode;
			while (pTmp != nullptr) {
				_listMaximumPath.push_front(pTmp);

				pTmp = pTmp->parrentNode;
			}
			//탈출
			return;
		}
		else
		{
			iter = _listOpendNode.begin();
			while (iter != _listOpendNode.end() && (*iter)->nPathToatalCost < _vvTile[nIntervalPosY][nIntervalPosX]->nPathToatalCost) {
				iter++;
			}
			_listOpendNode.insert(iter, _vvTile[nIntervalPosY][nIntervalPosX]);
		}

	}

	if (_listClosedyPath.size() > 300)
	{

		list<TILENODE*>::iterator iter = _listClosedyPath.begin();
		list<TILENODE*>::iterator end = _listClosedyPath.end();
		TILENODE* pNode;
		pNode = *iter;
		//가장 가까운 노드를 탐색한다.
		while (iter != end)
		{
			int nDst = abs(pNode->nIndexX - _nEndIndexX) + abs(pNode->nIndexY - _nEndIndexY);
			int nSrc = abs((*iter)->nIndexX - _nEndIndexX) + abs((*iter)->nIndexY - _nEndIndexY);
			if (nDst > nSrc)
			{
				pNode = *iter;
			}
			iter++;
		}

		//가장 가까운 노드에서 길을 만든다
		while (pNode != nullptr) {
			_listMaximumPath.push_front(pNode);

			pNode = pNode->parrentNode;
		}

		return;
	}


	pathFinder();
}


void ASTAR::release()
{
	while (!_listOpendNode.empty())
	{
		TILENODE* pNode = _listOpendNode.back();
		_listOpendNode.pop_back();
	}
	while (!_listClosedyPath.empty())
	{
		TILENODE* pNode = _listClosedyPath.back();
		_listClosedyPath.pop_back();
	}
	if (!_listMaximumPath.empty())
	{
		TILENODE* pNode = _listMaximumPath.back();
		_listMaximumPath.pop_back();
	}
	_listMaximumPath.clear();

}

