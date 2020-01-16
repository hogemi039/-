/**
* @file   Camera.hpp
* @brief  �J�����̃N���X
* @auther �ɓ� �L��
* @date   2020/1/15
*/
#ifndef CAMERA_HPP
#define CAMERA_HPP
#include "Vector2.hpp"
#include "DxLib.h"

class Camera
{
private:
	Vector2 position_{};
	Vector2 loolPosition_{};
public:
	MATRIX GetMatrix();
	void Move();
	Camera() {};
	~Camera() {};
};
#endif