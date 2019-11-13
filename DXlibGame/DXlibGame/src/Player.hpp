/**
* @file   Player.hpp
* @brief  playerÇÃÉÅÉìÉoÇêÈåæ
* @auther à…ì° çLé˜
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
	Vector2 moveVector_{};
	float playerDir{};
	bool jumpFlag{};
	void Init();
	void Render();
	void Update();
	Player();
	~Player() = default;
};
//#include "Vector2.hpp"
//#include "Timer.hpp"
//#include "Bullet.hpp"
//#include "Input.hpp"
//
//class Player
//{
//private:
//	//const float left{ -1.0f };
//	//const float right{ 1.0f };
//	enum DIR
//	{
//		Left = -1,
//		Right = 1
//	};
//	const float SPEEDLIMIT{ 7.0f };
//	const float FALLACCELERATION{ 20.0f };
//	int handle{};
//	float speed{};
//	float fallSpeed{};
//	Bullet *bullet;
//	void Render();
//	void Fall();
//	void Jump();
//	void Move(float);
//public:
//	float playerDir{};
//	bool jumpFlag{};
//	Vector2 position{};
//	Vector2 moveVector{};
//	Player();
//	void Init();
//	void Update();
//};
#endif
