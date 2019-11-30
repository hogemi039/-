/**
* @file   Enemy.cpp
* @brief  クラスのメンバ関数の定義
* @auther 伊藤 広樹
* @date   2019/11/30
*/
#include "Enemy.hpp"
#include "Timer.hpp"

Enemy::Enemy()
{
	position_ = Vector2(150.f, 0.f);
	moveVector_ = Vector2(0.f, 0.f);
	dir_ = Left;
	fallSpeed_ = 0.f;
}

Vector2 Enemy::GetPosition()
{
	return position_;
}

void Enemy::SetPosition(Vector2 position)
{
	this->position_ = position;
}

void Enemy::Fall()
{
	if (isGround_)
	{
		fallSpeed_ += FALLACCELERATION * Time::deltaTime;
		if (fallSpeed_ > FALLSPEEDLIMIT)
		{
			fallSpeed_ = FALLSPEEDLIMIT;
		}
	}
	moveVector_.y = fallSpeed_;
}

void Enemy::Move()
{

}

void Enemy::Render()
{

}

void Enemy::Update()
{
	moveVector_ = Vector2(0.f, 0.f);
	Fall();
	Move();
}