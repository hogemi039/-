/**
* @file   BulletManager.cpp
* @brief  メンバの定義
* @auther 伊藤 広樹
* @date   2019/11/12
*/
#include "BulletManager.hpp"
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
		auto bulletPos = temp->GetPosition();
		auto bulletSize = temp->GetSize();
		if ((position.x <= bulletPos.x && bulletPos.x <= (position.x + size.x)) &&
			(position.y <= bulletPos.y && bulletPos.y <= (position.y + size.y)))
		{
			temp->SetActive(false);
			bullets_.erase(bullets_.begin() + i);
			return true;
		}
		else if ((position.x <= (bulletPos.x + bulletSize.x) && (bulletPos.x + bulletSize.x) <= (position.x + size.x)) &&
			(position.y <= bulletPos.y && bulletPos.y <= (position.y + size.y)))
		{
			temp->SetActive(false);
			bullets_.erase(bullets_.begin() + i);
			return true;
		}
		else if ((position.x <= bulletPos.x && bulletPos.x <= (position.x + size.x)) &&
			(position.y <= (bulletPos.y + bulletSize.y) && (bulletPos.y + bulletSize.y) <= (position.y + size.y)))
		{
			temp->SetActive(false);
			bullets_.erase(bullets_.begin() + i);
			return true;
		}
		else if ((position.x <= (bulletPos.x + bulletSize.x) && (bulletPos.x + bulletSize.x) <= (position.x + size.x)) &&
			(position.y <= (bulletPos.y + bulletSize.y) && (bulletPos.y + bulletSize.y) <= (position.y + size.y)))
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
			return bulletPos.x > 1280 || bulletPos.x < 0;
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