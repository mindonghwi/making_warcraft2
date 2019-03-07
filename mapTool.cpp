#include "stdafx.h"
#include "mapTool.h"
#include "camera.h"

MAPTOOL::MAPTOOL():
	_nTileSize(0),
	_nTileCountX(0),
	_nTileCountY(0),
	_nMapWidth(0),
	_nMapHeight(0),
	_nCurrentTileX(0),
	_nCurrentTileY(0),
	_pImgMap(nullptr)
{
}

MAPTOOL::~MAPTOOL()
{
}

void MAPTOOL::createMap()
{
	//세로로 그리고 그다음 가로로 하나씩
	int nNodeIndex(0);
	_vvMap.resize(_nTileCountY);
	for (int i = 0; i < _nTileCountY; i++)
	{
		for (int j = 0; j < _nTileCountX; j++)
		{
			_vvMap[i].push_back(new TILE());
			_vvMap[i][j]->init(j * _nTileSize, i * _nTileSize, _nTileSize, _pImgMap, nNodeIndex);
			_vvMap[i][j]->setTerrian(_eTerrian);
			nNodeIndex++;
		}
	}
}

void MAPTOOL::setResizeNodeIndex()
{
	int nIndex(0);
	for (int i = 0; i < _nTileCountY; i++)
	{
		for (int j = 0; j < _nTileCountX; j++)
		{
			_vvMap[i][j]->setNodeIndex(nIndex);
			nIndex++;
		}
	}
}

void MAPTOOL::init(int nTileCountX, int nTileCountY, int nTileSize)
{

	_nTileCountX = nTileCountX;
	_nTileCountY = nTileCountY;
	_nTileSize = nTileSize;

	_nMapWidth = _nTileCountX * _nTileSize;
	_nMapHeight = _nTileCountY * _nTileSize;

	_nCurrentTileX = 0;
	_nCurrentTileY = 0;
	_bIsWall = false;
	
	_eTerrian;
	setObject(TILE::E_OBJECT::E_NONE);
	setTerrian(TILE::E_TERRIAN::GROUND);

	_arReadjustMap[0] = 1;
	_arReadjustMap[1] = 2;
	_arReadjustMap[2] = 3;
	_arReadjustMap[3] = 4;
	_arReadjustMap[4] = 8;
	_arReadjustMap[5] = 12;


	_pImgMap = IMAGEMANAGER->findImage("mapSprites");
	_pObjectImg = IMAGEMANAGER->findImage("mapTiles");
	
	releaseObject();
	createMap();
}

void MAPTOOL::release()
{
	_pImgMap = nullptr;

	for (int i = 0; i < _nTileCountY; i++)
	{
		for (int j = 0; j <_nTileCountX; j++)
		{
			TILE * pTile = _vvMap.back().back();
			pTile->release();
			_vvMap.back().pop_back();
			delete pTile;
			pTile = nullptr;
		}
		_vvMap.pop_back();
	}

}

void MAPTOOL::render(HDC hdc)
{

	for (int j = 0; j < _nTileCountY; j++)
	{
		for (int i = 0; i < _nTileCountX; i++)
		{
			_vvMap[j][i]->render(hdc);
		}
	}
	//for (int j = 0; j < _nTileCountY; j++)
	//{
	//	for (int i = 0; i < _nTileCountX; i++)
	//	{
	//		char str[32];
	//		sprintf_s(str, "%d,%d", i, j);
	//		TextOut(hdc, _vvMap[j][i]->getRectTile().left , _vvMap[j][i]->getRectTile().top , str, strlen(str));
	//	}
	//}

	POINT ptCameraMouse;
	ptCameraMouse.x = _ptMouse.x + _pCamera->getLeft();
	ptCameraMouse.y = _ptMouse.y + _pCamera->getTop();
	
	int nIndexX = 0;
	int nIndexY = 0;
	nIndexX = ptCameraMouse.x / TILESIZE;
	nIndexY = ptCameraMouse.y / TILESIZE;
	if (nIndexX >= _nTileCountX)
	{
		nIndexX = _nTileCountX - 1;
	}
	if (nIndexY >= _nTileCountY)
	{
		nIndexY = _nTileCountY - 1;
	}
	RectangleMake(hdc, _vvMap[nIndexY][nIndexX]->getRectTile().left, _vvMap[nIndexY][nIndexX]->getRectTile().top,32,32);
}

