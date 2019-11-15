/**
* @file   Input.cpp
* @brief  �����o�֐��̒�`
* @auther �ɓ� �L��
* @date   2019/11/04
*/
#include "DxLib.h"
#include "Input.hpp"

/**
* @brief �L�[�̓��͂̏�Ԃ�z��ɓ���鏈��
*/
void Input::InputCheck()
{
	DxLib::GetHitKeyStateAll(buf);
	//�L�[��������Ă���l�𑝂₵�A������Ă��Ȃ�������O����
	for (int i = 0; i < 256; i++)
	{
		key[i] = (buf[i] == 1) ? key[i]++ : key[i] = 0;
	}
}