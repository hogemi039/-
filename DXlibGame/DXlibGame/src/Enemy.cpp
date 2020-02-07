/**
* @file   Enemy.cpp
* @brief  クラスのメンバ関数の定義
* @auther 伊藤 広樹
* @date   2019/11/30
*/
#include "Enemy.hpp"
#include "Timer.hpp"
#include "Map.hpp"
#include "Camera.hpp"

#define DEBUG

Enemy::Enemy()
{
	position_ = Vector2(150.f, 0.f);
	moveVector_ = Vector2(0.f, 0.f);
	fallSpeed_ = 0.f;
	isCollision_ = false;
	active_ = true;
	handle_ = DxLib::LoadGraph("resource/image/purun.png");
}

void Enemy::Fall()
{
	if (isJump_)
	{
		fallSpeed_ += FALLACCELERATION * Time::deltaTime;
		if (fallSpeed_ > FALLSPEEDLIMIT)
		{
			fallSpeed_ = FALLSPEEDLIMIT;
		}
	}
	else
	{
		fallSpeed_ = 0.f;
	}
	moveVector_.y += fallSpeed_;
	position_.y += moveVector_.y;

	//ジャンプ中
	if (isJump_)
	{
		//上昇中
		if (fallSpeed_ < 0)
		{
			int x = position_.x - GROUND_IMAGE_SIZE / 2;
			int y = position_.y - GROUND_IMAGE_SIZE / 2;
			//上の左右を見る
			if (GetMapState(x / GROUND_IMAGE_SIZE, y))
			{
				isJump_ = false;
				fallSpeed_ = 0;
				position_.y = (y + 1) * GROUND_IMAGE_SIZE + GROUND_IMAGE_SIZE / 2;
			}
			else if (GetMapState((x + (GROUND_IMAGE_SIZE - 1)) / GROUND_IMAGE_SIZE, y))
			{
				isJump_ = false;
				fallSpeed_ = 0;
				position_.y = (y + 1) * GROUND_IMAGE_SIZE + GROUND_IMAGE_SIZE / 2;
			}
		}
		//落下中
		else
		{
			int x = position_.x - GROUND_IMAGE_SIZE / 2;
			int y = ((position_.y + (GROUND_IMAGE_SIZE - 1)) - GROUND_IMAGE_SIZE / 2) / GROUND_IMAGE_SIZE;
			if (GetMapState(x / GROUND_IMAGE_SIZE, y))
			{
				isJump_ = false;
				fallSpeed_ = 0;
				position_.y = (y - 1) * GROUND_IMAGE_SIZE + GROUND_IMAGE_SIZE / 2;
			}
			else if (GetMapState((x + (GROUND_IMAGE_SIZE - 1)) / GROUND_IMAGE_SIZE, y))
			{
				isJump_ = false;
				fallSpeed_ = 0;
				position_.y = (y - 1) * GROUND_IMAGE_SIZE + GROUND_IMAGE_SIZE / 2;
			}
		}
	}
	//着地中
	else
	{
		int x = position_.x - GROUND_IMAGE_SIZE / 2;
		int y = ((position_.y + 32) - GROUND_IMAGE_SIZE / 2) / GROUND_IMAGE_SIZE;
		if (!GetMapState(x / GROUND_IMAGE_SIZE, y) && !GetMapState((x + (GROUND_IMAGE_SIZE - 1)) / GROUND_IMAGE_SIZE, y))
		{
			isJump_ = true;
		}
	}
}

void Enemy::Move()
{
	moveVector_.x += 1.f;
	position_.x += moveVector_.x;
	//横のアタリ判定
	{
		int x = position_.x - GROUND_IMAGE_SIZE / 2;
		int y = position_.y - GROUND_IMAGE_SIZE / 2;
		//上
		if (GetMapState(x / GROUND_IMAGE_SIZE, y / GROUND_IMAGE_SIZE))
		{
			position_.x = (x / GROUND_IMAGE_SIZE + 1) * GROUND_IMAGE_SIZE + GROUND_IMAGE_SIZE / 2;
		}
		else if(GetMapState((x + (GROUND_IMAGE_SIZE - 1)) / GROUND_IMAGE_SIZE, y / GROUND_IMAGE_SIZE))
		{
			position_.x = x / GROUND_IMAGE_SIZE * GROUND_IMAGE_SIZE + GROUND_IMAGE_SIZE / 2;
		}
		//下
		else if (GetMapState(x / GROUND_IMAGE_SIZE, (y + (GROUND_IMAGE_SIZE - 1)) / GROUND_IMAGE_SIZE))
		{
			position_.x = (x / GROUND_IMAGE_SIZE + 1) * GROUND_IMAGE_SIZE + GROUND_IMAGE_SIZE / 2;
		}
		else if (GetMapState((x + (GROUND_IMAGE_SIZE - 1)) / GROUND_IMAGE_SIZE, (y + (GROUND_IMAGE_SIZE - 1)) / GROUND_IMAGE_SIZE))
		{
			position_.x = x / GROUND_IMAGE_SIZE * GROUND_IMAGE_SIZE + GROUND_IMAGE_SIZE / 2;
		}
	}
}

void Enemy::Render()
{
	if (active_ == false)
	{
		return;
	}
	DxLib::DrawRotaGraph(static_cast<int>(position_.x - Camera::position_.x), static_cast<int>(position_.y - Camera::position_.y)   //座標
		, 1                                                                             //拡大率
		, 0																			    //回転
		, handle_                                                                       //画像データ
		, true                                                                          //透明度を有効にするか
		, (moveVector_.x < 0) ? TRUE : FALSE);                                          //左右判定を有効にするか

#ifdef DEBUG
	DxLib::DrawCircle(position_.x - Camera::position_.x, position_.y - Camera::position_.y, 2, GetColor(255, 100, 255), 1);
	DxLib::DrawBox(position_.x - 32 / 2 - Camera::position_.x, position_.y - 32 / 2 - Camera::position_.y, position_.x + 32 / 2 - Camera::position_.x,
	position_.y + 32 / 2 - Camera::position_.y, GetColor(255, 255, 255), 0); 
	DxLib::DrawFormatString(0, 15, GetColor(255, 255, 255), "EnemyPos:x = %5f, y = %5f", position_.x, position_.y);
#endif
}

void Enemy::Update()
{
	if (isCollision_ == true)
	{
		Destroy();
	}
	if (active_ == true)
	{
		moveVector_ = Vector2(0.f, 0.f);
		Fall();
		Move();
	}
}

void Enemy::Destroy()
{
	active_ = false;
}