void MAPTOOL::update()
{
	//World coordinates the mouse local coordinates.
	POINT ptCameraMouse;
	ptCameraMouse.x = _ptMouse.x + _pCamera->getLeft();
	ptCameraMouse.y = _ptMouse.y + _pCamera->getTop();

	//Draw on tiles
	if (KEYMANAGER->isStayKeyDown(VK_LBUTTON) && _ptMouse.x < WINSIZEX - 100) {
		for (int j = 0; j < _nTileCountY; j++)
		{
			for (int i = 0; i < _nTileCountX; i++)
			{
				TILE* pTile = _vvMap[j][i];
				
				if (PtInRect(&(pTile->getRectTile()), ptCameraMouse))
				{
					if (_eObject == TILE::E_OBJECT::E_NONE)
					{
						drawMap(i, j);
					}
					else
					{
						drawObject(i, j);
					}
					
				}
			}
		}
	}

	//Re-adjust the terrain.
	while (!readjustMap()) {}
	readjustRock();
	

	//tile - Clapping
	for (int j = 0; j < _nTileCountY; j++)
	{
		for (int i = 0; i < _nTileCountX; i++)
		{
			TILE* pTile = _vvMap[j][i];
			pTile->setLimitRect(_pCamera->getLimitRect());
			pTile->extendLimitRect(32);
		}
	}

	//Re-adjust the Object
	readjustObject();


	//resource push the Camera
	list<GOLDMINE*>::iterator iter = _listGoldMine.begin();
	list<GOLDMINE*>::iterator end = _listGoldMine.end();
	while (iter != end)
	{
		(*iter)->update();
		iter++;
	}
	
	list<TREE*>::iterator iterTree = _listTree.begin();
	list<TREE*>::iterator endTree = _listTree.end();
	while (iterTree != endTree)
	{
		(*iterTree)->update();
		iterTree++;
	}
	
	list<OILPATCH*>::iterator iterOil = _listOilPatch.begin();
	list<OILPATCH*>::iterator endOil = _listOilPatch.end();
	while (iterOil != endOil)
	{
		(*iterOil)->update();
		iterOil++;
	}
}



string MAPTOOL::setSaveMapTool()
{
	//맵툴에는 타일 사이즈/ 타일 가로 갯수/ 타일 세로 갯수 / 파레트 셀 갯수
	string strTmp = "";
	strTmp.append(to_string(_nTileSize));
	strTmp.append("/");
	strTmp.append(to_string(_nTileCountX));
	strTmp.append("/");
	strTmp.append(to_string(_nTileCountY));
	strTmp.append("/");

	return strTmp;
}

string MAPTOOL::makeSaveMap()
{
	string strTmp = "";
	for (int j = 0; j < _nTileCountY; j++)
	{
		for (int i = 0; i < _nTileCountX; i++)
		{
			strTmp.append(_vvMap[j][i]->makeSaveString());
		}
	}

	return strTmp;
}

void MAPTOOL::drawMap(int nIndexX, int nIndexY)
{
	if (_eTerrian == TILE::E_TERRIAN::DIRT)
	{
		for (int i = 0; i < 8; i++)
		{
			int nTmpIndexX = nIndexX + _arInterval[i][0];
			int nTmpIndexY = nIndexY + _arInterval[i][1];

			if (nTmpIndexX < 0) continue;
			if (nTmpIndexX >= _nTileCountX) continue;
			if (nTmpIndexY < 0) continue;
			if (nTmpIndexY >= _nTileCountY) continue;
			if (_vvMap[nTmpIndexY][nTmpIndexX]->getTerrian() != _eTerrian)
			{
				_vvMap[nTmpIndexY][nTmpIndexX]->settingTile(_nCurrentTileX, _nCurrentTileY, _bIsWall, TILE::E_TERRIAN::DIRT, _eObject);
			}
		}
	}
	else if (_eTerrian == TILE::E_TERRIAN::GROUND || _eTerrian == TILE::E_TERRIAN::WATER)
	{
		for (int i = -2; i < 3; i++)
		{
			for (int j = -2; j < 3; j++)
			{
				int nTmpIndexX = nIndexX + i;
				int nTmpIndexY = nIndexY + j;

				if (nTmpIndexX < 0) continue;
				if (nTmpIndexX >= _nTileCountX) continue;
				if (nTmpIndexY < 0) continue;
				if (nTmpIndexY >= _nTileCountY) continue;

				if (_vvMap[nTmpIndexY][nTmpIndexX]->getTerrian() != _eTerrian)
				{
					_vvMap[nTmpIndexY][nTmpIndexX]->settingTile(_nCurrentTileX, _nCurrentTileY, _bIsWall, TILE::E_TERRIAN::DIRT, _eObject);
				}
			}
		}
	}
	else if (_eTerrian == TILE::E_TERRIAN::ROCK)
	{
		for (int i = -2; i < 3; i++)
		{
			for (int j = -2; j < 3; j++)
			{
				int nTmpIndexX = nIndexX + i;
				int nTmpIndexY = nIndexY + j;

				if (nTmpIndexX < 0) continue;
				if (nTmpIndexX >= _nTileCountX) continue;
				if (nTmpIndexY < 0) continue;
				if (nTmpIndexY >= _nTileCountY) continue;

				if (_vvMap[nTmpIndexY][nTmpIndexX]->getTerrian() != _eTerrian)
				{
					_vvMap[nTmpIndexY][nTmpIndexX]->settingTile(_nCurrentTileX, _nCurrentTileY, _bIsWall, TILE::E_TERRIAN::DIRT, _eObject);
				}
			}
		}


		for (int i = 0; i < 8; i++)
		{
			int nTmpIndexX = nIndexX + _arInterval[i][0];
			int nTmpIndexY = nIndexY + _arInterval[i][1];

			if (nTmpIndexX < 0) continue;
			if (nTmpIndexX >= _nTileCountX) continue;
			if (nTmpIndexY < 0) continue;
			if (nTmpIndexY >= _nTileCountY) continue;

			if (_vvMap[nTmpIndexY][nTmpIndexX]->getTerrian() != _eTerrian)
			{
				_vvMap[nTmpIndexY][nTmpIndexX]->settingTile(_nCurrentTileX, _nCurrentTileY, _bIsWall, TILE::E_TERRIAN::ROCK, _eObject);
			}
		}
	}

	_vvMap[nIndexY][nIndexX]->settingTile(_nCurrentTileX, _nCurrentTileY, _bIsWall, _eTerrian, _eObject);
}

