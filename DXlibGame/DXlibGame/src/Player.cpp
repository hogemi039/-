﻿/**
* @file   Player.cpp
* @brief  playerのメンバ関数の定義
* @auther 伊藤 広樹
* @date   2019/10/13
*/
#include "Player.hpp"
#include "Camera.hpp"

#define DEBUG


/**
* @brief コンストラクタ
*/
Player::Player()
{
	bulletmanager_ = new BulletManager();
	handle_ = DxLib::LoadGraph("resource/image/purun.png");
	playerDir_ = static_cast<float>(DIR::Right);
	active_ = true;
}

Player::~Player()
{
	delete bulletmanager_;
}

/**
* @brief 初期化処理
*/
void Player::Init()
{
	position_ = Vector2(100.f, -16.f);
#pragma region debug
	control_ = true;
#pragma endregion
}

/**
* @brief 落下処理
*/
void Player::Fall()
{
	if (isJump_)
	{
		fallSpeed_ += FALLACCELERATION * Time::deltaTime;
		if (fallSpeed_ > FALLSPEEDLIMIT)
		{
			fallSpeed_ = FALLSPEEDLIMIT;
		}
		moveVector_.y += fallSpeed_;
		position_.y += moveVector_.y;
	}
	else
	{
		DrawFormatString(0, 50, GetColor(255, 255, 255), "着地");
		fallSpeed_ = 0;
	}

	if (isJump_)
	{
		if (fallSpeed_ < 0)
		{
			//上昇中のアタリ
			int x = static_cast<int>(position_.x - GROUND_IMAGE_SIZE / 2);
			int y = static_cast<int>((position_.y - GROUND_IMAGE_SIZE / 2) / GROUND_IMAGE_SIZE);

			if (GetMapState(x / GROUND_IMAGE_SIZE, y))
			{
				isJump_ = false;
				fallSpeed_ = 0;
				position_.y = static_cast<float>((y + 1) * GROUND_IMAGE_SIZE + GROUND_IMAGE_SIZE / 2);
			}
			else if (GetMapState((x + (GROUND_IMAGE_SIZE - 1)) / GROUND_IMAGE_SIZE, y))
			{
				isJump_ = false;
				fallSpeed_ = 0;
				position_.y = static_cast<float>((y + 1) * GROUND_IMAGE_SIZE + GROUND_IMAGE_SIZE / 2);
			}
		}
		else
		{
			//落下中のアタリ
			int x = static_cast<int>(position_.x - GROUND_IMAGE_SIZE / 2);
			int y = static_cast<int>(((position_.y + (GROUND_IMAGE_SIZE - 1)) - GROUND_IMAGE_SIZE / 2) / GROUND_IMAGE_SIZE);

			if (GetMapState(x / GROUND_IMAGE_SIZE, y))
			{
				isJump_ = false;
				fallSpeed_ = 0;
				position_.y = static_cast<float>((y - 1) * GROUND_IMAGE_SIZE + GROUND_IMAGE_SIZE / 2);
			}
			else if (GetMapState((x + (GROUND_IMAGE_SIZE - 1)) / GROUND_IMAGE_SIZE, y))
			{
				isJump_ = false;
				fallSpeed_ = 0;
				position_.y = static_cast<float>((y - 1) * GROUND_IMAGE_SIZE + GROUND_IMAGE_SIZE / 2);
			}
		}
	}
	//着地してるとき
	else
	{
		int x = static_cast<int>(position_.x - GROUND_IMAGE_SIZE / 2);
		int y = static_cast<int>(((position_.y + 32) - GROUND_IMAGE_SIZE / 2) / GROUND_IMAGE_SIZE);
		//ここのif文が分かれていたのでバグってた（左右どちらかが着いていなければ浮いてる判定になっていたから）
		//左右どちらも着地していなければ浮いてる判定になる
		if (!GetMapState(x / GROUND_IMAGE_SIZE, y) && !GetMapState((x + (GROUND_IMAGE_SIZE - 1)) / GROUND_IMAGE_SIZE, y))
		{
			isJump_ = true;
		}
	}
}

