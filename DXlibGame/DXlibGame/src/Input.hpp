/**
* @file   Input.hpp
* @brief  �L�[���͏����p�N���X 
* @auther �ɓ� �L��
* @date   2019/10/24
*/
#ifndef INPUT_HPP
#define INPUT_HPP
#include "Singleton.hpp"

class Input /*: public Singleton<Input>*/
{
private:
	char buf[256];
public:
	int key[256];
	void InputCheck();
	Input() = default;
	~Input() = default;
};
#endif