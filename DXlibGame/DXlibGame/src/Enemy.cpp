/**
* @file   Enemy.cpp
* @brief  �N���X�̃����o�֐��̒�`
* @auther �ɓ� �L��
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

	//�W�����v��
	if (isJump_)
	{
		//�㏸��
		if (fallSpeed_ < 0)
		{
			int x = position_.x;
			int y = position_.y;
			//��̍��E������
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
		//������
		else
		{
			int x = position_.x;
			int y = (position_.y + 31) / GROUND_IMAGE_SIZE;
			///�r���`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`
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
	//���n��
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
	//���̃A�^������
	{
		int x = position_.x;
		int y = position_.y;
		//��
		if (GetMapState(x / GROUND_IMAGE_SIZE, y / GROUND_IMAGE_SIZE))
		{
			position_.x = (x / GROUND_IMAGE_SIZE + 1) * GROUND_IMAGE_SIZE;
		}
		else if(GetMapState((x + 31) / GROUND_IMAGE_SIZE, y / GROUND_IMAGE_SIZE))
		{
			position_.x = x / GROUND_IMAGE_SIZE * GROUND_IMAGE_SIZE;
		}
		//��
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