/**
* @file   Enemy.hpp
* @brief  “G‚ÌƒNƒ‰ƒX
* @auther ˆÉ“¡ LŽ÷
* @date   2019/11/29
*/
#ifndef ENEMY_HPP
#define ENEMY_HPP
#include "Vector2.hpp"
#include "OBject.hpp"

class Enemy : Object
{
private:
	const float FALLACCELERATION{ 20.0f };
	const float FALLSPEEDLIMIT{ 20.0f };
	Vector2 size = Vector2(32.0f, 32.0f);
	bool isJump_{};
	bool isCollision_{};
	bool active_{};
	void Fall();
	void Move();
public:
	Vector2 moveVector_{};
	float fallSpeed_{};
	Vector2 GetSize()
	{
		return size;
	}
	Vector2 GetPosition()
	{
		return position_;
	}
	bool GetCollisionFlag()
	{
		return isCollision_;
	}
	bool GetActive()
	{
		return active_;
	}
	void SetPosition(Vector2 position)
	{
		this->position_ = position;
	}
	void SetCollisionFlag(bool isCol)
	{
		isCollision_ = isCol;
	}
	void Render();
	void Update();
	void Destroy();
	Enemy();
	~Enemy() = default;
};
#endif