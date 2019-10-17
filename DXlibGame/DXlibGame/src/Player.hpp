/*
* @file   Player.hpp
* @brief  player‚Ìƒƒ“ƒo‚ğéŒ¾
* @auther ˆÉ“¡ L÷
* @date   2019/10/13
*/
#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Vector2.hpp"


class Player
{
private:
	const float left{ -1.0f };
	const float right{ 1.0f };
	const float speed_Limit{ 7.0f };
	const float fall_Acceleration{ 20.0f };
	int handle{};
	float speed{};
	float fall_Speed{};
public:
	bool jump_flag;
	Vector2 position{};
	Vector2 move_Vector{};
	Player()
	{
		speed = 5.0f;
		fall_Speed = 0.0f;
	}
	void Init();
	void Draw();
	void Update();
	void Move(float);
	void Fall();
};
#endif
