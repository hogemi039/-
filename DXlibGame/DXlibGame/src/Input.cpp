/**
* @file   Input.cpp
* @brief  メンバ関数の定義
* @auther 伊藤 広樹
* @date   2019/11/04
*/
#include "DxLib.h"
#include "Input.hpp"
#include <cstring>

/**
* @brief キーの入力の状態を配列に入れる処理
*/
void Input::Update()
{
	//１フレーム前のキー状態を更新した後にキーの状態を取得する
	std::memcpy(prev_, current_, sizeof(char) * 256);
	/*for (int i = 0; i < 256; i++)
	{
		prev_[i] = current_[i];
	}*/
	DxLib::GetHitKeyStateAll(current_);
}

/**
* @brief 押しっぱなしの状態を取る処理
*/
bool Input::GetKey(int key)
{
	return current_[key] && prev_[key];
}

/**
* @brief 押した瞬間を取る処理
*/
bool Input::GetKeyDown(int key)
{
	return current_[key] && !prev_[key];
}

/**
* @brief 離した瞬間を取る処理
*/
bool Input::GetKeyUp(int key)
{
	return !current_[key] && prev_[key];
}