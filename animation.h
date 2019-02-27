#pragma once
#include <vector>
#include "stdafx.h"

//typedef void(*CALLBACK_FUNCTION)(void);
//typedef void(*CALLBACK_FUNCTION_PARAMETER)(void*);

//void* ���� : � ���µ� �� ����ų���ִ�(�Ű������� �� �� �������ִ�)
//		���� : � �������� ���ø� �ؾ��Ѵ�.	


typedef function<void(void)> CALLBACK_FUNCTION;
typedef function<void(void*)> CALLBACK_FUNCTION_PARAMETER;

class animation
{
public:
	typedef vector<POINT>	vFrameList;	//�������ε��� 
	typedef vector<int>		vPlayList;	//�÷����ε���

private:
	int			_frameNum;		//�ִϸ��̼� ������ ����
	vFrameList	_frameList;		//������ ����Ʈ
	vPlayList	_playList;		//�÷��� ����Ʈ

	int _frameWidth;			//������ ����ũ��
	int _frameHeight;			//������ ����ũ��

	BOOL _loop;					//�ִϸ��̼� ��������

	float _frameUpdateSec;		//������ ���Žð�
	float _elapsedSec;			//����ð�

	int	 _nowPlayIndex;		//���� �÷��� �ε���
	BOOL _play;					//�ִϸ��̼� �������

	void*						_obj;
	CALLBACK_FUNCTION			_callbackFunction;
	CALLBACK_FUNCTION_PARAMETER _callbackFunctionParameter;

	BOOL	_isClickRender;	//�̰��� Ŭ�� ���� �Դϴ�.
	int		_clickVariable;

	BOOL	_isFixedRender;
	int		_fixedFrame;
public:
	animation();
	~animation();

	//       �̹�����ü����ũ�� ��ü����ũ��  �������Ӱ���ũ�� �������Ӽ���ũ��
	HRESULT init(int totalW, int totalH, int frameW, int frameH);
	void release();

	//����Ʈ �ִϸ��̼�
	void setDefPlayFrame(BOOL reverse = FALSE, BOOL loop = FALSE);
	void setDefPlayFrame(BOOL reverse, BOOL loop, CALLBACK_FUNCTION cbFunction);
	void setDefPlayFrame(BOOL reverse, BOOL loop, CALLBACK_FUNCTION_PARAMETER cbFunction, void* obj);


	//�迭�� ��� �ִϸ��̼� ���
	void setPlayFrame(int* playArr, int arrLen, BOOL loop = FALSE);
	void setPlayFrame(int* playArr, int arrLen, BOOL loop, CALLBACK_FUNCTION cbFunction);
	void setPlayFrame(int* playArr, int arrLen, BOOL loop, CALLBACK_FUNCTION_PARAMETER cbFunction, void* obj);

	//���� �ִϸ��̼� ���
	void setPlayFrame(int start, int end, BOOL reverse = FALSE, BOOL loop = FALSE);
	void setPlayFrame(int start, int end, BOOL reverse, BOOL loop, CALLBACK_FUNCTION cbFunction);
	void setPlayFrame(int start, int end, BOOL reverse, BOOL loop, CALLBACK_FUNCTION_PARAMETER cbFunction, void* obj);

	//�迭 ��� ����
	void setPlayFrame(int* playArr, int arrLen, BOOL loop, int loopCount);
	void setPlayFrame(int* playArr, int arrLen, BOOL loop, int loopCount, CALLBACK_FUNCTION cbFunction);
	void setPlayFrame(int* playArr, int arrLen, BOOL loop, int loopCount, CALLBACK_FUNCTION_PARAMETER cbFunction, void* obj);

	//�ִϸ��̼� ������ ����ӵ� ����
	void setFPS(int framePerSec);

	//������
	void frameUpdate(float elapsedTime);
	void frameClickUpdate();
	void frameFixedFrame();

	void start();		//���
	void stop();		//����
	void pause();		//�Ͻ�����
	void resume();		//�ٽ����

	inline BOOL isPlay() { return _play; }
	inline POINT getFramePos() { return _frameList[_playList[_nowPlayIndex]]; }
	inline int getFrameWidth() { return _frameWidth; }
	inline int getFrameHeight() { return _frameHeight; }

	inline int getFramePlayingCount() { return _nowPlayIndex; }
	inline int getFrameMaxCount() { return static_cast<int>(_playList.size()); }

	inline void setClickRender(BOOL isClickRender) { _isClickRender = isClickRender; }
	inline BOOL	getIsClickRender() { return _isClickRender; }

	inline void setClickVariable(int variable) { _clickVariable = variable; }

	inline void setFixedRender(BOOL isFixedRender) { _isFixedRender = isFixedRender; }
	inline BOOL	getIsFixedRender() { return _isFixedRender; }
	inline void setFixedFrame(int fixedFrame) {_fixedFrame = fixedFrame;}
};
