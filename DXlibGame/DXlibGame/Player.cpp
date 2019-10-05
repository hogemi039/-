#include "DxLib.h"
#include "Player.hpp"

void Player::Init()
{
	handle = DxLib::LoadGraph("purun.png");  //画像を読み込み
	position_ = Vector2(0.f, 0.f);
}

void Player::Move(float dir)
{
	//moveVector_ = Vector2(0.f, 0.f);  //移動量をリセット
	position_.x += dir;
	
}

void Player::Draw()
{
	DxLib::DrawGraph(position_.x, position_.y, handle, true);  //画像を表示
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