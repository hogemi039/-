/**
* @file   Bullet.cpp
* @brief  ÉÅÉìÉoä÷êîÇÃíËã`
* @auther à…ì° çLé˜
* @date   2019/10/23
*/
#include "Bullet.hpp"

Bullet::Bullet()
{
	active = false;
	//origin = Vector2(16.0f, 16.0f);
	move_Vector = Vector2(0.0f, 0.0f);
	position = Vector2(0.0f, 0.0f);
}

void Bullet::Init()
{
	handle = DxLib::LoadGraph("resource/purun.png");
}

void Bullet::CreateBullet(Vector2& pos, float dir)
{
	active = true;
	position = pos;
	move_Vector = Vector2(dir, 0.0f);
	move_Vector.Normalize();
}

void Bullet::Move()
{
	position += move_Vector;
}

void Bullet::Draw()
{
	DxLib::DrawGraph(static_cast<int>(position.x), static_cast<int>(position.y), handle, true);
}

void Bullet::Update()
{
	if (active == false)
	{
		return;
	}
	Move();
	Draw();
	DxLib::DrawFormatString(0, 300, GetColor(255, 255, 255), "x = %f, y = %f", position.x, position.y);
}