/**
* @brief ジャンプ処理
*/
void Player::Jump()
{
	if (!isJump_ && Input::GetInstance().GetKeyDown(KEY_INPUT_SPACE) && control_ == true)
	{
		isJump_ = true;
		fallSpeed_ = jumpForce_;
	}
}

/**
* @brief playerの左右移動
* @param dir 左(-1)右(1)どちらか入力した値を持っている
*/
void Player::Move(const float dir)
{
	if (control_ == true)
	{
		moveVector_.x += SPEED * dir * Time::deltaTime;
		position_.x += moveVector_.x;
	}
	//横の判定
	{
		int x = static_cast<int>(position_.x - GROUND_IMAGE_SIZE / 2);
		int y = static_cast<int>(position_.y - GROUND_IMAGE_SIZE / 2);
		//座標をサイズで割るとタイルの番号が出る
		//画像の上の右角
		if (GetMapState((x + (GROUND_IMAGE_SIZE - 1)) / GROUND_IMAGE_SIZE, y / GROUND_IMAGE_SIZE))
		{
			//画像のサイズを掛けると座標が出る
			position_.x = static_cast<float>(x / GROUND_IMAGE_SIZE * GROUND_IMAGE_SIZE + GROUND_IMAGE_SIZE / 2);
		}
		//画像の下の右角
		else if (GetMapState((x + (GROUND_IMAGE_SIZE - 1)) / GROUND_IMAGE_SIZE, (y + (GROUND_IMAGE_SIZE - 1)) / GROUND_IMAGE_SIZE))
		{
			position_.x = static_cast<float>(x / GROUND_IMAGE_SIZE * GROUND_IMAGE_SIZE + GROUND_IMAGE_SIZE / 2);
		}
		//画像の上の左角
		else if (GetMapState(x / GROUND_IMAGE_SIZE, y / GROUND_IMAGE_SIZE))
		{
			position_.x = static_cast<float>((x / GROUND_IMAGE_SIZE + 1) * GROUND_IMAGE_SIZE + GROUND_IMAGE_SIZE / 2);
		}
		//画像の下の左角
		else if (GetMapState(x / GROUND_IMAGE_SIZE, (y + (GROUND_IMAGE_SIZE - 1)) / GROUND_IMAGE_SIZE))
		{
			position_.x = static_cast<float>((x / GROUND_IMAGE_SIZE + 1) * GROUND_IMAGE_SIZE + GROUND_IMAGE_SIZE / 2);
		}
	}
}

/**
* @brief ノックバックさせる関数
*/
void Player::KnockBack()
{
	if (control_ == true)
	{
		return;
	}
	knockBackTimer_ = 0.0f;
	knockBackTimer_ += Time::deltaTime;
	if (knockBackTimer_ > 0.5f)
	{
		control_ = true;
		knockBackTimer_ = 0.0f;
		return;
	}
	//向いてる方向の逆方向
	int dir{};
	//敵の座標が16ズレているので調整
	auto d = position_.x - (targetPosition_.x + 16.f);
	dir = d >= 0 ? static_cast<int>(DIR::Right) : static_cast<int>(DIR::Left);
	//knockback
	moveVector_.x += dir * KNOCKBACKSPEED * Time::deltaTime;
	position_.x += moveVector_.x;
}

/**
* @brief 当たり判定の関数
*/
bool Player::Collision(const Vector2 pos, const Vector2 size)
{
	if (active_ == false || isTargetActive_ == false)
	{
		return false;
	}
	//自分の左上の角が対象の矩形に入ったかを見る
	if ((pos.x <= position_.x - 16.f && position_.x - 16.f <= pos.x + size.x + 16.0f) &&
		(pos.y <= position_.y - 16.f && position_.y - 16.f <= pos.y + size.y + 16.0f))
	{
		//Collision function
		DrawFormatString(200, 100, GetColor(255, 255, 255), "自身の左上が当たった");
		return true;
	}
	//自分の右上の角が対象の矩形に入ったかを見る
	else if ((pos.x <= position_.x + size_.x && position_.x + size_.x <= pos.x + size.x + 16.0f) &&
		(pos.y <= position_.y - 16.f && position_.y - 16.f <= pos.y + size.y + 16.0f))
	{
		//Collision function
		DrawFormatString(200, 100, GetColor(255, 255, 255), "自身の右上が当たった");
		return true;
	}
	//自分の左下の角が対象の矩形に入ったかを見る
	else if ((pos.x <= position_.x - 16.f && position_.x - 16.f <= pos.x + size.x + 16.0f) &&
		(pos.y <= position_.y + size_.y && position_.y + size_.y <= pos.y + size.y + 16.0f))
	{
		//Collision function
		DrawFormatString(200, 100, GetColor(255, 255, 255), "自身の左下が当たった");
		return true;
	}
	//自分の右下の角が対象の矩形に入ったかを見る
	else if ((pos.x <= position_.x + size_.x && position_.x + size_.x <= pos.x + size.x + 16.0f) &&
		(pos.y <= position_.y + size_.y && position_.y + size_.y <= pos.y + size.y + 16.0f))
	{
		//Collision function
		DrawFormatString(200, 100, GetColor(255, 255, 255), "自身の右下が当たった");
		return true;
	}
	return false;
}

