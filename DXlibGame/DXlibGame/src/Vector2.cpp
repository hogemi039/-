/*
* @file   Vector2.cpp
* @brief  operator‚Ì’è‹`
* @auther ˆÉ“¡ L÷
* @data   2019/10/17
*/
#include "Vector2.hpp"

Vector2 operator+(const Vector2& vector1, const Vector2& vector2)
{
	return Vector2{ vector1.x + vector2.x, vector1.y + vector2.y };
}

Vector2& Vector2::operator+=(const Vector2& vector)
{
	*this = *this + vector;
	return *this;
}