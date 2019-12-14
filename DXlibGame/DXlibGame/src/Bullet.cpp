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
	handle_ = DxLib::LoadGraph("resource/image/Bullet.png");
	position_ = position;
	moveVector_ = Vector2(dir, 0);
	moveVector_.Normalize();
	active_ = true;
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
	DxLib::DrawRotaGraph(static_cast<int>(position_.x), static_cast<int>(position_.y)   //座標
		, 1                                                                             //拡大率
		, 0																			    //回転
		, handle_                                                                       //画像データ
		, true                                                                          //透明度を有効にするか
		, (moveVector_.x == -1)? TRUE : FALSE);                                         //左右判定を有効にするか
}

/**
* @brief 更新処理
*/
void Bullet::Update()
{
	Move();
}