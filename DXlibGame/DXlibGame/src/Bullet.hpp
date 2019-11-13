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

class Bullet :public Object
{
private:
	const float DELAY{ 15.0f };
	const float SPEED{ 10.0f };
	Vector2 moveVector_{};
	bool active{};
public:
	void Move();
	void Render();
	void Update();
	Bullet(Vector2, Vector2);
	~Bullet() = default;
};

//class Bullet
//{
//private:
//	const float DELAY{ 15.0f };
//	const float SPEED{ 10.0f };
//	Vector2 moveVector{};
//	int handle{};
//	bool active{};
//	//void Destroy();
//public:
//	Vector2 position{};
//	Bullet(float, float);
//	void CreateBullet(Vector2&, float);
//	void Move();
//	void Render();
//	void Update();
//};

#endif
