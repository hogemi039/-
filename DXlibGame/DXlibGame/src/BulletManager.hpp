/**
* @file   BulletManager.hpp
* @brief  BulletÇÃä«óùÉNÉâÉX
* @auther à…ì° çLé˜
* @date   2019/11/10
*/
#ifndef BULLETMANAGER_HPP
#define BULLETMANAGER_HPP
#include "Bullet.hpp"
#include <vector>

class BulletManager
{
private:
	const float DELAY{ 0.2f };
	const int MAX_BULLET{ 3 };
	bool isCollision_{};
	Vector2 targetPosition_{};
	Vector2 targetSize_{};
	std::vector<Bullet*> bullets_;
public:
	void SetTargetPosition(Vector2 targetPos)
	{
		targetPosition_ = targetPos;
	}
	void SetTargetSize(Vector2 targetSize)
	{
		targetSize_ = targetSize;
	}
	void SetCollisionFlag(bool isCol)
	{
		isCollision_ = isCol;
	}
	Vector2 GetTargetPosition()
	{
		return targetPosition_;
	}
	Vector2 GetTargetSize()
	{
		return targetSize_;
	}
	bool GetCollisionFlag()
	{
		return isCollision_;
	}
	bool Collision(Vector2, Vector2);
	void Shot(const Vector2, const float);
	void Update();
	void Render();
	BulletManager() = default;
	~BulletManager() = default;
};
#endif