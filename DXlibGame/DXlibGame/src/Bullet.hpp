/**
* @file   Bullet.hpp
* @brief  �e�ۂ̃N���X
* @auther �ɓ� �L��
* @date   2019/10/21
*/
#ifndef BULLET_HPP
#define BULLET_HPP

#include "DxLib.h"
#include "Vector2.hpp"

class Bullet
{
private:
	const float DELAY = 15.0f;
	const float SPEED = 10.0f;
	bool active{};
	int handle{};
	Vector2 move_Vector{};
public:
	Vector2 position{};
	Bullet();
	void Init();
	void CreateBullet(Vector2&, float);
	void Move();
	void Draw();
	void Update();
};

#endif
