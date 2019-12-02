/**
* @file   Player.cpp
* @brief  player�̃����o�֐��̒�`
* @auther �ɓ� �L��
* @date   2019/10/13
*/
#include "Player.hpp"

/**
* @brief �R���X�g���N�^
*/
Player::Player()
{
	bulletmanager = new BulletManager();
	handle_ = DxLib::LoadGraph("resource/purun.png");
	playerDir_ = Right;
}

Player::~Player()
{
	delete bulletmanager; 
}

/**
* @brief ����������
*/
void Player::Init()
{
	position_ = Vector2(0.0f, 0.0f);
}

/**
* @brief ���W��Ԃ��Q�b�^�[
*/
Vector2 Player::GetPosition()
{
	return position_;
}

/**
* @brief ��������
*/
void Player::Fall()
{
	if (isJump_)
	{
		fallSpeed_ += FALLACCELERATION * Time::deltaTime;
		if (fallSpeed_ > FALLSPEEDLIMIT)
		{
			fallSpeed_ = FALLSPEEDLIMIT;
		}
		moveVector_.y += fallSpeed_;
		position_.y += moveVector_.y;
	}
	else
	{
		DrawFormatString(0, 50, GetColor(255, 255, 255), "���n");
		fallSpeed_ = 0;
	}

	if (isJump_)
	{
		if (fallSpeed_ < 0)
		{
			//�㏸���̃A�^��
			int x = position_.x;
			int y = position_.y / GROUND_IMAGE_SIZE;

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
		else
		{
			//�������̃A�^��
			int x = position_.x;
			int y = (position_.y + 31) / GROUND_IMAGE_SIZE;

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
	//���n���Ă�Ƃ�
	else
	{
		int x = position_.x;
		int y = (position_.y + 32) / GROUND_IMAGE_SIZE;
		//������if����������Ă����̂Ńo�O���Ă��i���E�ǂ��炩�������Ă��Ȃ���Ε����Ă锻��ɂȂ��Ă�������j
		//���E�ǂ�������n���Ă��Ȃ���Ε����Ă锻��ɂȂ�
		if (!GetMapState(x / GROUND_IMAGE_SIZE, y) && !GetMapState((x + 31) / GROUND_IMAGE_SIZE, y))
		{
			isJump_ = true;
		}
	}
}

/**
* @brief �W�����v����
*/
void Player::Jump()
{
	if (!isJump_ && Input::GetInstance().GetKeyDown(KEY_INPUT_SPACE))
	{
  		isJump_ = true;
		fallSpeed_ = jumpForce_;
	}
}

/**
* @brief player�̍��E�ړ�
* @param dir ��(-1)�E(1)�ǂ��炩���͂����l�������Ă���
*/
void Player::Move(float dir)
{
	moveVector_.x += SPEED * dir;
	position_.x += moveVector_.x;
	//���̔���
	{
		int x = position_.x;
		int y = position_.y;
		//��̍��E�p
		if (GetMapState((x + 31) / GROUND_IMAGE_SIZE, y / GROUND_IMAGE_SIZE))
		{
			position_.x = x / GROUND_IMAGE_SIZE * GROUND_IMAGE_SIZE;
		}
		else if (GetMapState(x / GROUND_IMAGE_SIZE, y / GROUND_IMAGE_SIZE))
		{
			position_.x = (x / GROUND_IMAGE_SIZE + 1) * GROUND_IMAGE_SIZE;
		}
		//���̍��E�p
		else if (GetMapState((x + 31) / GROUND_IMAGE_SIZE, (y + 31) / GROUND_IMAGE_SIZE))
		{
			position_.x = x / GROUND_IMAGE_SIZE * GROUND_IMAGE_SIZE;
		}
		else if (GetMapState(x / GROUND_IMAGE_SIZE, (y + 31) / GROUND_IMAGE_SIZE))
		{
			position_.x = (x / GROUND_IMAGE_SIZE + 1) * GROUND_IMAGE_SIZE;
		}
	}
}

/**
* @brief �`�揈��
*/
void Player::Render()
{
	DxLib::DrawGraph(static_cast<int>(position_.x), static_cast<int>(position_.y), handle_, true);
	bulletmanager->Render();
}

/**
* @brief �X�V����
*/
void Player::Update()
{
	moveVector_ = Vector2(0.0f, 0.0f);
	Jump();
	Fall();
	if (Input::GetInstance().GetKey(KEY_INPUT_LEFT))
	{
		playerDir_ = Left;
		Move(playerDir_);
	}
	else if (Input::GetInstance().GetKey(KEY_INPUT_RIGHT))
	{
		playerDir_ = Right;
		Move(playerDir_);
	}
	if (Input::GetInstance().GetKeyDown(KEY_INPUT_B))
	{
		bulletmanager->Shot(position_, playerDir_);
	}
	bulletmanager->Update();
}