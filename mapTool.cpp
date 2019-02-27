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
	
	
	RectangleMake(hdc, _vvMap[ptCameraMouse.y / 32][ptCameraMouse.x / 32]->getRectTile().left, _vvMap[ptCameraMouse.y / 32][ptCameraMouse.x / 32]->getRectTile().top,32,32);
}

void MAPTOOL::update()
{

	POINT ptCameraMouse;
	ptCameraMouse.x = _ptMouse.x + _pCamera->getLeft();
	ptCameraMouse.y = _ptMouse.y + _pCamera->getTop();
	if (KEYMANAGER->isStayKeyDown(VK_LBUTTON) && _ptMouse.x < WINSIZEX - 200) {
		for (int j = 0; j < _nTileCountY; j++)
		{
			for (int i = 0; i < _nTileCountX; i++)
			{
				TILE* pTile = _vvMap[j][i];
				
				if (PtInRect(&(pTile->getRectTile()), ptCameraMouse))
				{
					//땜빵
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

	if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON))
	{
		while (!readjustMap()) {}
		
	}

	
	for (int j = 0; j < _nTileCountY; j++)
	{
		for (int i = 0; i < _nTileCountX; i++)
		{
			TILE* pTile = _vvMap[j][i];
			pTile->setLimitRect(_pCamera->getLimitRect());
		}
	}

	readjustObject();


	list<GOLDMINE*>::iterator iter = _listGoldMine.begin();
	list<GOLDMINE*>::iterator end = _listGoldMine.end();
	while (iter != end)
	{
		(*iter)->update();
		iter++;
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

	_vvMap[nIndexY][nIndexX]->settingTile(_nCurrentTileX, _nCurrentTileY, _bIsWall, _eTerrian, _eObject);
}

void MAPTOOL::drawObject(int nIndexX, int nIndexY)
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
		_listGoldMine.back()->init(nIndexX*32, nIndexY*32);
		

	}
}

void MAPTOOL::mapResize(int nTileCountX, int nTileCountY)
{
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
	for (int j = 0; j < _nTileCountY; j++)
	{
		for (int i = 0; i < _nTileCountX; i++)
		{
			//벽이면 검사

			TILE::E_TERRIAN eTerrian = _vvMap[j][i]->getTerrian();
			TILE::E_TERRIAN eTmp = eTerrian;	//자기 속성을 가질것이다.

			if (eTerrian == TILE::E_TERRIAN::DIRT_GROUND ||
				eTerrian == TILE::E_TERRIAN::DIRT_WATER)
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
					if (_vvMap[j - 1][i]->getTerrian() == TILE::E_TERRIAN::DIRT)
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
					if (_vvMap[j + 1][i]->getTerrian() == eTerrian)
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
					if (_vvMap[j][i - 1]->getTerrian() == eTerrian)
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

					if (_vvMap[j][i + 1]->getTerrian() == eTerrian)
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


						if (_vvMap[j - 1][i - 1]->getTerrian() != TILE::E_TERRIAN::DIRT)
						{
							nFrameX += static_cast<unsigned int>(MAPTOOL::E_DIAGONAL::E_NORTH_WEST);
							if (_vvMap[j - 1][i - 1]->getTerrian() == TILE::E_TERRIAN::GROUND)
							{
								nFrameY = 3;
							}
							else if (_vvMap[j - 1][i - 1]->getTerrian() == TILE::E_TERRIAN::WATER)
							{
								nFrameY = 4;
							}

						}
						else if (_vvMap[j - 1][i + 1]->getTerrian() != TILE::E_TERRIAN::DIRT) {
							nFrameX += static_cast<unsigned int>(MAPTOOL::E_DIAGONAL::E_NORTH_EAST);
							if (_vvMap[j - 1][i + 1]->getTerrian() == TILE::E_TERRIAN::GROUND)
							{
								nFrameY = 3;
							}
							else if (_vvMap[j - 1][i + 1]->getTerrian() == TILE::E_TERRIAN::WATER)
							{
								nFrameY = 4;
							}
						}
						else if (_vvMap[j + 1][i - 1]->getTerrian() != TILE::E_TERRIAN::DIRT) {
							nFrameX += static_cast<unsigned int>(MAPTOOL::E_DIAGONAL::E_SOUTH_WEST);
							if (_vvMap[j + 1][i - 1]->getTerrian() == TILE::E_TERRIAN::GROUND)
							{
								nFrameY = 3;
							}
							else if (_vvMap[j + 1][i - 1]->getTerrian() == TILE::E_TERRIAN::WATER)
							{
								nFrameY = 4;
							}
						}
						else if (_vvMap[j + 1][i + 1]->getTerrian() != TILE::E_TERRIAN::DIRT) {
							nFrameX += static_cast<unsigned int>(MAPTOOL::E_DIAGONAL::E_SOUTH_EAST);
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



	return false;
}

void MAPTOOL::save()
{
	//세이브는 크기 두가지로한다.
	//현재 맵툴에 있는 데이터와
	//타일들에 있는 데이터로 구분해서 저장한다.
	//맵툴에는 타일 사이즈/ 타일 가로 갯수/ 타일 세로 갯수 / 파레트 셀 갯수
	//타일에는 주변벽값/ 벽인지 아닌지/ 이미지 키값/ 프레임 x/ 프레임 y/ 사격형/ 노드 인덱스

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

	ReadFile(file, strs, 20000, &read, NULL);
	//ReadFile(file, strTmp, 100, &read, NULL);
	CloseHandle(file);


	char* tmp;
	char* tokenMap;

	tokenMap = strtok_s(strs, separator, &tmp);

	for (int j = 0; j < _nTileCountY; j++)
	{
		for (int i = 0; i < _nTileCountX; i++)
		{
			
			//노드인덱스/주변값/벽/프레임x/프레임y			
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
		}
	}

	delete[] strs;
	strs = nullptr;
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
