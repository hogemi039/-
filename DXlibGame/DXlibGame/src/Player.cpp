/*
* @file   Player.cpp
* @brief  playerのメンバ関数の定義
* @auther 伊藤 広樹
* @date   2019/10/13
*/
#include "DxLib.h"
#include "Player.hpp"
#include "Timer.hpp"

/*
* @brief 初期化処理
*/
void Player::Init()
{
	//画像を読み込み
	handle = DxLib::LoadGraph("resource/purun.png");
	position = Vector2{ 0.f, 0.f };
}

/*
* @brief playerの左右移動
* @param dir 左(-1)右(1)どちらか入力した値を持っている
*/
void Player::Move(float dir)
{
	move_Vector.x += speed * dir;
	position.x += move_Vector.x;
}

/*
* @brief 落下処理
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
		fall_Speed = 0;
	}
}

/*
* @brief 描画処理
*/
void Player::Draw()
{
	//画像を表示
	DxLib::DrawGraph(static_cast<int>(position.x), static_cast<int>(position.y), handle, true);
}

/*
* @brief 更新処理
*/
void Player::Update()
{
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
	Draw();
}