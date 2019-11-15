/**
* @file   Input.cpp
* @brief  メンバ関数の定義
* @auther 伊藤 広樹
* @date   2019/11/04
*/
#include "DxLib.h"
#include "Input.hpp"

/**
* @brief キーの入力の状態を配列に入れる処理
*/
void Input::InputCheck()
{
	DxLib::GetHitKeyStateAll(buf);
	//キーが押されてたら値を増やし、押されていなかったら０を代入
	for (int i = 0; i < 256; i++)
	{
		key[i] = (buf[i] == 1) ? key[i]++ : key[i] = 0;
	}
}