/**
* @file   Player.cpp
* @brief  player�̃����o�֐��̒�`
* @auther �ɓ� �L��
* @date   2019/10/13
*/
#include "Player.hpp"

#define DEBUG


/**
* @brief �R���X�g���N�^
*/
Player::Player()
{
	bulletmanager_ = new BulletManager();
	handle_ = DxLib::LoadGraph("resource/image/purun.png");
	playerDir_ = Right;
}

Player::~Player()
{
	delete bulletmanager_; 
}

/**
* @brief ����������
*/
void Player::Init()
{
	position_ = Vector2(16.0f, 0.0f);
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
			int x = position_.x - GROUND_IMAGE_SIZE / 2;
			int y = (position_.y - GROUND_IMAGE_SIZE / 2) / GROUND_IMAGE_SIZE;

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
		else
		{
			//�������̃A�^��
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
	//���n���Ă�Ƃ�
	else
	{
		int x = position_.x - GROUND_IMAGE_SIZE / 2;
		int y = ((position_.y + 32) - GROUND_IMAGE_SIZE / 2) / GROUND_IMAGE_SIZE;
		//������if����������Ă����̂Ńo�O���Ă��i���E�ǂ��炩�������Ă��Ȃ���Ε����Ă锻��ɂȂ��Ă�������j
		//���E�ǂ�������n���Ă��Ȃ���Ε����Ă锻��ɂȂ�
		if (!GetMapState(x / GROUND_IMAGE_SIZE, y) && !GetMapState((x + (GROUND_IMAGE_SIZE - 1)) / GROUND_IMAGE_SIZE, y))
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
		int x = position_.x - GROUND_IMAGE_SIZE / 2;
		int y = position_.y - GROUND_IMAGE_SIZE / 2;
		//���W���T�C�Y�Ŋ���ƃ^�C���̔ԍ����o��
		//�摜�̏�̉E�p
		if (GetMapState((x + (GROUND_IMAGE_SIZE - 1)) / GROUND_IMAGE_SIZE, y / GROUND_IMAGE_SIZE))
		{
			//�摜�̃T�C�Y���|����ƍ��W���o��
			position_.x = x / GROUND_IMAGE_SIZE * GROUND_IMAGE_SIZE + GROUND_IMAGE_SIZE / 2;
		}
		//�摜�̉��̉E�p
		else if (GetMapState((x + (GROUND_IMAGE_SIZE - 1)) / GROUND_IMAGE_SIZE, (y + (GROUND_IMAGE_SIZE - 1)) / GROUND_IMAGE_SIZE))
		{
			position_.x = x / GROUND_IMAGE_SIZE * GROUND_IMAGE_SIZE + GROUND_IMAGE_SIZE / 2;
		}
		//�摜�̏�̍��p
		else if (GetMapState(x / GROUND_IMAGE_SIZE, y / GROUND_IMAGE_SIZE))
		{
			position_.x = (x / GROUND_IMAGE_SIZE + 1) * GROUND_IMAGE_SIZE + GROUND_IMAGE_SIZE / 2;
		}
		//�摜�̉��̍��p
		else if (GetMapState(x / GROUND_IMAGE_SIZE, (y + (GROUND_IMAGE_SIZE - 1)) / GROUND_IMAGE_SIZE))
		{
			position_.x = (x / GROUND_IMAGE_SIZE + 1) * GROUND_IMAGE_SIZE + GROUND_IMAGE_SIZE / 2;
		}
	}
}

/**
* @brief �`�揈��
*/
void Player::Render()
{
	DxLib::DrawRotaGraph(static_cast<int>(position_.x), static_cast<int>(position_.y)   //���W
		, 1                                                                             //�g�嗦
		, 0																			    //��]
		, handle_                                                                       //�摜�f�[�^
		, true                                                                          //�����x��L���ɂ��邩
		, (playerDir_ == DIR::Left) ? TRUE : FALSE);                                    //���E�����L���ɂ��邩
	bulletmanager_->Render();

#ifdef DEBUG
	DxLib::DrawCircle(position_.x, position_.y, 2, GetColor(255, 100, 255), 1);
	DxLib::DrawBox(position_.x - 32 / 2, position_.y - 32 / 2, position_.x + 32 / 2, position_.y + 32 / 2, GetColor(255, 255, 255), 0);
#endif
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
		bulletmanager_->Shot(position_, playerDir_);
	}
	bulletmanager_->Update();
	//�G�����݂��Ă��Ȃ��Ƃ��ɓ����蔻�������
	if (isTargetActive_ == false)
	{
		return;
	}
	{
		//�G�̍��W�ƃT�C�Y������
		bulletmanager_->SetTargetPosition(targetPosition_);
		bulletmanager_->SetTargetSize(targetSize_);
		auto pos = bulletmanager_->GetTargetPosition();
		auto size = bulletmanager_->GetTargetSize();
		//�e�ƓG�̓����蔻��
		isBulletCollision_ = bulletmanager_->Collision(pos, size);
	}
}