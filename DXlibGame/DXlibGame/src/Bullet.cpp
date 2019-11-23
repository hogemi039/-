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
	handle_ = DxLib::LoadGraph("resource/Bullet.png");
	this->position_ = position;
	this->moveVector_ = Vector2(dir, 0);
}

/**
* @brief ���W��Ԃ��Q�b�^�[
*/
Vector2& Bullet::GetPosition()
{
	return position_;
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
	DxLib::DrawGraph(static_cast<int>(position_.x), static_cast<int>(position_.y), handle_, true);
}

/**
* @brief �X�V����
*/
void Bullet::Update()
{
	Move();
}