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
	handle_ = DxLib::LoadGraph("resource/purun.png");
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
	//if (isJump_)
	{
		fallSpeed_ += FALLACCELERATION * Time::deltaTime;
		if (fallSpeed_ > FALLSPEEDLIMIT)
		{
			fallSpeed_ = FALLSPEEDLIMIT;
		}
	}
	/*else
	{
		fallSpeed_ = 0.f;
	}*/
	moveVector_.y += fallSpeed_;
	position_.y += moveVector_.y;
}

void Enemy::Move()
{

}

void Enemy::Render()
{
	DxLib::DrawGraph(static_cast<int>(position_.x), static_cast<int>(position_.y), handle_, true);
}

void Enemy::Update()
{
	moveVector_ = Vector2(0.f, 0.f);
	Fall();
	Move();
}