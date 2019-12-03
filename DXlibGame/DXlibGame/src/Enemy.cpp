/**
* @file   Enemy.cpp
* @brief  ÉNÉâÉXÇÃÉÅÉìÉoä÷êîÇÃíËã`
* @auther à…ì° çLé˜
* @date   2019/11/30
*/
#include "Enemy.hpp"
#include "Timer.hpp"
#include "Map.hpp"

Enemy::Enemy()
{
	position_ = Vector2(150.f, 0.f);
	moveVector_ = Vector2(0.f, 0.f);
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

	//ÉWÉÉÉìÉvíÜ
	if (isJump_)
	{
		//è„è∏íÜ
		if (fallSpeed_ < 0)
		{
			int x = position_.x;
			int y = position_.y;
			//è„ÇÃç∂âEÇå©ÇÈ
			if (GetMapState(x / GROUND_IMAGE_SIZE, y))
			{
				isJump_ = false;
				fallSpeed_ = 0;
				position_.y = (y + 1) * GROUND_IMAGE_SIZE;
			}
			else if (GetMapState((x + 31) / GROUND_IMAGE_SIZE, y))
			{
				isJump_ = false;
				fallSpeed_ = 0;
				position_.y = (y + 1) * GROUND_IMAGE_SIZE;
			}
		}
		//óéâ∫íÜ
		else
		{
			int x = position_.x;
			int y = (position_.y + 31) / GROUND_IMAGE_SIZE;
			///ìríÜÅ`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`
			if (GetMapState(x / GROUND_IMAGE_SIZE, y))
			{
				isJump_ = false;
				fallSpeed_ = 0;
				position_.y = (y - 1) * GROUND_IMAGE_SIZE;
			}
			else if (GetMapState((x + 31) / GROUND_IMAGE_SIZE, y))
			{
				isJump_ = false;
				fallSpeed_ = 0;
				position_.y = (y - 1) * GROUND_IMAGE_SIZE;
			}
		}
	}
	//íÖíníÜ
	else
	{
		int x = position_.x;
		int y = (position_.y + 32) / GROUND_IMAGE_SIZE;
		if (!GetMapState(x, y) && !GetMapState((x + 31) / GROUND_IMAGE_SIZE, y))
		{
			isJump_ = true;
		}

	}
}

void Enemy::Move()
{
	moveVector_.x += 0.5f;
	position_.x += moveVector_.x;
	//â°ÇÃÉAÉ^ÉäîªíË
	{
		int x = position_.x;
		int y = position_.y;
		//è„
		if (GetMapState(x / GROUND_IMAGE_SIZE, y / GROUND_IMAGE_SIZE))
		{
			position_.x = (x / GROUND_IMAGE_SIZE + 1) * GROUND_IMAGE_SIZE;
		}
		else if(GetMapState((x + 31) / GROUND_IMAGE_SIZE, y / GROUND_IMAGE_SIZE))
		{
			position_.x = x / GROUND_IMAGE_SIZE * GROUND_IMAGE_SIZE;
		}
		//â∫
		else if (GetMapState(x / GROUND_IMAGE_SIZE, (y + 31) / GROUND_IMAGE_SIZE))
		{
			position_.x = (x / GROUND_IMAGE_SIZE + 1) * GROUND_IMAGE_SIZE;
		}
		else if (GetMapState((x + 31) / GROUND_IMAGE_SIZE, (y + 31) / GROUND_IMAGE_SIZE))
		{
			position_.x = x / GROUND_IMAGE_SIZE * GROUND_IMAGE_SIZE;
		}
	}
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