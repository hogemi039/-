/**
* @file   BulletManager.hpp
* @brief  Bullet�̊Ǘ��N���X
* @auther �ɓ� �L��
* @date   2019/11/10
*/
#ifndef BULLETMANAGER_HPP
#define BULLETMANAGER_HPP
#include "Bullet.hpp"
#include <vector>

class BulletManager
{
private:
	const int MAX_BULLET = 3;
	std::vector<Bullet*> bullets;
public:
	void Shot(Vector2&, Vector2&);
	void Update();
	BulletManager() = default;
	~BulletManager() = default;
};
#endif