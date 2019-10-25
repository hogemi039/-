/**
* @file   Player.cpp
* @brief  playerのメンバ関数の定義
* @auther 伊藤 広樹
* @date   2019/10/13
*/
#include "DxLib.h"
#include "Player.hpp"

/**
* @brief 初期化処理
*/
void Player::Init()
{
	//画像を読み込み
	handle = DxLib::LoadGraph("resource/purun.png");
	position = Vector2{ 0.f, 0.f };

	//後々消す
	bullet.Init();
}

/**
* @brief playerの左右移動
* @param dir 左(-1)右(1)どちらか入力した値を持っている
*/
void Player::Move(float dir)
{
	move_Vector.x += speed * dir;
	position.x += move_Vector.x;
}

/**
* @brief ジャンプ処理
*/
void Player::Jump()
{
	if (!jump_Flag && CheckHitKey(KEY_INPUT_SPACE))
	{
  		jump_Flag = true;
		fall_Speed = -7.5f;
	}
}

/**
* @brief 落下処理
*/
void Player::Fall()
{
	if (jump_Flag)
	{
		fall_Speed += FALL_ACCELERATION * Time::delta_Time;
		if (fall_Speed > FALL_ACCELERATION)
		{
			fall_Speed = FALL_ACCELERATION;
		}
		move_Vector.y += fall_Speed;
		position.y += move_Vector.y;
	}
	else
	{
		DrawFormatString(0, 50, GetColor(255, 255, 255), "ばーか");
		fall_Speed = 0;
	}
}

/**
* @brief 描画処理
*/
void Player::Draw()
{
	//下記2行はデバッグ用
	DxLib::DrawFormatString(0, 100, GetColor(255, 255, 255), "%d", jump_Flag);
	DxLib::DrawFormatString(0, 0, GetColor(255, 255, 255), "落下速度：%.2f", fall_Speed);

	//画像を表示
	DxLib::DrawGraph(static_cast<int>(position.x), static_cast<int>(position.y), handle, true);
}

/**
* @brief 更新処理
*/
void Player::Update()
{
	//移動量をリセット
	move_Vector = Vector2{ 0.0f, 0.0f };
	Jump();
	Fall();
	if (CheckHitKey(KEY_INPUT_LEFT))
	{
		player_Dir = DIR::Left;
		Move(player_Dir);
	}
	else if (CheckHitKey(KEY_INPUT_RIGHT))
	{
		player_Dir = DIR::Right;
		Move(player_Dir);
	}
	if (CheckHitKey(KEY_INPUT_B))
	{
		bullet.CreateBullet(position, player_Dir);
	}
	bullet.Update();
	Draw();
}