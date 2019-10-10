#ifndef DEF_PLAYER_HPP
#define DEF_PLAYER_HPP

#include "Vector2.hpp"


class Player
{
public:
	const float left{ -1.0f };
	const float right{ 1.0f };
	const float speed_Limit{ 7.0f };
	const float fall_Acceleration{ 5.0f };
	int handle{};
	float speed{ 5.0f };
	float fall_Speed{ 0.0f };
	Vector2<float> position{};
	Vector2<float> move_Vector{};
	void Init();
	void Draw();
	void Update();
	void Move(float);
	void Fall();
	Vector2<float> GetPos() { return position; }
};
#endif