/*
* @file   Player.cpp
* @brief  player�̃����o�֐��̒�`
* @auther �ɓ� �L��
* @date   2019/10/13
*/
#include "DxLib.h"
#include "Player.hpp"
#include "Timer.hpp"

/*
* @brief ����������
*/
void Player::Init()
{
	//�摜��ǂݍ���
	handle = DxLib::LoadGraph("resource/purun.png");
	position = Vector2{ 0.f, 0.f };
}

/*
* @brief player�̍��E�ړ�
* @param dir ��(-1)�E(1)�ǂ��炩���͂����l�������Ă���
*/
void Player::Move(float dir)
{
	move_Vector.x += speed * dir;
	position.x += move_Vector.x;
}

/*
* @brief �W�����v����
*/
void Player::Jump()
{
	if (!jump_flag && CheckHitKey(KEY_INPUT_SPACE))
	{
  		jump_flag = true;
		fall_Speed = -7.5f;
	}
}

/*
* @brief ��������
*/
void Player::Fall()
{
	if (jump_flag)
	{
		fall_Speed += fall_Acceleration * Time::delta_Time;
		if (fall_Speed > fall_Acceleration)
		{
			fall_Speed = fall_Acceleration;
		}
		move_Vector.y += fall_Speed;
		position.y += move_Vector.y;
	}
	else
	{
		DrawFormatString(0, 50, GetColor(255, 255, 255), "�΁[��");
		fall_Speed = 0;
	}
}

/*
* @brief �`�揈��
*/
void Player::Draw()
{
	DxLib::DrawFormatString(0, 100, GetColor(255, 255, 255), "%d", jump_flag);
	DxLib::DrawFormatString(0, 0, GetColor(255, 255, 255), "�������x�F%.2f", fall_Speed);
	//�摜��\��
	DxLib::DrawGraph(static_cast<int>(position.x), static_cast<int>(position.y), handle, true);
}

/*
* @brief �X�V����
*/
void Player::Update()
{
	//�ړ��ʂ����Z�b�g
	move_Vector = Vector2{ 0.0f, 0.0f };
	Jump();
	Fall();
	if (CheckHitKey(KEY_INPUT_LEFT))
	{
		Move(left);
	}
	else if (CheckHitKey(KEY_INPUT_RIGHT))
	{
		Move(right);
	}
	Draw();
}