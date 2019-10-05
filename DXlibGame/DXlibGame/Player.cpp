#include "DxLib.h"
#include "Player.hpp"

void Player::Init()
{
	handle = DxLib::LoadGraph("purun.png");  //�摜��ǂݍ���
	position_ = Vector2(0.f, 0.f);
}

void Player::Move(float dir)
{
	//moveVector_ = Vector2(0.f, 0.f);  //�ړ��ʂ����Z�b�g
	position_.x += dir;
	
}

void Player::Draw()
{
	DxLib::DrawGraph(position_.x, position_.y, handle, true);  //�摜��\��
}

void Player::Update()
{
	Draw();
	if (CheckHitKey(KEY_INPUT_LEFT) == TRUE)
	{
		Move(left);
	}
	else if (CheckHitKey(KEY_INPUT_RIGHT) == TRUE)
	{
		Move(right);
	}
}