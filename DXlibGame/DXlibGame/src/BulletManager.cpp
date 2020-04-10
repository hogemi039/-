/**
* @file   BulletManager.cpp
* @brief  �����o�̒�`
* @auther �ɓ� �L��
* @date   2019/11/12
*/
#include "BulletManager.hpp"
#include "Camera.hpp"
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
		auto bulletPos = temp->GetPosition() - Vector2{-16.f, -16.f};
		auto bulletSize = temp->GetSize() - Vector2{ -16.f, -16.f };
		//�����̍���̊p���Ώۂ̋�`�ɓ�������������
		if ((position.x <= bulletPos.x - 16.f && bulletPos.x - 16.f <= (position.x + size.x)) &&
			(position.y <= bulletPos.y - 16.f && bulletPos.y - 16.f <= (position.y + size.y)))
		{
			temp->SetActive(false);
			bullets_.erase(bullets_.begin() + i);
			return true;
		}
		//�����̉E��̊p���Ώۂ̋�`�ɓ�������������
		else if ((position.x <= (bulletPos.x + bulletSize.x) - 16.f && (bulletPos.x + bulletSize.x) - 16.f <= (position.x + size.x)) &&
			(position.y <= bulletPos.y - 16.f && bulletPos.y - 16.f <= (position.y + size.y)))
		{
			temp->SetActive(false);
			bullets_.erase(bullets_.begin() + i);
			return true;
		}
		//�����̍����̊p���Ώۂ̋�`�ɓ�������������
		else if ((position.x <= bulletPos.x - 16.f && bulletPos.x - 16.f <= (position.x + size.x)) &&
			(position.y <= (bulletPos.y + bulletSize.y) - 16.f && (bulletPos.y + bulletSize.y) - 16.f <= (position.y + size.y)))
		{
			temp->SetActive(false);
			bullets_.erase(bullets_.begin() + i);
			return true;
		}
		//�����̉E���̊p���Ώۂ̋�`�ɓ�������������
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
* @brief �`�揈��
*/
void BulletManager::Render()
{
	for (int i = 0; i < bullets_.size(); i++)
	{
		bullets_.at(i)->Render();
	}
}