void MAPTOOL::drawObject(int nIndexX, int nIndexY)
{
	switch (_eObject)
	{
	case TILE::E_OBJECT::E_TREE:
		drawTree(nIndexX, nIndexY);
		break;
	case TILE::E_OBJECT::E_GOLDMINE:
		drawGoldMine(nIndexX, nIndexY);
		break;
	case TILE::E_OBJECT::E_OILPATCH:
		drawOilPatch(nIndexX, nIndexY);
		break;
	case TILE::E_OBJECT::E_BUILDING:
		break;
	case TILE::E_OBJECT::E_UNIT:
		break;

	}
}

void MAPTOOL::releaseObject()
{
	//resource release
	list<GOLDMINE*>::iterator iter = _listGoldMine.begin();
	list<GOLDMINE*>::iterator end = _listGoldMine.end();
	while (iter != end)
	{
		GOLDMINE* pGoldMine = *iter;
		pGoldMine->release();
		
		iter = _listGoldMine.erase(iter);
		delete pGoldMine;
		pGoldMine = nullptr;
	}

	list<TREE*>::iterator iterTree = _listTree.begin();
	list<TREE*>::iterator endTree = _listTree.end();
	while (iterTree != endTree)
	{
		TREE* pTree = *iterTree;
		pTree->release();

		iterTree = _listTree.erase(iterTree);
		delete pTree;
		pTree = nullptr;
	}

	list<OILPATCH*>::iterator iterOil = _listOilPatch.begin();
	list<OILPATCH*>::iterator endOil = _listOilPatch.end();
	while (iterOil != endOil)
	{
		OILPATCH* pOilPatch = *iterOil;
		pOilPatch->release();

		iterOil = _listOilPatch.erase(iterOil);
		delete pOilPatch;
		pOilPatch = nullptr;
	}

	_listGoldMine.clear();
	_listTree.clear();
	_listOilPatch.clear();
}

void MAPTOOL::mapResize(int nTileCountX, int nTileCountY)
{
	if (nTileCountX == 0 || nTileCountY == 0)
	{
		return;
	}
	
	if (_nTileCountX <= nTileCountX)
	{
		//추가하면 된다!!
		int nOffset = nTileCountX - _nTileCountX;
		
		//int nLeft = _vvMap[0][_nTileCountX - 1]->getRectTile().right;

		for (int j = 0; j < _nTileCountY; j++)
		{
			for (int i = 0; i < nOffset; i++)
			{
				int nLeft = _vvMap[j].back()->getRectTile().right;
				int nTop = _vvMap[j].back()->getRectTile().top;
				_vvMap[j].push_back(new TILE());
				TILE* pTile = _vvMap[j].back();
				pTile->init((i+1)*nLeft, nTop, _nTileSize, _pImgMap, 0);
				pTile->setTerrian(_eTerrian);
				pTile = nullptr;
			}
		}

	}
	else
	{
		//빼야한다!!!
		int nOffset = _nTileCountX - nTileCountX;

		for (int j = 0; j < _nTileCountY; j++)
		{
			for (int i = 0; i < nOffset; i++)
			{
				TILE* pTile = _vvMap[j].back();
				pTile->release();
				_vvMap[j].pop_back();
				delete pTile;
				pTile = nullptr;
			}
		}
	}
	_nTileCountX = nTileCountX;

	if (_nTileCountY <= nTileCountY)
	{
		//추가하면 된다.

		int nOffset = nTileCountY - _nTileCountY;

		int nLeft = _vvMap[_nTileCountY - 1].front()->getRectTile().left;
		int nTop = _vvMap[_nTileCountY - 1].front()->getRectTile().bottom;

		for (int j = 0; j < nOffset; j++)
		{
			vector<TILE*> vMapLine;
			for (int i = 0; i < _nTileCountX; i++)
			{
				vMapLine.push_back(new TILE());
				TILE* pTile = vMapLine.back();
				pTile->init((i )*_nTileSize + nLeft,(j+1)* nTop, _nTileSize, _pImgMap, 0);
				pTile->setTerrian(_eTerrian);
				pTile = nullptr;
			}
			_vvMap.push_back(vMapLine);
		}
	}
	else
	{
		//빼야한다.
		int nOffset = _nTileCountY - nTileCountY;

		for (int j = 0; j < nOffset; j++)
		{
			for (int i = 0; i < _nTileCountX; i++)
			{
				TILE* pTile = _vvMap.back().back();
				pTile->release();
				_vvMap.back().pop_back();
				delete pTile;
				pTile = nullptr;
			}
			_vvMap.pop_back();
		}
	}
	_nTileCountY = nTileCountY;
	setResizeNodeIndex();
}

