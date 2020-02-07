/**
* @file   Enemy.cpp
* @brief  �N���X�̃����o�֐��̒�`
* @auther �ɓ� �L��
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

	//�W�����v��
	if (isJump_)
	{
		//�㏸��
		if (fallSpeed_ < 0)
		{
			int x = position_.x - GROUND_IMAGE_SIZE / 2;
			int y = position_.y - GROUND_IMAGE_SIZE / 2;
			//��̍��E������
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
		//������
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
	//���n��
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
	//���̃A�^������
	{
		int x = position_.x - GROUND_IMAGE_SIZE / 2;
		int y = position_.y - GROUND_IMAGE_SIZE / 2;
		//��
		if (GetMapState(x / GROUND_IMAGE_SIZE, y / GROUND_IMAGE_SIZE))
		{
			position_.x = (x / GROUND_IMAGE_SIZE + 1) * GROUND_IMAGE_SIZE + GROUND_IMAGE_SIZE / 2;
		}
		else if(GetMapState((x + (GROUND_IMAGE_SIZE - 1)) / GROUND_IMAGE_SIZE, y / GROUND_IMAGE_SIZE))
		{
			position_.x = x / GROUND_IMAGE_SIZE * GROUND_IMAGE_SIZE + GROUND_IMAGE_SIZE / 2;
		}
		//��
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
	DxLib::DrawRotaGraph(static_cast<int>(position_.x - Camera::position_.x), static_cast<int>(position_.y - Camera::position_.y)   //���W
		, 1                                                                             //�g�嗦
		, 0																			    //��]
		, handle_                                                                       //�摜�f�[�^
		, true                                                                          //�����x��L���ɂ��邩
		, (moveVector_.x < 0) ? TRUE : FALSE);                                          //���E�����L���ɂ��邩

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