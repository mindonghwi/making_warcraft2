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
