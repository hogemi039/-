/**
* @file   Input.cpp
* @brief  �����o�֐��̒�`
* @auther �ɓ� �L��
* @date   2019/11/04
*/
#include "DxLib.h"
#include "Input.hpp"
#include <cstring>

/**
* @brief �L�[�̓��͂̏�Ԃ�z��ɓ���鏈��
*/
void Input::Update()
{
	//�P�t���[���O�̃L�[��Ԃ��X�V������ɃL�[�̏�Ԃ��擾����
	std::memcpy(prev_, current_, sizeof(char) * 256);
	/*for (int i = 0; i < 256; i++)
	{
		prev_[i] = current_[i];
	}*/
	DxLib::GetHitKeyStateAll(current_);
}

/**
* @brief �������ςȂ��̏�Ԃ���鏈��
*/
bool Input::GetKey(int key)
{
	return current_[key] && prev_[key];
}

/**
* @brief �������u�Ԃ���鏈��
*/
bool Input::GetKeyDown(int key)
{
	return current_[key] && !prev_[key];
}

/**
* @brief �������u�Ԃ���鏈��
*/
bool Input::GetKeyUp(int key)
{
	return !current_[key] && prev_[key];
}