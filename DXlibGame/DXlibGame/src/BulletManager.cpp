/**
* @file   BulletManager.cpp
* @brief  メンバの定義
* @auther 伊藤 広樹
* @date   2019/11/12
*/
#include "BulletManager.hpp"

#include <algorithm>

void BulletManager::Shot(Vector2 &position, float &dir)
{
	//for (int i = 0; i < MAX_BULLET; i++)
	{
		//なんか配列外参照（？）おこしてる
		//if (bullets.at(i) == nullptr)
		//{
		bullets.push_back(new Bullet(position, dir));
		//break;
	//}
	}
}

void BulletManager::Update()
{
	//後ろからforを回すのは、消したあと配列はなくなった部分を詰めるので調べたい要素の+1を見てしまう。
	//後ろから調べれば、無くなった部分を詰めても調べたい要素に影響がないため。
	bullets.erase(std::remove_if(bullets.begin(), bullets.end(),
		[](Bullet* bullet) {
			bullet->Update();
			auto bulletPos = bullet->GetPosition();
			return bulletPos.x > 500;
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

void BulletManager::Render()
{
	for (int i = 0; i < bullets.size(); i++)
	{
		bullets.at(i)->Render();
	}
}