bool MAPTOOL::readjustMap()
{
	//terrian재조정
	for (int j = 0; j < _nTileCountY; j++)
	{
		for (int i = 0; i < _nTileCountX; i++)
		{
			//벽이면 검사

			TILE::E_TERRIAN eTerrian = _vvMap[j][i]->getTerrian();
			TILE::E_TERRIAN eTmp = eTerrian;	//자기 속성을 가질것이다.

			if (eTerrian == TILE::E_TERRIAN::DIRT_GROUND ||
				eTerrian == TILE::E_TERRIAN::DIRT_WATER ||
				eTerrian == TILE::E_TERRIAN::ROCK)
			{
				eTerrian = TILE::E_TERRIAN::DIRT;
			}

			if (eTerrian == TILE::E_TERRIAN::DIRT)
			{
				unsigned int nFrameX(0);
				int nFrameY(0);
				if (j > 0)
				{
					//위쪽 탐색 가능
					if (_vvMap[j - 1][i]->getTerrian() == TILE::E_TERRIAN::DIRT||
						_vvMap[j - 1][i]->getTerrian() == TILE::E_TERRIAN::ROCK)
					{
						nFrameX |= E_MAPTILEPOS::E_TOP;
					}
					else
					{
						eTmp = _vvMap[j - 1][i]->getTerrian();
					}
				}

				if (j < _nTileCountY - 1)
				{
					//아래 탐색 가능
					if (_vvMap[j + 1][i]->getTerrian() == TILE::E_TERRIAN::DIRT ||
						_vvMap[j + 1][i]->getTerrian() == TILE::E_TERRIAN::ROCK)
					{
						nFrameX |= E_MAPTILEPOS::E_BOTTOM;
					}
					else
					{
						eTmp = _vvMap[j + 1][i]->getTerrian();
					}
				}

				if (i > 0)
				{
					//좌측 탐색 가능
					if (_vvMap[j][i - 1]->getTerrian() == TILE::E_TERRIAN::DIRT ||
						_vvMap[j][i - 1]->getTerrian() == TILE::E_TERRIAN::ROCK)
					{
						nFrameX |= E_MAPTILEPOS::E_LEFT;
					}
					else
					{
						eTmp = _vvMap[j][i - 1]->getTerrian();
					}
				}

				if (i < _nTileCountX - 1)
				{
					//우측 탐색 가능

					if (_vvMap[j][i + 1]->getTerrian() == TILE::E_TERRIAN::DIRT ||
						_vvMap[j][i + 1]->getTerrian() == TILE::E_TERRIAN::ROCK)
					{
						nFrameX |= E_MAPTILEPOS::E_RIGHT;
					}
					else
					{
						eTmp = _vvMap[j][i + 1]->getTerrian();
					}
				}

				if (eTmp != TILE::E_TERRIAN::DIRT)
				{
					//for (int i = 0; i < 6; i++)
					//{
					//	if (nFrameX == _arReadjustMap[i])
					//	{
					//		_vvMap[j][i]->settingTile(0, 0, _bIsWall, eTmp, TILE::E_OBJECT::E_NONE);
					//		return false;
					//	}
					//}
					if (nFrameX == 3)
					{
						_vvMap[j][i]->settingTile(0, 0, _bIsWall, eTmp, TILE::E_OBJECT::E_NONE);
						return false;
					}
					else if (nFrameX == 12)
					{
						_vvMap[j][i]->settingTile(0, 0, _bIsWall, eTmp, TILE::E_OBJECT::E_NONE);
						return false;
					}
					else if (nFrameX == 1 || nFrameX == 2 || nFrameX == 4 || nFrameX == 8)
					{
						_vvMap[j][i]->settingTile(0, 0, _bIsWall, eTmp, TILE::E_OBJECT::E_NONE);
						return false;
					}
					else if (nFrameX == 0)
					{
						_vvMap[j][i]->settingTile(0, 0, _bIsWall, eTmp, TILE::E_OBJECT::E_NONE);
						return false;
					}
				}


				//찾아야한다 주변에 풀인지 바다인지
				if (nFrameX > 0 && nFrameX < 15)
				{
					if (eTmp == TILE::E_TERRIAN::GROUND)
					{
						nFrameY = 3;
					}
					else if (eTmp == TILE::E_TERRIAN::WATER)
					{
						nFrameY = 4;
					}
				}
				else
				{
					if (nFrameX == 15)
					{
						if (_vvMap[j - 1][i - 1]->getTerrian() != TILE::E_TERRIAN::DIRT
							&& _vvMap[j - 1][i - 1]->getTerrian() != TILE::E_TERRIAN::ROCK 
							&& _vvMap[j - 1][i - 1]->getTerrian() != TILE::E_TERRIAN::DIRT_WATER
							&& _vvMap[j - 1][i - 1]->getTerrian() != TILE::E_TERRIAN::DIRT_GROUND)
						{
							nFrameX += static_cast<unsigned int>(E_DIAGONAL::E_NORTH_WEST);
							if (_vvMap[j - 1][i - 1]->getTerrian() == TILE::E_TERRIAN::GROUND)
							{
								nFrameY = 3;
							}
							else if (_vvMap[j - 1][i - 1]->getTerrian() == TILE::E_TERRIAN::WATER)
							{
								nFrameY = 4;
							}

						}
						else if (_vvMap[j - 1][i + 1]->getTerrian() != TILE::E_TERRIAN::DIRT
							&& _vvMap[j - 1][i + 1]->getTerrian() != TILE::E_TERRIAN::ROCK
							&& _vvMap[j - 1][i + 1]->getTerrian() != TILE::E_TERRIAN::DIRT_WATER
							&& _vvMap[j - 1][i + 1]->getTerrian() != TILE::E_TERRIAN::DIRT_GROUND) {
							nFrameX += static_cast<unsigned int>(E_DIAGONAL::E_NORTH_EAST);
							if (_vvMap[j - 1][i + 1]->getTerrian() == TILE::E_TERRIAN::GROUND)
							{
								nFrameY = 3;
							}
							else if (_vvMap[j - 1][i + 1]->getTerrian() == TILE::E_TERRIAN::WATER)
							{
								nFrameY = 4;
							}
						}
						else if (_vvMap[j + 1][i - 1]->getTerrian() != TILE::E_TERRIAN::DIRT
							&& _vvMap[j + 1][i - 1]->getTerrian() != TILE::E_TERRIAN::ROCK
							&& _vvMap[j + 1][i - 1]->getTerrian() != TILE::E_TERRIAN::DIRT_WATER
							&& _vvMap[j + 1][i - 1]->getTerrian() != TILE::E_TERRIAN::DIRT_GROUND) {
							nFrameX += static_cast<unsigned int>(E_DIAGONAL::E_SOUTH_WEST);
							if (_vvMap[j + 1][i - 1]->getTerrian() == TILE::E_TERRIAN::GROUND)
							{
								nFrameY = 3;
							}
							else if (_vvMap[j + 1][i - 1]->getTerrian() == TILE::E_TERRIAN::WATER)
							{
								nFrameY = 4;
							}
						}
						else if (_vvMap[j + 1][i + 1]->getTerrian() != TILE::E_TERRIAN::DIRT
							&& _vvMap[j + 1][i + 1]->getTerrian() != TILE::E_TERRIAN::ROCK
							&& _vvMap[j + 1][i + 1]->getTerrian() != TILE::E_TERRIAN::DIRT_WATER
							&& _vvMap[j + 1][i + 1]->getTerrian() != TILE::E_TERRIAN::DIRT_GROUND) {
							nFrameX += static_cast<unsigned int>(E_DIAGONAL::E_SOUTH_EAST);
							if (_vvMap[j + 1][i + 1]->getTerrian() == TILE::E_TERRIAN::GROUND)
							{
								nFrameY = 3;
							}
							else if (_vvMap[j + 1][i + 1]->getTerrian() == TILE::E_TERRIAN::WATER)
							{
								nFrameY = 4;
							}
						}
						else
						{
							nFrameY = 2;
						}
					}

				}

				_vvMap[j][i]->readjustWall((int)nFrameX, (int)nFrameX, nFrameY);
			}


		}
	}

	return true;
}

