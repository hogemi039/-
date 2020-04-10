/**
* @file   BulletManager.cpp
* @brief  メンバの定義
* @auther 伊藤 広樹
* @date   2019/11/12
*/
#include "BulletManager.hpp"
#include "Camera.hpp"
#include <algorithm>

/**
* @brief 弾を動的生成する処理
* @param position 弾を撃ったオブジェクトの座標
* @param dir 弾を撃ったオブジェクトの向き
*/
void BulletManager::Shot(const Vector2 position, const float dir)
{
	if (bullets_.size() < MAX_BULLET)
	{
		bullets_.push_back(new Bullet(position, dir));
	}
}

bool BulletManager::Collision(Vector2 position = Vector2(0.f,0.f), Vector2 size = Vector2(0.f, 0.f))
{
	for (size_t i = 0; i < bullets_.size(); i++)
	{
		auto temp = bullets_.at(i);
		if (!temp->GetActive())
		{
			continue;
		}
		auto bulletPos = temp->GetPosition() - Vector2{-16.f, -16.f};
		auto bulletSize = temp->GetSize() - Vector2{ -16.f, -16.f };
		//自分の左上の角が対象の矩形に入ったかを見る
		if ((position.x <= bulletPos.x - 16.f && bulletPos.x - 16.f <= (position.x + size.x)) &&
			(position.y <= bulletPos.y - 16.f && bulletPos.y - 16.f <= (position.y + size.y)))
		{
			temp->SetActive(false);
			bullets_.erase(bullets_.begin() + i);
			return true;
		}
		//自分の右上の角が対象の矩形に入ったかを見る
		else if ((position.x <= (bulletPos.x + bulletSize.x) - 16.f && (bulletPos.x + bulletSize.x) - 16.f <= (position.x + size.x)) &&
			(position.y <= bulletPos.y - 16.f && bulletPos.y - 16.f <= (position.y + size.y)))
		{
			temp->SetActive(false);
			bullets_.erase(bullets_.begin() + i);
			return true;
		}
		//自分の左下の角が対象の矩形に入ったかを見る
		else if ((position.x <= bulletPos.x - 16.f && bulletPos.x - 16.f <= (position.x + size.x)) &&
			(position.y <= (bulletPos.y + bulletSize.y) - 16.f && (bulletPos.y + bulletSize.y) - 16.f <= (position.y + size.y)))
		{
			temp->SetActive(false);
			bullets_.erase(bullets_.begin() + i);
			return true;
		}
		//自分の右下の角が対象の矩形に入ったかを見る
		else if ((position.x <= (bulletPos.x + bulletSize.x) - 16.f && (bulletPos.x + bulletSize.x) - 16.f <= (position.x + size.x)) &&
			(position.y <= (bulletPos.y + bulletSize.y) - 16.f && (bulletPos.y + bulletSize.y) - 16.f <= (position.y + size.y)))
		{
			temp->SetActive(false);
			bullets_.erase(bullets_.begin() + i);
			return true;
		}
	}
	return false;
}

/**
* @brief 更新処理
*/
void BulletManager::Update()
{
	//後ろからforを回すのは、消したあと配列はなくなった部分を詰めるので調べたい要素の+1を見てしまう。
	//後ろから調べれば、無くなった部分を詰めても調べたい要素に影響がないため。
	bullets_.erase(std::remove_if(bullets_.begin(), bullets_.end(),
		[](Bullet* bullet)
		{
			bullet->Update();
			auto bulletPos = bullet->GetPosition();
			return bulletPos.x - Camera::position_.x > 1280 || bulletPos.x - Camera::position_.x < 0;
		}),
		bullets_.end());
	/*for (int i = bullets.size() - 1; i >= 0; i--)
	{
		bullets.at(i)->Update();
		auto bulletPos = bullets.at(i)->GetPosition();
		if (bulletPos.x > 500)
		{
			bullets.erase(bullets.begin() + i);
		}
	}*/
}

/**
* @brief 描画処理
*/
void BulletManager::Render()
{
	for (int i = 0; i < bullets_.size(); i++)
	{
		bullets_.at(i)->Render();
	}
}