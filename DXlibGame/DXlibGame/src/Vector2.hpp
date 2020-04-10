﻿/*
* @file   Player.cpp
* @brief  Vector2のクラス
* @auther 伊藤 広樹
* @date   2019/10/01
*/
#ifndef VECTOR2_HPP
#define VECTOR2_HPP

class Vector2
{
public:
	float x{};
	float y{};
	Vector2() = default;
	Vector2(float x, float y) :x(x), y(y) {};
	Vector2& operator+=(const Vector2&);
	Vector2& operator-=(const Vector2&);
	float Length();
	void Normalize();
};
Vector2 operator+(const Vector2&, const Vector2&);
Vector2 operator-(const Vector2&, const Vector2&);
Vector2 operator*(const Vector2&, const float&);
static float Distance(const Vector2&, const Vector2&);
#endif