bool MAPTOOL::readjustObject()
{
	readjustGoldMine();
	reAdjustTree();
	readjustOilPatch();


	return false;
}

void MAPTOOL::save()
{
	//세이브는 크기 두가지로한다.
	//현재 맵툴에 있는 데이터와
	//타일들에 있는 데이터로 구분해서 저장한다.
	//맵툴에는 타일 사이즈/ 타일 가로 갯수/ 타일 세로 갯수 / 파레트 셀 갯수
	//타일에는 주변벽값/ 벽인지 아닌지/ 이미지 키값/ 프레임 x/ 프레임 y/ 사격형/ 노드 인덱스
	//노드인덱스/주변값/벽/프레임x/프레임y/object/terrian
	HANDLE file;
	DWORD write;
	
	string strTmp = makeSaveMap();
	
	file = CreateFile("map01.map", GENERIC_WRITE, NULL, NULL,
		CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	WriteFile(file, strTmp.c_str(), static_cast<DWORD>(strTmp.length()), &write, NULL);
	CloseHandle(file);

	strTmp.clear();
	strTmp.append(setSaveMapTool());
	file = CreateFile("mapFull01.map", GENERIC_WRITE, NULL, NULL,
		CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	WriteFile(file, strTmp.c_str(), static_cast<DWORD>(strTmp.length()), &write, NULL);
	CloseHandle(file);
}

void MAPTOOL::load()
{
	HANDLE file;
	DWORD read;

	char strTmp[100]{};

	file = CreateFile("mapFull01.map", GENERIC_READ, NULL, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	//ReadFile(file, str, 5000, &read, NULL);
	ReadFile(file, strTmp, 100, &read, NULL);
	CloseHandle(file);

	char* temp;
	const char* separator = "/"; //구분자
	char* token;

	//맵툴에는 타일 사이즈/ 타일 가로 갯수/ 타일 세로 갯수 / 파레트 셀 갯수

	token = strtok_s(strTmp, separator, &temp);

	_nTileSize = (atoi(token));
	token = strtok_s(NULL, separator, &temp);
	_nTileCountX = (atoi(token));							
	token = strtok_s(NULL, separator, &temp);
	_nTileCountY = atoi(token);

	this->init(_nTileCountX, _nTileCountY,_nTileSize);

	int nData = _nTileCountX * _nTileCountY * 20;
	char* strs = new char[nData];
	


	file = CreateFile("map01.map", GENERIC_READ, NULL, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, strs, nData, &read, NULL);
	//ReadFile(file, strTmp, 100, &read, NULL);
	CloseHandle(file);


	char* tmp;
	char* tokenMap;

	tokenMap = strtok_s(strs, separator, &tmp);


	//노드인덱스/주변값/벽/프레임x/프레임y/object/terrian
	for (int j = 0; j < _nTileCountY; j++)
	{
		for (int i = 0; i < _nTileCountX; i++)
		{
			//노드인덱스/주변값/벽/프레임x/프레임y/object/terrian
			_vvMap[j][i]->setNodeIndex(atoi(tokenMap));
			tokenMap = strtok_s(NULL, separator, &tmp);
			_vvMap[j][i]->setAroundWall(atoi(tokenMap));
			tokenMap = strtok_s(NULL, separator, &tmp);
			_vvMap[j][i]->setIsWall(atoi(tokenMap));
			tokenMap = strtok_s(NULL, separator, &tmp);
			_vvMap[j][i]->setFrameX(atoi(tokenMap));
			tokenMap = strtok_s(NULL, separator, &tmp);
			_vvMap[j][i]->setFrameY(atoi(tokenMap));
			tokenMap = strtok_s(NULL, separator, &tmp);
			_vvMap[j][i]->setObject(static_cast<TILE::E_OBJECT>(atoi(tokenMap)));
			_vvMap[j][i]->setttingObject();
			tokenMap = strtok_s(NULL, separator, &tmp);
			_vvMap[j][i]->setTerrian(static_cast<TILE::E_TERRIAN>(atoi(tokenMap)));
			_vvMap[j][i]->settingTerrian();
			tokenMap = strtok_s(NULL, separator, &tmp);
		}
	}

	delete[] strs;
	strs = nullptr;
	loadObject();
}



void MAPTOOL::deleteObject()
{
	for (int j = 0; j < _nTileCountY; j++)
	{
		for (int i = 0; i < _nTileCountX; i++)
		{
			_vvMap[j][i]->setObject(TILE::E_OBJECT::E_NONE);
		}
	}
}

void MAPTOOL::drawGoldMine(int nIndexX, int nIndexY)
{
	bool bIsDraw = true;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			int nTmpIndexX = nIndexX + i;
			int nTmpIndexY = nIndexY + j;

			if (nTmpIndexX < 0 ||
				nTmpIndexX >= _nTileCountX ||
				nTmpIndexY < 0 ||
				nTmpIndexY >= _nTileCountY)
			{
				bIsDraw = false;
				break;
			}

			if (_vvMap[nTmpIndexY][nTmpIndexX]->getTerrian() != TILE::E_TERRIAN::GROUND)
			{
				bIsDraw = false;
				break;
			}

			if (_vvMap[nTmpIndexY][nTmpIndexX]->getObject() != TILE::E_OBJECT::E_NONE)
			{
				bIsDraw = false;
				break;
			}
		}
	}


	if (bIsDraw)
	{
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				int nTmpIndexX = nIndexX + i;
				int nTmpIndexY = nIndexY + j;

				_vvMap[nTmpIndexY][nTmpIndexX]->settingTile(_nCurrentTileX, _nCurrentTileY, _bIsWall, _eTerrian, _eObject);
			}
		}


		_listGoldMine.push_back(new GOLDMINE);
		_listGoldMine.back()->linkCamera(_pCamera);
		_listGoldMine.back()->init(nIndexX * 32, nIndexY * 32);
	}
}

