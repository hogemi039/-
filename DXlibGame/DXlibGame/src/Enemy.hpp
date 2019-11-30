/**
* @file   Enemy.hpp
* @brief  ìGÇÃÉNÉâÉX
* @auther à…ì° çLé˜
* @date   2019/11/29
*/
#ifndef ENEMY_HPP
#define ENEMY_HPP
#include "Vector2.hpp"
#include "OBject.hpp"

class Enemy : Object
{
private:
	enum DIR
	{
		Left = -1,
		Right = 1
	};
	bool jumpFlag_{};
	void Fall();
	void Move();
public:
	Vector2 moveVector_{};
	float dir_{};
	float fallSpeed_{};
	Vector2 GetPosition();
	void SetPosition(Vector2);
	void Render();
	void Update();
	Enemy();
	~Enemy() = default;
};
#endif