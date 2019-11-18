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
void BulletManager::Shot(Vector2 &position, float &dir)
{
	if(bullets.size() < MAX_BULLET)
	{
		bullets.push_back(new Bullet(position, dir));
	}
}

/**
* @brief 更新処理
*/
void BulletManager::Update()
{
	//後ろからforを回すのは、消したあと配列はなくなった部分を詰めるので調べたい要素の+1を見てしまう。
	//後ろから調べれば、無くなった部分を詰めても調べたい要素に影響がないため。
	bullets.erase(std::remove_if(bullets.begin(), bullets.end(),
		[](Bullet* bullet) {
			bullet->Update();
			auto bulletPos = bullet->GetPosition();
			return bulletPos.x > 500 || bulletPos.x < 0;
		}),
		bullets.end());
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
	for (int i = 0; i < bullets.size(); i++)
	{
		bullets.at(i)->Render();
	}
}