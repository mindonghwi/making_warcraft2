#pragma once
#include "singletonBase.h"
#include <map>

class image;
class animation;


class keyAniManager : public singletonBase<keyAniManager>
{
private:
	typedef map<string, animation*>				arrAnimation;
	typedef map<string, animation*>::iterator	iterAnimation;

	typedef map<string, arrAnimation*>					arObjectAnimation;
	typedef map<string, arrAnimation*>::iterator		iterObjectAnimation;

private:

	arObjectAnimation _mmTotalAnimation;

public:
	keyAniManager();
	~keyAniManager();

	HRESULT init();
	void release();
	void update();
	void render();

	//오브젝트를 추가해준다 오브젝트를 추가하지 않으면 아무것도 못쓴다.
	void addObject(string strObjectKey);
	//오브젝트를 삭제한다
	void deleteObject(string strObjectKey);
	void deleteAllObject();

	//디폴트 애니메이션
	void addDefaultFrameAnimation(string strObjectKey, string animationKeyName, const char* imageKeyName, int fps, bool reverse, bool loop);
	
	void addDefaultFrameAnimation(string strObjectKey, string animationKeyName, const char* imageKeyName, int fps, bool reverse, bool loop, CALLBACK_FUNCTION cbFunction);
	void addDefaultFrameAnimation(string strObjectKey, string animationKeyName, const char* imageKeyName, int fps, bool reverse, bool loop, CALLBACK_FUNCTION_PARAMETER cbFunction, void* obj);

	//배열 애니메이션
	void addArrayFrameAnimation(string strObjectKey, string animationKeyName, const char* imageKeyName, int* arr, int arrLen, int fps, bool loop);
	void addArrayFrameAnimation(string strObjectKey, string animationKeyName, const char* imageKeyName, int* arr, int arrLen, int fps, bool loop, CALLBACK_FUNCTION cbFunction);
	void addArrayFrameAnimation(string strObjectKey, string animationKeyName, const char* imageKeyName, int* arr, int arrLen, int fps, bool loop, CALLBACK_FUNCTION_PARAMETER cbFunction, void* obj);

	//배열 구간 애니메이션
	void addArrayCoordinateFrameAnimation(string strObjectKey, string animationKeyName, const char* imageKeyName, int* arr, int arrLen, int fps, bool loop, int loopCount);
	void addArrayCoordinateFrameAnimation(string strObjectKey, string animationKeyName, const char* imageKeyName, int* arr, int arrLen, int fps, bool loop, int loopCount, CALLBACK_FUNCTION cbFunction);
	void addArrayCoordinateFrameAnimation(string strObjectKey, string animationKeyName, const char* imageKeyName, int* arr, int arrLen, int fps, bool loop, int loopCount, CALLBACK_FUNCTION_PARAMETER cbFunction, void* obj);



	//구간 애니메이션
	void addCoordinateFrameAnimation(string strObjectKey, string animationKeyName, const char* imageKeyName, int start, int end, int fps, bool reverse, bool loop);
	void addCoordinateFrameAnimation(string strObjectKey, string animationKeyName, const char* imageKeyName, int start, int end, int fps, bool reverse, bool loop, CALLBACK_FUNCTION cbFunction);
	void addCoordinateFrameAnimation(string strObjectKey, string animationKeyName, const char* imageKeyName, int start, int end, int fps, bool reverse, bool loop, CALLBACK_FUNCTION_PARAMETER cbFunction, void* obj);

	void start(string strObjectKey, string animationKeyName);
	void stop(string strObjectKey, string animationKeyName);
	void pause(string strObjectKey, string animationKeyName);
	void resume(string strObjectKey, string animationKeyName);

	animation* findAnimation(string strObjectKey, string animationKeyName);
};

