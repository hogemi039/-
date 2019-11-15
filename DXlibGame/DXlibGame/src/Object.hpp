/**
* @file   Object.hpp
* @brief  オブジェクトの基底クラス
* @auther 伊藤 広樹
* @date   2019/11/10
*/
#ifndef OBJECT_HPP
#define OBJECT_HPP
#include "Vector2.hpp"

class Object
{
protected:
	Vector2 position_{};
	int handle_{};
public:
	virtual void Render() = 0;
	virtual void Update() = 0;
	Object() = default;
	virtual ~Object() = default;
};

#endif