void MAPTOOL::drawTree(int nIndexX, int nIndexY)
{
	bool bIsDraw = true;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			int nTmpIndexX = nIndexX + i;
			int nTmpIndexY = nIndexY + j;

			if (nTmpIndexX < 0 ||
				nTmpIndexX >= _nTileCountX ||
				nTmpIndexY < 0 ||
				nTmpIndexY >= _nTileCountY)
			{
				bIsDraw = false;
				break;
			}

			if (_vvMap[nTmpIndexY][nTmpIndexX]->getTerrian() != TILE::E_TERRIAN::GROUND)
			{
				bIsDraw = false;
				break;
			}

			if (_vvMap[nTmpIndexY][nTmpIndexX]->getObject() != TILE::E_OBJECT::E_NONE)
			{
				bIsDraw = false;
				break;
			}
		}
	}


	if (bIsDraw)
	{
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				int nTmpIndexX = nIndexX + i;
				int nTmpIndexY = nIndexY + j;

				_vvMap[nTmpIndexY][nTmpIndexX]->settingTile(_nCurrentTileX, _nCurrentTileY, _bIsWall, _eTerrian, _eObject);
			}
		}


		_listTree.push_back(new TREE);
		_listTree.back()->linkCamera(_pCamera);
		_listTree.back()->init(nIndexX * 32, nIndexY * 32);
	}
}

