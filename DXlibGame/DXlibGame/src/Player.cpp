/**
* @file   Player.cpp
* @brief  playerのメンバ関数の定義
* @auther 伊藤 広樹
* @date   2019/10/13
*/
#include "Player.hpp"

/**
* @brief コンストラクタ
*/
Player::Player()
{
	bulletmanager = new BulletManager();
	handle_ = DxLib::LoadGraph("resource/purun.png");
	playerDir_ = Right;
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

/**
* @brief 座標を返すゲッター
*/
Vector2 Player::GetPosition()
{
	return position_;
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
			int x = position_.x;
			int y = position_.y / GROUND_IMAGE_SIZE;

			if (GetMapState(x / GROUND_IMAGE_SIZE, y))
			{
				isJump_ = false;
				fallSpeed_ = 0;
				position_.y = (y + 1) * GROUND_IMAGE_SIZE;
			}
			else if (GetMapState((x + 31) / GROUND_IMAGE_SIZE, y))
			{
				isJump_ = false;
				fallSpeed_ = 0;
				position_.y = (y + 1) * GROUND_IMAGE_SIZE;
			}
		}
		else
		{
			//落下中のアタリ
			int x = position_.x;
			int y = (position_.y + 31) / GROUND_IMAGE_SIZE;

			if (GetMapState(x / GROUND_IMAGE_SIZE, y))
			{
				isJump_ = false;
				fallSpeed_ = 0;
				position_.y = (y - 1) * GROUND_IMAGE_SIZE;
			}
			else if (GetMapState((x + 31) / GROUND_IMAGE_SIZE, y))
			{
				isJump_ = false;
				fallSpeed_ = 0;
				position_.y = (y - 1) * GROUND_IMAGE_SIZE;
			}
		}
	}
	//着地してるとき
	else
	{
		int x = position_.x;
		int y = (position_.y + 32) / GROUND_IMAGE_SIZE;
		//ここのif文が分かれていたのでバグってた（左右どちらかが着いていなければ浮いてる判定になっていたから）
		//左右どちらも着地していなければ浮いてる判定になる
		if (!GetMapState(x / GROUND_IMAGE_SIZE, y) && !GetMapState((x + 31) / GROUND_IMAGE_SIZE, y))
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
	if (!isJump_ && Input::GetInstance().GetKeyDown(KEY_INPUT_SPACE))
	{
  		isJump_ = true;
		fallSpeed_ = jumpForce_;
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
	//横の判定
	{
		int x = position_.x;
		int y = position_.y;
		//上の左右角
		if (GetMapState((x + 31) / GROUND_IMAGE_SIZE, y / GROUND_IMAGE_SIZE))
		{
			position_.x = x / GROUND_IMAGE_SIZE * GROUND_IMAGE_SIZE;
		}
		else if (GetMapState(x / GROUND_IMAGE_SIZE, y / GROUND_IMAGE_SIZE))
		{
			position_.x = (x / GROUND_IMAGE_SIZE + 1) * GROUND_IMAGE_SIZE;
		}
		//下の左右角
		else if (GetMapState((x + 31) / GROUND_IMAGE_SIZE, (y + 31) / GROUND_IMAGE_SIZE))
		{
			position_.x = x / GROUND_IMAGE_SIZE * GROUND_IMAGE_SIZE;
		}
		else if (GetMapState(x / GROUND_IMAGE_SIZE, (y + 31) / GROUND_IMAGE_SIZE))
		{
			position_.x = (x / GROUND_IMAGE_SIZE + 1) * GROUND_IMAGE_SIZE;
		}
	}
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
	if (Input::GetInstance().GetKey(KEY_INPUT_LEFT))
	{
		playerDir_ = Left;
		Move(playerDir_);
	}
	else if (Input::GetInstance().GetKey(KEY_INPUT_RIGHT))
	{
		playerDir_ = Right;
		Move(playerDir_);
	}
	if (Input::GetInstance().GetKeyDown(KEY_INPUT_B))
	{
		bulletmanager->Shot(position_, playerDir_);
	}
	bulletmanager->Update();
}