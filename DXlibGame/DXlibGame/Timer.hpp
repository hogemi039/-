#ifndef DEF_TIMER_HPP
#define DEF_TIMER_HPP

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
		delta_time = (current - prev) / 1000.0f;
		prev = current;
	}
	inline static float delta_time;
};
#endif