/**
* @brief 描画処理
*/
void Player::Render()
{
	DxLib::DrawRotaGraph(static_cast<int>(position_.x - Camera::position_.x), static_cast<int>(position_.y - Camera::position_.y)   //座標
		, 1                                                                                                                         //拡大率
		, 0																															//回転
		, handle_																												    //画像データ
		, true																														//透明度を有効にするか
		, (playerDir_ == static_cast<int>(DIR::Left)) ? TRUE : FALSE);																//左右判定を有効にするか
	bulletmanager_->Render();

#ifdef DEBUG
	DxLib::DrawCircle(static_cast<int>(position_.x - Camera::position_.x), static_cast<int>(position_.y - Camera::position_.y), 2, GetColor(255, 100, 255), 1);
	DxLib::DrawBox(static_cast<int>(position_.x - 32 / 2 - Camera::position_.x), static_cast<int>(position_.y - 32 / 2 - Camera::position_.y), static_cast<int>(position_.x + 32 / 2 - Camera::position_.x),
		static_cast<int>(position_.y + 32 / 2 - Camera::position_.y), GetColor(255, 255, 255), 0);
	DxLib::DrawFormatString(400, 0, GetColor(255, 255, 255), "CameraPos:x = %5f, y = %5f", Camera::position_.x, Camera::position_.y);
	DxLib::DrawFormatString(0, 0, GetColor(255, 255, 255), "PlayerPos:x = %5f, y = %5f", position_.x, position_.y);
	DxLib::DrawFormatString(0, 200, GetColor(255, 255, 255), "TargetPos:x = %5f, y = %5f", targetPosition_.x, targetPosition_.y);
#endif
}

/**
* @brief 更新処理
*/
void Player::Update()
{
	//移動量をリセット
	moveVector_ = Vector2(0.0f, 0.0f);
	Fall();
	if (Collision(targetPosition_, targetSize_))
	{
		control_ = false;
	}
	KnockBack();
	//カメラの位置をプレイヤーが画面の真ん中に来るように設定
	Camera::position_.x = position_.x - (1280 / 2);
	Camera::position_.y = position_.y - (720 / 2);
	Jump();
	if (Input::GetInstance().GetKey(KEY_INPUT_LEFT))
	{
		playerDir_ = static_cast<int>(DIR::Left);
		Move(playerDir_);
	}
	else if (Input::GetInstance().GetKey(KEY_INPUT_RIGHT))
	{
		playerDir_ = static_cast<int>(DIR::Right);
		Move(playerDir_);
	}
	if (Input::GetInstance().GetKeyDown(KEY_INPUT_B) && control_ == true)
	{
		bulletmanager_->Shot(position_, playerDir_);
	}
	bulletmanager_->Update();
	//敵が存在していない場合returnする
	if (isTargetActive_ == false)
	{
		return;
	}
	//敵の座標とサイズが入る
	bulletmanager_->SetTargetPosition(targetPosition_);
	bulletmanager_->SetTargetSize(targetSize_);
	//敵の座標と当たり判定のサイズを格納
	auto pos = bulletmanager_->GetTargetPosition();
	auto size = bulletmanager_->GetTargetSize();
	//弾と敵の当たり判定
	isBulletCollision_ = bulletmanager_->Collision(pos, size);
}
