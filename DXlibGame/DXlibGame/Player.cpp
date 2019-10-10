#include "DxLib.h"
#include "Player.hpp"
#include "Timer.hpp"

void Player::Init()
{
	//画像を読み込み
	handle = DxLib::LoadGraph("purun.png");  
	position = Vector2{ 0.f, 0.f };
}

void Player::Move(float dir)
{
	move_Vector.x += speed * dir;
	position += move_Vector;
}

void Player::Fall()
{
	fall_Speed += fall_Acceleration * Time::delta_time;
	if (fall_Speed > 5.0f) 
	{
		fall_Speed = 5.0f;
	}
	move_Vector.y += fall_Speed;
	position.y += move_Vector.y;
}

void Player::Draw()
{
	//画像を表示
	DxLib::DrawGraph(static_cast<int>(position.x), static_cast<int>(position.y), handle, true);  
}

void Player::Update()
{
	Draw();
	//移動量をリセット
	move_Vector = Vector2{ 0.0f, 0.0f };
	Fall();
	if (CheckHitKey(KEY_INPUT_LEFT))
	{
		Move(left);
	}
 	else if (CheckHitKey(KEY_INPUT_RIGHT))
	{
		Move(right);
	}
}