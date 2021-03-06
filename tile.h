#pragma once
#include "stdafx.h"

//0 이면 벽
//139 이면 길

enum {PASS = 139};

class TILE
{
public:
	enum class E_TERRIAN
	{
		NONE = 0,
		GROUND,
		WATER,			//물만 있다
		DIRT,			//더러움만 있다
		DIRT_WATER,
		DIRT_GROUND,
		WALL,
		ROCK,
		TREE,			//그 나무 배인 걸로 처리함
		MAX
	};
	//물을 찍으면 더 더 물 더 더
	//더티일때는 주변을 본다 상하좌우 풀이나 물을 탐색

	enum class E_TRIBUTE
	{
		E_NONE = 0,
		E_HUMAN,
		E_ORC,
		E_MAX
	};

	enum class E_OBJECT
	{
		E_NONE = 0,
		E_TREE,
		E_GOLDMINE,
		E_OILPATCH,
		E_BUILDING,
		E_UNIT,
		E_MAX
	};

	enum class E_UNIT
	{
		E_GROUND = 0,
		E_FLY,
		E_MAX
	};
	//시작위치는 골드마인에서 레프트 탑 의 왼쪽 타일에 피전한마리 출현
	//오브젝트는 TRIBUTE와 연관이 있다
	//벽 돌 나무 골드마인 오일패치는 종족none 빌딩과 유닛은 휴먼과 오크에 영향을 받는다.
	//종족none에 해당하는 오브젝트가 있는 땅은 DIRT가 된다.
	//left top 오브젝트가 타일 몇개를 먹으면 lefttop 기준으로 먹자
	//DIRT는 위에 유닛만 가능하다
	//비행유닛은 제외
public:
	TILE();
	~TILE();

private:
	int				_nAroundWall;	//주변벽값을 가진다.
	
	bool			_bIsWall;		//벽인지 아닌지 아직 2개 밖에 없어서 가능한 방식 나중에는 바꾸어야한다 테리안으로
	TILE::E_TERRIAN	_eTerrian;		//2가지가 아니라면 terrian을 사용해서 찾아야 한다.
	
	image*			_pImage;		//이미지를 담을 것이다.
	int				_nFrameX;		//프레임 넘버 X
	int				_nFrameY;		//프레임 넘버 Y
	RECT			_rcTile;		//사각형
	int				_nNodeIndex;	//몇번째 노드인지 넣는 함수
	TILE::E_OBJECT	_eObject;		//무슨 오브젝트가 있는지
	image*			_pObjectImage;	//오브젝트 이미지 none이면 아무것도 안그림

	RECT			_rcCameraLimit;	//클러핑용

	bool			_bIsObjectLoadCheck;	//로드시 오브젝트생성을 체크했는지 

public:
	void	setttingObject();
	void	settingTerrian();

public:
	//초기 초기화
	void	init(int nTileLeft, int nTileTop, int nTileSize,image* pImg,int nNodeIndex);
	
	//그려주는 함수
	void	render(HDC hdc);
	void	renderBackGround(HDC hdc);

	//메모리 해제
	void	release();

	//타일 세팅
	void	settingTile(int nFrameX, int nFrameY, bool bIsWall,TILE::E_TERRIAN eTerrian ,E_OBJECT object);
	
	//타일 세팅이 끝나면 재조정한 것을 받아온다 클릭을 멈추는 순간에 업데이트를 한번에 해서 받아온다.
	void	readjustWall(int nAroundWall, int nFrameX, int nFrameY);

	string	makeSaveString();

	void	move(int vertical,int horizontal);

	void	extendLimitRect(int nOffset);

public:
	//setter
	inline	void	setAroundWall(int nAroundWall)		{ _nAroundWall = nAroundWall; }
	inline	void	setIsWall(bool isWall)				{ _bIsWall = isWall; }
	inline	void	setImg(image* pImg)					{ _pImage = pImg; }
	inline	void	setFrameX(int nFrameX)				{ _nFrameX = nFrameX; }
	inline	void	setFrameY(int nFrameY)				{ _nFrameY = nFrameY; }
	inline	void	setRectTile(RECT& rcTile)			{ _rcTile = rcTile;}
	inline	void	setNodeIndex(int nIndex)			{ _nNodeIndex = nIndex; }
	inline	void	setLimitRect(RECT rc)				{ _rcCameraLimit = rc; }
	inline	void	setTerrian(TILE::E_TERRIAN eTerrian)	{ _eTerrian = eTerrian; }
	inline	void	setObject(TILE::E_OBJECT eObject)	{ _eObject = eObject; }
	inline	void	setRectTile(int nLeft, int nTop, int nWidth, int nHeight) { _rcTile = RectMake(nLeft, nTop, nWidth, nHeight); }
	inline	void	setIsObjectLoadCheck(bool bIsCheck) { _bIsObjectLoadCheck = bIsCheck; }

	//getter
	inline	int				getAroundWall() { return _nAroundWall; }
	inline	bool			getIsWall()		{ return _bIsWall; }
	inline	image*			getimg()		{ return _pImage; }
	inline	int				getFrameX()		{ return _nFrameX; }
	inline	int				setFrameY()		{ return _nFrameY; }
	inline	RECT			getRectTile()	{ return _rcTile; }
	inline	int				getNodeIndex()	{ return _nNodeIndex; }
	inline	TILE::E_TERRIAN	getTerrian()	{return _eTerrian; }
	inline	TILE::E_OBJECT	getObject()		{ return _eObject; }
	inline	bool			getIsObjectLoadCheck() {return _bIsObjectLoadCheck; }

};