/*
* @file   Vector2.cpp
* @brief  operatorの定義
* @auther 伊藤 広樹
* @data   2019/10/17
*/
#include "Vector2.hpp"
#include <cmath>

Vector2 operator+(const Vector2& vector1, const Vector2& vector2)
{
	return Vector2{ vector1.x + vector2.x, vector1.y + vector2.y };
}

Vector2 operator-(const Vector2& vector1, const Vector2& vector2)
{
	return Vector2{ vector1.x - vector2.x, vector1.y - vector2.y };
}

Vector2 operator*(const Vector2& vector1, const float& scalar)
{
	return Vector2{ vector1.x * scalar, vector1.y * scalar };
}

Vector2& Vector2::operator+=(const Vector2& vector)
{
	*this = *this + vector;
	return *this;
}

Vector2& Vector2::operator-=(const Vector2& vector)
{
	*this = *this - vector;
	return *this;
}

float Vector2::Length()
{
	return sqrt(x * x + y * y);
}

void Vector2::Normalize()
{
	auto length = Length();
	if (length == 0)
	{
		x = 0;
		y = 0;
	}
	else
	{
		x /= length;
		y /= length;
	}
}

static float Distance(const Vector2& vec1, const Vector2& vec2)
{
	auto x = vec1.x - vec2.x;
	auto y = vec1.y - vec2.y;
	return std::abs(std::sqrt(x * x + y * y));
}