void MAPTOOL::readjustGoldMine()
{
	list<GOLDMINE*>::iterator iter = _listGoldMine.begin();
	list<GOLDMINE*>::iterator end = _listGoldMine.end();
	while (iter != end)
	{
		GOLDMINE*	pGoldMine = *iter;

		int nIndexX(0);
		int nIndexY(0);
		bool bIsDestroy = false;

		nIndexX = static_cast<int>(pGoldMine->getPosX()) / TILESIZE;
		nIndexY = static_cast<int>(pGoldMine->getPosY()) / TILESIZE;

		for (int i = -1; i < 2; i++)
		{
			for (int j = -1; j < 2; j++)
			{
				int nTmpX = 0;
				int nTmpY = 0;
				nTmpX = nIndexX + i;
				nTmpY = nIndexY + j;

				if (_vvMap[nTmpY][nTmpX]->getTerrian() != TILE::E_TERRIAN::GROUND)
				{
					bIsDestroy = true;
					break;
				}
				if (_vvMap[nTmpY][nTmpX]->getObject() == TILE::E_OBJECT::E_NONE)
				{
					bIsDestroy = true;
					break;
				}
			}
			if (bIsDestroy)
			{
				break;
			}
		}


		if (bIsDestroy)
		{
			for (int i = -1; i < 2; i++)
			{
				for (int j = -1; j < 2; j++)
				{
					int nTmpX = 0;
					int nTmpY = 0;
					nTmpX = nIndexX + i;
					nTmpY = nIndexY + j;
					_vvMap[nTmpY][nTmpX]->setObject(TILE::E_OBJECT::E_NONE);
				}
			}

			iter = _listGoldMine.erase(iter);
		}
		else
		{
			iter++;
		}

	}

}

void MAPTOOL::reAdjustTree()
{
	list<TREE*>::iterator iter = _listTree.begin();
	list<TREE*>::iterator end = _listTree.end();
	while (iter != end)
	{
		TREE*	pGoldMine = *iter;

		int nIndexX(0);
		int nIndexY(0);
		bool bIsDestroy = false;

		nIndexX = static_cast<int>(pGoldMine->getPosX()) / TILESIZE;
		nIndexY = static_cast<int>(pGoldMine->getPosY()) / TILESIZE;

		for (int i = -1; i < 2; i++)
		{
			for (int j = -1; j < 2; j++)
			{
				int nTmpX = 0;
				int nTmpY = 0;
				nTmpX = nIndexX + i;
				nTmpY = nIndexY + j;

				if (_vvMap[nTmpY][nTmpX]->getTerrian() != TILE::E_TERRIAN::GROUND)
				{
					bIsDestroy = true;
					break;
				}
				if (_vvMap[nTmpY][nTmpX]->getObject() == TILE::E_OBJECT::E_NONE)
				{
					bIsDestroy = true;
					break;
				}
			}
			if (bIsDestroy)
			{
				break;
			}
		}


		if (bIsDestroy)
		{
			for (int i = -1; i < 2; i++)
			{
				for (int j = -1; j < 2; j++)
				{
					int nTmpX = 0;
					int nTmpY = 0;
					nTmpX = nIndexX + i;
					nTmpY = nIndexY + j;
					_vvMap[nTmpY][nTmpX]->setObject(TILE::E_OBJECT::E_NONE);
				}
			}

			iter = _listTree.erase(iter);
		}
		else
		{
			iter++;
		}

	}
}

void MAPTOOL::drawOilPatch(int nIndexX, int nIndexY)
{
	bool bIsDraw = true;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			int nTmpIndexX = nIndexX + i;
			int nTmpIndexY = nIndexY + j;

			if (nTmpIndexX < 0 ||
				nTmpIndexX >= _nTileCountX ||
				nTmpIndexY < 0 ||
				nTmpIndexY >= _nTileCountY)
			{
				bIsDraw = false;
				break;
			}

			if (_vvMap[nTmpIndexY][nTmpIndexX]->getTerrian() != TILE::E_TERRIAN::WATER)
			{
				bIsDraw = false;
				break;
			}

			if (_vvMap[nTmpIndexY][nTmpIndexX]->getObject() != TILE::E_OBJECT::E_NONE)
			{
				bIsDraw = false;
				break;
			}
		}
	}


	if (bIsDraw)
	{
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				int nTmpIndexX = nIndexX + i;
				int nTmpIndexY = nIndexY + j;

				_vvMap[nTmpIndexY][nTmpIndexX]->settingTile(_nCurrentTileX, _nCurrentTileY, _bIsWall, _eTerrian, _eObject);
			}
		}


		_listOilPatch.push_back(new OILPATCH);
		_listOilPatch.back()->linkCamera(_pCamera);
		_listOilPatch.back()->init(nIndexX * 32, nIndexY * 32);
	}
}

void MAPTOOL::readjustOilPatch()
{
	list<OILPATCH*>::iterator iter = _listOilPatch.begin();
	list<OILPATCH*>::iterator end = _listOilPatch.end();
	while (iter != end)
	{
		OILPATCH*	pGoldMine = *iter;

		int nIndexX(0);
		int nIndexY(0);
		bool bIsDestroy = false;

		nIndexX = static_cast<int>(pGoldMine->getPosX()) / TILESIZE;
		nIndexY = static_cast<int>(pGoldMine->getPosY()) / TILESIZE;

		for (int i = -1; i < 2; i++)
		{
			for (int j = -1; j < 2; j++)
			{
				int nTmpX = 0;
				int nTmpY = 0;
				nTmpX = nIndexX + i;
				nTmpY = nIndexY + j;

				if (_vvMap[nTmpY][nTmpX]->getTerrian() != TILE::E_TERRIAN::WATER)
				{
					bIsDestroy = true;
					break;
				}
				if (_vvMap[nTmpY][nTmpX]->getObject() == TILE::E_OBJECT::E_NONE)
				{
					bIsDestroy = true;
					break;
				}
			}
			if (bIsDestroy)
			{
				break;
			}
		}


		if (bIsDestroy)
		{
			for (int i = -1; i < 2; i++)
			{
				for (int j = -1; j < 2; j++)
				{
					int nTmpX = 0;
					int nTmpY = 0;
					nTmpX = nIndexX + i;
					nTmpY = nIndexY + j;
					_vvMap[nTmpY][nTmpX]->setObject(TILE::E_OBJECT::E_NONE);
				}
			}

			iter = _listOilPatch.erase(iter);
		}
		else
		{
			iter++;
		}

	}
}

