/**
* @file   Player.cpp
* @brief  Vector2ÇÃÉNÉâÉX
* @auther à…ì° çLé˜
* @date   2019/10/01
*/
#ifndef VECTOR2_HPP
#define VECTOR2_HPP

template<typename T>
class Vector2
{
public:
	T x{};
	T y{};
	Vector2() = default;
	Vector2(T x, T y) :x(x), y(y) {};
	template<typename U>
	Vector2<T>& operator+=(const Vector2<U>& vector)
	{
		*this = *this + vector;
		return *this;
	}
};
template<typename T>
Vector2<T> operator+(const Vector2<T>& vector1, const Vector2<T>& vector2)
{
	return Vector2{ vector1.x + vector2.x, vector1.y + vector2.y };
}

#endif
