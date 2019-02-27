#pragma once
#include "stdafx.h"

//0 �̸� ��
//139 �̸� ��

enum {PASS = 139};

class TILE
{
public:
	enum class E_TERRIAN
	{
		NONE = 0,
		GROUND,
		WATER,			//���� �ִ�
		DIRT,			//������ �ִ�
		DIRT_WATER,
		DIRT_GROUND,
		WALL,
		ROCK,
		TREE,			//�� ���� ���� �ɷ� ó����
		MAX
	};
	//���� ������ �� �� �� �� ��
	//��Ƽ�϶��� �ֺ��� ���� �����¿� Ǯ�̳� ���� Ž��
	enum class BRIGHTNESS
	{
		NONE = 0,
		LIGHT,
		DARK,
		MAX
	};

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
	//������ġ�� ��帶�ο��� ����Ʈ ž �� ���� Ÿ�Ͽ� �����Ѹ��� ����
	//������Ʈ�� TRIBUTE�� ������ �ִ�
	//�� �� ���� ��帶�� ������ġ�� ����none ������ ������ �޸հ� ��ũ�� ������ �޴´�.
	//����none�� �ش��ϴ� ������Ʈ�� �ִ� ���� DIRT�� �ȴ�.
	//left top ������Ʈ�� Ÿ�� ��� ������ lefttop �������� ����
	//DIRT�� ���� ���ָ� �����ϴ�
	//���������� ����
public:
	TILE();
	~TILE();

private:
	int				_nAroundWall;	//�ֺ������� ������.
	
	bool			_bIsWall;		//������ �ƴ��� ���� 2�� �ۿ� ��� ������ ��� ���߿��� �ٲپ���Ѵ� �׸�������
	TILE::E_TERRIAN	_eTerrian;		//2������ �ƴ϶�� terrian�� ����ؼ� ã�ƾ� �Ѵ�.
	
	image*			_pImage;		//�̹����� ���� ���̴�.
	int				_nFrameX;		//������ �ѹ� X
	int				_nFrameY;		//������ �ѹ� Y
	RECT			_rcTile;		//�簢��
	int				_nNodeIndex;	//���° ������� �ִ� �Լ�
	TILE::E_OBJECT	_eObject;		//���� ������Ʈ�� �ִ���
	image*			_pObjectImage;	//������Ʈ �̹��� none�̸� �ƹ��͵� �ȱ׸�

	RECT			_rcCameraLimit;	//Ŭ���ο�

public:
	void	setttingObject();
	void	settingTerrian();

public:
	//�ʱ� �ʱ�ȭ
	void	init(int nTileLeft, int nTileTop, int nTileSize,image* pImg,int nNodeIndex);
	
	//�׷��ִ� �Լ�
	void	render(HDC hdc);

	//�޸� ����
	void	release();

	//Ÿ�� ����
	void	settingTile(int nFrameX, int nFrameY, bool bIsWall,TILE::E_TERRIAN eTerrian ,E_OBJECT object);
	
	//Ÿ�� ������ ������ �������� ���� �޾ƿ´� Ŭ���� ���ߴ� ������ ������Ʈ�� �ѹ��� �ؼ� �޾ƿ´�.
	void	readjustWall(int nAroundWall, int nFrameX, int nFrameY);

	string	makeSaveString();

	void	move(int vertical,int horizontal);

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


};