void MAPTOOL::loadObject()
{
	//resource release
	bool bIsResource = false;

	for (int j = 0; j < _nTileCountY; j++)
	{
		for (int i = 0; i < _nTileCountX; i++)
		{
			if (!_vvMap[j][i]->getIsObjectLoadCheck())
			{
				switch (_vvMap[j][i]->getObject())
				{
				case TILE::E_OBJECT::E_GOLDMINE:
					bIsResource = true;
					for (int k = 0; k < 3; k++)
					{
						for (int h = 0; h < 3; h++)
						{

							if (_vvMap[j + k][i + h]->getObject() != TILE::E_OBJECT::E_GOLDMINE)
							{
								bIsResource = false;
								break;
							}
							else
							{
								_vvMap[j + k][i + h]->setIsObjectLoadCheck(true);
							}
						}
						if (!bIsResource)
						{
							break;
						}
					}

					if (bIsResource)
					{
						GOLDMINE* pGoldMine = new GOLDMINE();
						pGoldMine->init(_vvMap[j][i]->getRectTile().left, _vvMap[j][i]->getRectTile().top);
						pGoldMine->linkCamera(_pCamera);
						_listGoldMine.push_back(pGoldMine);
						
					}
					break;

				case TILE::E_OBJECT::E_TREE:
					bIsResource = true;

					for (int k = 0; k < 3; k++)
					{
						for (int h = 0; h < 3; h++)
						{
							if (_vvMap[j + k][i + h]->getObject() != TILE::E_OBJECT::E_TREE)
							{
								bIsResource = false;
								break;
							}
							else
							{
								_vvMap[j + k][i + h]->setIsObjectLoadCheck(true);
							}
						}
						if (!bIsResource)
						{
							break;
						}
					}

					if (bIsResource)
					{
						TREE* pTree = new TREE();
						pTree->init(_vvMap[j][i]->getRectTile().left, _vvMap[j][i]->getRectTile().top);
						pTree->linkCamera(_pCamera);
						_listTree.push_back(pTree);

					}
					break;

				case TILE::E_OBJECT::E_OILPATCH:
					bIsResource = true;

					for (int k = 0; k < 3; k++)
					{
						for (int h = 0; h < 3; h++)
						{
							if (_vvMap[j + k][i + h]->getObject() != TILE::E_OBJECT::E_OILPATCH)
							{
								bIsResource = false;
								break;
							}
							else
							{
								_vvMap[j + k][i + h]->setIsObjectLoadCheck(true);
							}
						}
						if (!bIsResource)
						{
							break;
						}
					}

					if (bIsResource)
					{
						OILPATCH* pOilPatch = new OILPATCH();
						pOilPatch->init(_vvMap[j][i]->getRectTile().left, _vvMap[j][i]->getRectTile().top);
						pOilPatch->linkCamera(_pCamera);
						_listOilPatch.push_back(pOilPatch);

					}
					break;
				}
			}

		}
	}
}

void MAPTOOL::readjustRock()
{
	//돌이미지 조정
	for (int j = 0; j < _nTileCountY; j++)
	{
		for (int i = 0; i < _nTileCountX; i++)
		{
			if (_vvMap[j][i]->getTerrian() == TILE::E_TERRIAN::ROCK)
			{
				unsigned int nFrameX(0);
				if (j > 0)
				{
					//위쪽 탐색 가능
					if (_vvMap[j - 1][i]->getTerrian() == TILE::E_TERRIAN::ROCK)
					{
						nFrameX |= E_MAPTILEPOS::E_TOP;
					}
				}

				if (j < _nTileCountY - 1)
				{
					//아래 탐색 가능
					if (_vvMap[j + 1][i]->getTerrian() == TILE::E_TERRIAN::ROCK)
					{
						nFrameX |= E_MAPTILEPOS::E_BOTTOM;
					}

				}

				if (i > 0)
				{
					//좌측 탐색 가능
					if (_vvMap[j][i - 1]->getTerrian() == TILE::E_TERRIAN::ROCK)
					{
						nFrameX |= E_MAPTILEPOS::E_LEFT;
					}
	
				}

				if (i < _nTileCountX - 1)
				{
					//우측 탐색 가능

					if (_vvMap[j][i + 1]->getTerrian() == TILE::E_TERRIAN::ROCK)
					{
						nFrameX |= E_MAPTILEPOS::E_RIGHT;
					}

				}


				if (nFrameX < 5 || nFrameX == 12 || nFrameX == 8)
				{
					_vvMap[j][i]->settingTile(0, 0, _bIsWall, TILE::E_TERRIAN::DIRT, TILE::E_OBJECT::E_NONE);
				}
				else
				{
					_vvMap[j][i]->readjustWall((int)nFrameX, (int)nFrameX, 0);
				}

			}
		}
	}
}
