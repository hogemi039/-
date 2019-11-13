/**
* @file   Input.cpp
* @brief  ƒƒ“ƒoŠÖ”‚Ì’è‹`
* @auther ˆÉ“¡ L÷
* @date   2019/11/04
*/
#include "DxLib.h"
#include "Input.hpp"

void Input::InputCheck()
{
	DxLib::GetHitKeyStateAll(buf);
	for (int i = 0; i < 256; i++)
	{
		key[i] = (buf[i] == 1) ? key[i]++ : key[i] = 0;
	}
}