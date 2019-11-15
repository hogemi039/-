/**
* @file   Player.cpp
* @brief  playerのメンバ関数の定義
* @auther 伊藤 広樹
* @date   2019/10/13
*/
#include "DxLib.h"
#include "Player.hpp"

/**
* @brief コンストラクタ
*/
Player::Player()
{
	bulletmanager = new BulletManager();
	handle_ = DxLib::LoadGraph("resource/purun.png");
	playerDir = Right;
}

Player::~Player()
{
	delete bulletmanager; 
}

/**
* @brief 初期化処理
*/
void Player::Init()
{
	position_ = Vector2(0.0f, 0.0f);
}

Vector2& Player::GetPosition()
{
	return position_;
}

/**
* @brief 落下処理
*/
void Player::Fall()
{
	if (jumpFlag)
	{
		fallSpeed_ += FALLACCELERATION * Time::deltaTime;
		if (fallSpeed_ > FALLACCELERATION)
		{
			fallSpeed_ = FALLACCELERATION;
		}
		moveVector_.y += fallSpeed_;
		position_.y += moveVector_.y;
	}
	else
	{
		DrawFormatString(0, 50, GetColor(255, 255, 255), "ばーか");
		fallSpeed_ = 0;
	}
}

/**
* @brief ジャンプ処理
*/
void Player::Jump()
{
	if (!jumpFlag && CheckHitKey(KEY_INPUT_SPACE))
	{
  		jumpFlag = true;
		fallSpeed_ = -7.5f;
	}
}

/**
* @brief playerの左右移動
* @param dir 左(-1)右(1)どちらか入力した値を持っている
*/
void Player::Move(float dir)
{
	moveVector_.x += SPEED * dir;
	position_.x += moveVector_.x;
}

/**
* @brief 描画処理
*/
void Player::Render()
{
	DxLib::DrawGraph(static_cast<int>(position_.x), static_cast<int>(position_.y), handle_, true);
	bulletmanager->Render();
}

/**
* @brief 更新処理
*/
void Player::Update()
{
	moveVector_ = Vector2(0.0f, 0.0f);
	Jump();
	Fall();
	if (DxLib::CheckHitKey(KEY_INPUT_LEFT) == 1)
	{
		playerDir = Left;
		Move(playerDir);
	}
	else if (DxLib::CheckHitKey(KEY_INPUT_RIGHT) == 1)
	{
		playerDir = Right;
		Move(playerDir);
	}
	if (CheckHitKey(KEY_INPUT_B) == 1)
	{
		bulletmanager->Shot(position_, playerDir);
	}
	bulletmanager->Update();
}

///**
//* @brief コンストラクタ
//*/
//Player::Player()
//{
//	handle = DxLib::LoadGraph("resource/purun.png");
//	playerDir = Right;
//	speed = 3.0f;
//	fallSpeed = 0.0f;
//}
//
///**
//* @brief 初期化処理
//*/
//void Player::Init()
//{
//	position = Vector2{ 0.f, 0.f };
//}
//
///**
//* @brief playerの左右移動
//* @param dir 左(-1)右(1)どちらか入力した値を持っている
//*/
//void Player::Move(float dir)
//{
//	moveVector.x += speed * dir;
//	position.x += moveVector.x;
//}
//
///**
//* @brief ジャンプ処理
//*/
//void Player::Jump()
//{
//	if (!jumpFlag && CheckHitKey(KEY_INPUT_SPACE))
//	{
//  		jumpFlag = true;
//		fallSpeed = -7.5f;
//	}
//}
//
///**
//* @brief 落下処理
//*/
//void Player::Fall()
//{
//	if (jumpFlag)
//	{
//		fallSpeed += FALLACCELERATION * Time::deltaTime;
//		if (fallSpeed > FALLACCELERATION)
//		{
//			fallSpeed = FALLACCELERATION;
//		}
//		moveVector.y += fallSpeed;
//		position.y += moveVector.y;
//	}
//	else
//	{
//		DrawFormatString(0, 50, GetColor(255, 255, 255), "ばーか");
//		fallSpeed = 0;
//	}
//}
//
///**
//* @brief 描画処理
//*/
//void Player::Render()
//{
//	//下記2行はデバッグ用
//	DxLib::DrawFormatString(0, 100, GetColor(255, 255, 255), "%d", jumpFlag);
//	DxLib::DrawFormatString(0, 0, GetColor(255, 255, 255), "落下速度：%.2f", fallSpeed);
//
//	//画像を表示
//	DxLib::DrawGraph(static_cast<int>(position.x), static_cast<int>(position.y), handle, true);
//}
//
///**
//* @brief 更新処理
//*/
//void Player::Update()
//{
//	//移動量をリセット
//	moveVector = Vector2{ 0.0f, 0.0f };
//	Jump();
//	Fall();
//	if (/*Input::key[KEY_INPUT_LEFT] >= 1*/CheckHitKey(KEY_INPUT_LEFT))
//	{
//		DrawFormatString(200, 0, GetColor(255, 255, 255), "←を入力した!");
//		playerDir = Left;
//		Move(playerDir);
//	}
//	else if (CheckHitKey(KEY_INPUT_RIGHT))
//	{
//		playerDir = Right;
//		Move(playerDir);
//	}
//	if (CheckHitKey(KEY_INPUT_B))
//	{
//		bullet = new Bullet(position.x, position.y);
//		//bullet.CreateBullet(position, playerDir);
//	}
//	bullet->Update();
//	Render();
//}