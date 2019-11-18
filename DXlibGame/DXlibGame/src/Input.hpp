/**
* @file   Input.hpp 
* @brief  �L�[���͏����p�N���X 
* @auther �ɓ� �L�� 
* @date   2019/10/24 
*/
#ifndef INPUT_HPP
#define INPUT_HPP
#include "Singleton.hpp"

class Input : public Singleton<Input>
{
private:
	char current_[256], prev_[256];
public:
	void Update();
	bool GetKey(int);
	bool GetKeyDown(int);
	bool GetKeyUp(int);
	Input() = default;
	~Input() = default;
};
#endif