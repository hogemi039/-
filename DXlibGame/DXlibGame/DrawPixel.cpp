#include "DxLib.h"
#include "player.hpp"

// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	Player player_;
	DxLib::ChangeWindowMode(true);
	DxLib::SetGraphMode(1280, 720, 32);
	
	if (DxLib_Init() == -1) { return -1; }
	player_.Init();  //プレイヤーの初期化
	DxLib::SetDrawScreen(DX_SCREEN_BACK);
	while (ProcessMessage() == FALSE && CheckHitKey(KEY_INPUT_ESCAPE) == FALSE)   //ESCキーを押すか, 画面を閉じたらループを抜ける
	{
		DxLib::ClearDrawScreen();
		player_.Update();
		DxLib::ScreenFlip();
	}
	DxLib_End(); 
	return 0;				// ソフトの終了 
}