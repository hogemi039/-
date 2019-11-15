/**
* @file   Bullet.cpp
* @brief  �����o�֐��̒�`
* @auther �ɓ� �L��
* @date   2019/10/23
*/
#include "Bullet.hpp"

Bullet::Bullet(Vector2 &position, float &dir)
{
	handle_ = DxLib::LoadGraph("resource/Bullet.png");
	this->position_ = position;
	this->moveVector_ = Vector2(dir, 0);
}

Vector2& Bullet::GetPosition()
{
	return position_;
}

void Bullet::Move()
{
	position_ += moveVector_ * SPEED;
}

void Bullet::Render()
{
	DxLib::DrawGraph(static_cast<int>(position_.x), static_cast<int>(position_.y), handle_, true);
}

void Bullet::Update()
{
	Move();
	//Render();
}


///**
//* @brief �R���X�g���N�^
//*/
//Bullet::Bullet(float x, float y)
//{
//	handle = DxLib::LoadGraph("resource/Bullet.png");
//	active = false;
//	//origin = Vector2(16.0f, 16.0f);
//	moveVector = Vector2(0.0f, 0.0f);
//	position = Vector2(x, y);
//}
//
///**
//* @brief �e�𐶐�
//* @param pos �v���C���[�̍��W
//* @param dir �v���C���[�̌���
//*/
//void Bullet::CreateBullet(Vector2& pos, float dir)
//{
//	/*if (active != false)
//	{
//		return;
//	}*/
//	active = true;
//	position = pos;
//	moveVector = Vector2(dir, 0.0f);
//	moveVector.Normalize();
//}
//
///**
//* @brief �e�𓮂���
//*/
//void Bullet::Move()
//{
//	position += moveVector * SPEED;
//}
//
///**
//* @brief �`�揈��
//*/
//void Bullet::Render()
//{
//	DxLib::DrawGraph(static_cast<int>(position.x), static_cast<int>(position.y), handle, true);
//}
//
///**
//* @brief �I�u�W�F�N�g������
//*/
////void Bullet::Destroy()
////{
////
////}
//
///**
//* @brief �X�V����
//*/
//void Bullet::Update()
//{
//	if (active == false)
//	{
//		return;
//	}
//	Move();
//	Render();
//	DxLib::DrawFormatString(0, 300, GetColor(255, 255, 255), "x = %f, y = %f", position.x, position.y);
//}