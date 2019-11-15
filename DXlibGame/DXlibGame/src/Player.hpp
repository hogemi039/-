/**
* @file   Player.hpp
* @brief  player‚Ìƒƒ“ƒo‚ğéŒ¾
* @auther ˆÉ“¡ L÷
* @date   2019/10/13
*/
#ifndef PLAYER_HPP
#define PLAYER_HPP
#include "Object.hpp"
#include "BulletManager.hpp"
#include "Timer.hpp"

class Player : public Object
{
private:
	enum DIR
	{
		Left = -1,
		Right = 1
	};
	const float SPEEDLIMIT{ 7.0f };
	const float FALLACCELERATION{ 20.0f };
	const float SPEED{ 3.0f };
	float fallSpeed_{};
	BulletManager *bulletmanager{};
	void Fall();
	void Jump();
	void Move(float);
public:
	Vector2& GetPosition();
	Vector2 moveVector_{};
	float playerDir{};
	bool jumpFlag{};
	void Init();
	void Render();
	void Update();
	Player();
	~Player();
};
#endif
