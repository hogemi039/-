/**
* @file   Input.hpp 
* @brief  キー入力処理用クラス 
* @auther 伊藤 広樹 
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