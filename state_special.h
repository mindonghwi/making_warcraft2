#pragma once
#include "stdafx.h"
#include "state.h"

//스페셜은 각기 따로 있는 것들을 처리할 것이다.
//마법사라면 마법들이 여기에 들어 올 것이다.
//일군들의 채집도 여기로 올것이다.
class STATE_SPECIAL : public STATE
{
private:


public:
	STATE_SPECIAL();
	~STATE_SPECIAL();

	virtual void start()	override;
	virtual void update()	override;

};