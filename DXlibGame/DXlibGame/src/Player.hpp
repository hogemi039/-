/**
* @file   Player.hpp
* @brief  player‚Ìƒƒ“ƒo‚ğéŒ¾
* @auther ˆÉ“¡ L÷
* @date   2019/10/13
*/
#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Vector2.hpp"
#include "Timer.hpp"
#include "Bullet.hpp"

class Player
{
private:
	//const float left{ -1.0f };
	//const float right{ 1.0f };
	enum DIR
	{
		Left = -1,
		Right = 1
	};
	const float SPEED_LIMIT{ 7.0f };
	const float FALL_ACCELERATION{ 20.0f };
	int handle{};
	float speed{};
	float fall_Speed{};
	Bullet bullet;
	void Draw();
	void Fall();
	void Jump();
	void Move(float);
public:
	float player_Dir{};
	bool jump_Flag{};
	Vector2 position{};
	Vector2 move_Vector{};
	Player()
	{
		player_Dir = DIR::Right;
		speed = 3.0f;
		fall_Speed = 0.0f;
	}
	void Init();
	void Update();
};
#endif
