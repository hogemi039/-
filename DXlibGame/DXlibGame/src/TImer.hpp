/**
* @file   Timer.cpp
* @brief  1�t���[���Ɋ|���鎞�Ԃ��v�Z����N���X
* @auther �ɓ� �L��
* @date   2019/10/06
*/
#ifndef TIMER_HPP
#define TIMER_HPP

#include <DxLib.h>

class Time
{
	inline static int prev;
public:
	static void Init()
	{
		prev = GetNowCount();
	}
	static void Update()
	{
		int current = GetNowCount();
		delta_Time = (current - prev) / 1000.0f;
		prev = current;
	}
	inline static float delta_Time;
};
#endif