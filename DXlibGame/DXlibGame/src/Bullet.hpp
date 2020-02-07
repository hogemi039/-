/**
* @file   Bullet.hpp
* @brief  íeä€ÇÃÉNÉâÉX
* @auther à…ì° çLé˜
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
	Vector2 size{ 16.0f, 16.0f };
	Vector2 moveVector_{};
	bool active_{};
public:
	Vector2 GetPosition()
	{
		return position_;
	}
	Vector2 GetSize()
	{
		return size;
	}
	bool GetActive()
	{
		return active_;
	}
	void SetActive(bool active)
	{
		active_ = active;
	}
	void Move();
	void Render();
	void Update();
	Bullet(const Vector2, const float);
	~Bullet() = default;
};
#endif