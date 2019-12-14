/**
* @file   Bullet.cpp
* @brief  �����o�֐��̒�`
* @auther �ɓ� �L��
* @date   2019/10/23
*/
#include "Bullet.hpp"

/**
* @brief �R���X�g���N�^
* @param position �e���������I�u�W�F�N�g�̍��W
* @param dir �e���������I�u�W�F�N�g�̌���
*/
Bullet::Bullet(const Vector2 position, const float dir)
{
	handle_ = DxLib::LoadGraph("resource/image/Bullet.png");
	position_ = position;
	moveVector_ = Vector2(dir, 0);
	moveVector_.Normalize();
	active_ = true;
}

/**
* @brief �ړ�����
*/
void Bullet::Move()
{
	position_ += moveVector_ * SPEED;
}

/**
* @brief �`�揈��
*/
void Bullet::Render()
{
	DxLib::DrawRotaGraph(static_cast<int>(position_.x), static_cast<int>(position_.y)   //���W
		, 1                                                                             //�g�嗦
		, 0																			    //��]
		, handle_                                                                       //�摜�f�[�^
		, true                                                                          //�����x��L���ɂ��邩
		, (moveVector_.x == -1)? TRUE : FALSE);                                         //���E�����L���ɂ��邩
}

/**
* @brief �X�V����
*/
void Bullet::Update()
{
	Move();
}