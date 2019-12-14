/**
* @file   BulletManager.cpp
* @brief  �����o�̒�`
* @auther �ɓ� �L��
* @date   2019/11/12
*/
#include "BulletManager.hpp"
#include <algorithm>

/**
* @brief �e�𓮓I�������鏈��
* @param position �e���������I�u�W�F�N�g�̍��W
* @param dir �e���������I�u�W�F�N�g�̌���
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
* @brief �X�V����
*/
void BulletManager::Update()
{
	//��납��for���񂷂̂́A���������Ɣz��͂Ȃ��Ȃ����������l�߂�̂Œ��ׂ����v�f��+1�����Ă��܂��B
	//��납�璲�ׂ�΁A�����Ȃ����������l�߂Ă����ׂ����v�f�ɉe�����Ȃ����߁B
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
* @brief �`�揈��
*/
void BulletManager::Render()
{
	for (int i = 0; i < bullets_.size(); i++)
	{
		bullets_.at(i)->Render();
	}
}