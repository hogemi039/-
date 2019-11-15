/**
* @file   Object.hpp
* @brief  �I�u�W�F�N�g�̊��N���X
* @auther �ɓ� �L��
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