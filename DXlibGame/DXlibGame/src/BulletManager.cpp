/**
* @file   BulletManager.cpp 
* @brief  ƒƒ“ƒo‚Ì’è‹`
* @auther ˆÉ“¡ L÷
* @date   2019/11/12
*/
#include "BulletManager.hpp"

void BulletManager::Shot(Vector2 &position, Vector2 &moveVector)
{
	for (int i = 0; i < MAX_BULLET; i++)
	{
		if (bullets.at(i) == nullptr)
		{
			bullets.push_back(new Bullet(position, moveVector));
			break;
		}
	}
}

void BulletManager::Update()
{
	for (int i = 0; i < bullets.size(); i++)
	{
		if (bullets.at(i) == nullptr)
		{
			return;
		}
		bullets.at(i)->Update();
	}
}