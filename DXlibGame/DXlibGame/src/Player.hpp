/**
* @file   Player.hpp
* @brief  playerÇÃÉÅÉìÉoÇêÈåæ
* @auther à…ì° çLé˜
* @date   2019/10/13
*/
#ifndef PLAYER_HPP
#define PLAYER_HPP
#include "DxLib.h"
#include "Input.hpp"
#include "Object.hpp"
#include "BulletManager.hpp"
#include "Timer.hpp"
#include "Map.hpp"

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
	const float FALLSPEEDLIMIT{ 20.0f };
	const float SPEED{ 3.0f };
	float jumpForce_{ -7.5f };
	BulletManager *bulletmanager_{};
	Vector2 targetPosition_{};
	Vector2 targetSize_{};
	Vector2 size_{ 16.0f, 16.0f };
	bool isBulletCollision_{};
	bool isTargetActive_{};
	bool active_{};
	void Fall();
	void Jump();
	void Move(float);
public:
	Vector2 moveVector_{};
	float fallSpeed_{};
	float playerDir_{};
	bool isJump_{};
	Vector2 GetPosition()
	{
		return position_;
	}
	Vector2 GetTargetPosition()
	{
		return targetPosition_;
	}
	Vector2 GetTargetSize()
	{
		return targetSize_;
	}
	Vector2 GetSize()
	{
		return size_;
	}
	bool GetCollisionFlag()
	{
		return isBulletCollision_;
	}
	bool GetActive()
	{
		return active_;
	}
	void SetTargetPosition(Vector2 targetpos)
	{
		targetPosition_ = targetpos;
	}
	void SetTargetSize(Vector2 targetsize)
	{
		targetSize_ = targetsize;
	}
	void SetTargetActive(bool target)
	{
		isTargetActive_ = target;
	}
	void SetActive(bool active)
	{
		active_ = active;
	}
	void Init();
	void Render();
	void Update();
	void Collision(Vector2, Vector2);
	Player();
	~Player();
};
#endif
