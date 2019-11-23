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
#include "Object.hpp"

class Bullet : public Object
{
private:
	const float SPEED{ 10.0f };
	Vector2 moveVector_{};
	bool active{};
public:
	Vector2& GetPosition();
	void Move();
	void Render();
	void Update();
	Bullet(const Vector2, const float);
	~Bullet() = default;
};
#endif
