/**
* @file   BulletManager.cpp
* @brief  �����o�̒�`
* @auther �ɓ� �L��
* @date   2019/11/12
*/
#include "BulletManager.hpp"

#include <algorithm>

void BulletManager::Shot(Vector2 &position, float &dir)
{
	//for (int i = 0; i < MAX_BULLET; i++)
	{
		//�Ȃ񂩔z��O�Q�Ɓi�H�j�������Ă�
		//if (bullets.at(i) == nullptr)
		//{
		bullets.push_back(new Bullet(position, dir));
		//break;
	//}
	}
}

void BulletManager::Update()
{
	//��납��for���񂷂̂́A���������Ɣz��͂Ȃ��Ȃ����������l�߂�̂Œ��ׂ����v�f��+1�����Ă��܂��B
	//��납�璲�ׂ�΁A�����Ȃ����������l�߂Ă����ׂ����v�f�ɉe�����Ȃ����߁B
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