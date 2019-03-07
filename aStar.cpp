#include "stdafx.h"
#include "aStar.h"


ASTAR::TILENODE * ASTAR::getNode(int nIndex)
{
	list<TILENODE*>::iterator iter = _listMaximumPath.begin();
	for (int i = 0; i < nIndex; i++)
	{
		iter++;
	}

	return *iter;
}

void ASTAR::initMap()
{
	for (int j = 0; j < _nTileSizeY; j++)
	{
		for (int i = 0; i <_nTileSizeX; i++)
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
	_nStartIndexX = static_cast<int>(fStartPosX)/ TILESIZE;
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
		if (_eMoveHeight == MOVEHEIGHT::WATER && _pMap->getTile(nIntervalPosX, nIntervalPosY)->getTerrian() != TILE::E_TERRIAN::WATER) continue;
		if (_eMoveHeight != MOVEHEIGHT::FLY && _pMap->getTile(nIntervalPosX, nIntervalPosY)->getObject() != TILE::E_OBJECT::E_NONE) continue;

		//유닛들이 통과하면 안된다.
		//유닛이 만들어지면 플레이어의 유닛과 COM의 유닛들과 통과를 막는다.
		
		
		bool bIsSearch = false;
		list<TILENODE*>::iterator iter = _listOpendNode.begin();
		list<TILENODE*>::iterator end = _listOpendNode.end();
		//////////open에 있으면 
		while (iter != end)
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


					_listOpendNode.erase(iter);

					iter = _listOpendNode.begin();
					while ((*iter)->nPathToatalCost < _vvTile[nIntervalPosY][nIntervalPosX]->nPathToatalCost) {
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
		end = _listClosedyPath.end();
		while (iter != end)
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

	if (_listClosedyPath.size() > 50)
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

