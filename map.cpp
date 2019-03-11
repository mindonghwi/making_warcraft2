#include "stdafx.h"
#include "map.h"

MAP::MAP()
{
}

MAP::~MAP()
{
}



void MAP::createMap()
{
	_nMapWidth = _nTileCountX * _nTileSize;
	_nMapHeight = _nTileCountY * _nTileSize;

	_bIsWall = false;
	_object = TILE::E_OBJECT::E_NONE;

	_pImgMap = IMAGEMANAGER->addFrameImage("map", "image/mapFrame.bmp", 928, 32, 29, 1, true, Mins::getMazenta());
	_pObjectImg = IMAGEMANAGER->findImage("mapTiles");

	int nNodeIndex(0);
	_vvMap.resize(_nTileCountY);


	for (int i = 0; i < _nTileCountY; i++)
	{
		for (int j = 0; j < _nTileCountX; j++)
		{
			_vvMap[i].push_back(new TILE());
			_vvMap[i][j]->init(j * _nTileSize, i * _nTileSize, _nTileSize, _pImgMap, nNodeIndex);
			nNodeIndex++;
		}
	}
}

void MAP::init(const char * mapName)
{
	_strMapName = mapName;

	load();
	readjust();
}

void MAP::load()
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

	createMap();

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

void MAP::loadObject()
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
						_pResourceMgr->addGoldMine(_vvMap[j][i]->getRectTile().left, _vvMap[j][i]->getRectTile().top);
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
						_pResourceMgr->addTree(_vvMap[j][i]->getRectTile().left, _vvMap[j][i]->getRectTile().top);

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
						_pResourceMgr->addOilPatch(_vvMap[j][i]->getRectTile().left, _vvMap[j][i]->getRectTile().top);


					}
					break;
				}
			}

		}
	}
}


void MAP::release()
{
	_pImgMap = nullptr;
	_pObjectImg = nullptr;

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

void MAP::render(HDC hdc)
{
	for (int j = 0; j < _nTileCountY; j++)
	{
		for (int i = 0; i < _nTileCountX; i++)
		{
			_vvMap[j][i]->render(hdc);
		}
	}
}

void MAP::update()
{

}

void MAP::drawMap(HDC hdc)
{
	for (int j = 0; j < _nTileCountY; j++)
	{
		for (int i = 0; i < _nTileCountX; i++)
		{
			_vvMap[j][i]->renderBackGround(hdc);
		}
	}
}



bool MAP::getObjectPos(vector<vector<int>>& _vvTileIndex, TILE::E_OBJECT object)
{
	for (int j = 0; j < _nTileCountY; j++)
	{
		for (int i = 0; i < _nTileCountX; i++)
		{
			if (_vvMap[j][i]->getObject() == object)
			{
				vector<int> vPos;
				vPos.resize(2);
				vPos[0] = _vvMap[j][i]->getRectTile().left + (_vvMap[j][i]->getRectTile().right - _vvMap[j][i]->getRectTile().left) / 2;
				vPos[1] = _vvMap[j][i]->getRectTile().top + (_vvMap[j][i]->getRectTile().bottom - _vvMap[j][i]->getRectTile().top) / 2;
				_vvTileIndex.push_back(vPos);
				_vvMap[j][i]->setObject(TILE::E_OBJECT::E_NONE);
				return true;
			}
		}
	}

	return false;
}


void MAP::deleteObject()
{
	for (int j = 0; j < _nTileCountY; j++)
	{
		for (int i = 0; i < _nTileCountX; i++)
		{
			_vvMap[j][i]->setObject(TILE::E_OBJECT::E_NONE);
		}
	}
}

void MAP::readjust()
{
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
					if (_vvMap[j - 1][i]->getTerrian() == TILE::E_TERRIAN::DIRT ||
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
					}
					else if (nFrameX == 12)
					{
						_vvMap[j][i]->settingTile(0, 0, _bIsWall, eTmp, TILE::E_OBJECT::E_NONE);
					}
					else if (nFrameX == 1 || nFrameX == 2 || nFrameX == 4 || nFrameX == 8)
					{
						_vvMap[j][i]->settingTile(0, 0, _bIsWall, eTmp, TILE::E_OBJECT::E_NONE);
					}
					else if (nFrameX == 0)
					{
						_vvMap[j][i]->settingTile(0, 0, _bIsWall, eTmp, TILE::E_OBJECT::E_NONE);
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


	for (int j = 1; j < _nTileCountY-1; j++)
	{
		for (int i = 1; i < _nTileCountX-1; i++)
		{
			TILE::E_TERRIAN eTerrian = _vvMap[j][i]->getTerrian();
			if (eTerrian == TILE::E_TERRIAN::DIRT)
			{
				int nWater = 0;
				if (_vvMap[j-1][i]->getTerrian() == TILE::E_TERRIAN::WATER)
				{
					nWater++;
				}
				if (_vvMap[j + 1][i]->getTerrian() == TILE::E_TERRIAN::WATER)
				{
					nWater++;
				}
				if (_vvMap[j][i-1]->getTerrian() == TILE::E_TERRIAN::WATER)
				{
					nWater++;
				}
				if (_vvMap[j][i+1]->getTerrian() == TILE::E_TERRIAN::WATER)
				{
					nWater++;
				}

				if (nWater>=1 )
				{
					_vvMap[j][i]->setTerrian(TILE::E_TERRIAN::DIRT_WATER);
				}

			}
		}
	}

}

void MAP::renderMiniMap()
{

}

