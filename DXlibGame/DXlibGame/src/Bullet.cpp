/**
* @file   Bullet.cpp
* @brief  メンバ関数の定義
* @auther 伊藤 広樹
* @date   2019/10/23
*/
#include "Bullet.hpp"

/**
* @brief コンストラクタ
* @param position 弾を撃ったオブジェクトの座標
* @param dir 弾を撃ったオブジェクトの向き
*/
Bullet::Bullet(const Vector2 position, const float dir)
{
	handle_ = DxLib::LoadGraph("resource/Bullet.png");
	this->position_ = position;
	this->moveVector_ = Vector2(dir, 0);
}

/**
* @brief 座標を返すゲッター
*/
Vector2& Bullet::GetPosition()
{
	return position_;
}

/**
* @brief 移動処理
*/
void Bullet::Move()
{
	position_ += moveVector_ * SPEED;
}

/**
* @brief 描画処理
*/
void Bullet::Render()
{
	DxLib::DrawGraph(static_cast<int>(position_.x), static_cast<int>(position_.y), handle_, true);
}

/**
* @brief 更新処理
*/
void Bullet::Update()
{
	Move();
}