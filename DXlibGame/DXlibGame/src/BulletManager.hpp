/**
* @file   BulletManager.hpp
* @brief  Bullet‚ÌŠÇ—ƒNƒ‰ƒX
* @auther ˆÉ“¡ L÷
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
	std::vector<Bullet*> bullets;
public:
	void Shot(const Vector2, const float);
	void Update();
	void Render();
	BulletManager() = default;
	~BulletManager() = default;
};
#endif