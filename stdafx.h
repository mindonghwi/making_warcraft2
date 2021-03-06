// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 또는 프로젝트 관련 포함 파일이
// 들어 있는 포함 파일입니다.
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용은 Windows 헤더에서 제외합니다.
// Windows 헤더 파일:
#include <windows.h>

// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <iostream>
#include <functional>
#include <queue>
#include <list>
#include <algorithm>
#include <stack>
using namespace std;

#include "commonMacroFunction.h"
#include "randomFunction.h"
#include "keyManager.h"
#include "imageManager.h"
#include "timeManager.h"
#include "soundManager.h"
#include "sceneManager.h"
#include "keyAniManager.h"
#include "utils.h"
#include "aStar.h"
#include "FrameWork.h"
#include "effectManager.h"
using namespace BRAVO_UTIL;

//====================================
// ## 18.11.20 ## - 디파인문 -
//====================================

#define WINNAME (LPCTSTR)(TEXT("MDH_WarCraft2"))
#define WINSTARTX 0		//윈도우 시작 X좌표 
#define WINSTARTY 0		//윈도우 시작 Y좌표
#define WINSIZEX 1024		//윈도우 가로크기
#define WINSIZEY 768				//윈도우 세로크기
#define WINSTYLE WS_CAPTION | WS_SYSMENU


#define RND randomFunction::getSingleton()
#define KEYMANAGER keyManager::getSingleton()
#define IMAGEMANAGER imageManager::getSingleton()
#define TIMEMANAGER timeManager::getSingleton()
#define SOUNDMANAGER soundManager::getSingleton()
#define SCENEMANAGER sceneManager::getSingleton()
#define KEYANIMANAGER keyAniManager::getSingleton()
#define EFFECTMGR EFFECTMANAGER::getSingleton()



// TODO: 프로그램에 필요한 추가 헤더는 여기에서 참조합니다.

#define SAFE_DELETE(p) {if(p) { delete(p); (p) = NULL; }}
#define SAFE_RELEASE(p) {if(p) {(p)->release(); }}
#define SAFE_DELETE_ARRAY(p) {if(p) { delete[](p); (p) = NULL;}}

extern HINSTANCE _hInstance;
extern HWND _hWnd;
extern POINT _ptMouse;
extern BOOL _leftButtonDown;



enum { TILESIZE = 32 };
enum { TILECOUNTX = 128 };
enum { TILECOUNTY = 128 };


enum E_MAPTILEPOS
{
	E_NONE = 0x00,
	E_TOP = 0x01,
	E_BOTTOM = 0x02,
	E_LEFT = 0x04,
	E_RIGHT = 0x08
};

enum class E_DIAGONAL
{
	E_NONE = 0,
	E_NORTH_WEST = 1,
	E_NORTH_EAST = 2,
	E_SOUTH_WEST = 3,
	E_SOUTH_EAST = 4
};


enum class E_RESOURCE
{
	E_GOLD = 0,
	E_TREE,
	E_OIL,
	E_MAX
};

enum class E_BUILDS
{
	E_TOWN = 0,
	E_KEEP,
	E_CASTLE,
	E_FARM,
	E_BARRACKS,
	E_LUMBER_MILL,
	E_BLACK_SMITH,
	E_SCOUT_TOWER,
	E_GUARD_TOWER,
	E_CANNON_TOWER,
	E_SHIPYARD,		//조선소
	E_FOUNDRY,		//주조소
	E_OIL_REFINERY,
	E_OIL_PLATFORM,
	E_GNOMISH_INVENTOR,	//노움발명소
	E_STABLE,
	E_CHURCH,
	E_MAGE_TOWER,
	E_GRYPHON_AVIARY,
	E_MAX
};