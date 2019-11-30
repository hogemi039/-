#include "DxLib.h"
#include "player.hpp"
#include "Enemy.hpp"
#include "Object.hpp"
#include "BulletManager.hpp"
#include "Timer.hpp"
#include "Input.hpp"
#include "Map.hpp"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//フルスクリーンモードからウィンドウモードに変更
	DxLib::ChangeWindowMode(true);
	//ウィンドウサイズを指定
	DxLib::SetGraphMode(1280, 720, 32);
	if (DxLib::DxLib_Init() == -1) { return -1; }
	Player *player_ = new Player();
	Enemy *Enemy_ = new Enemy();
	player_->Init();
	Time::Init();
	DxLib::LoadDivGraph("resource/sheet.png", 70, 10, 7, 32, 32, maphandle);
	DxLib::SetDrawScreen(DX_SCREEN_BACK);
	//ESCキーを押すか, 画面を閉じたらループを抜ける
	while (DxLib::ProcessMessage() == 0 && !Input::GetInstance().GetKeyDown(KEY_INPUT_ESCAPE))
	{
		DxLib::ClearDrawScreen();
		Input::GetInstance().Update();
		Time::Update();
		player_->Update();

		Enemy_->Update();
		
		DrawMap();

		player_->Render();
		Enemy_->Render();

		DxLib::ScreenFlip();
	}
	delete player_;
	DxLib_End();
	return 0;
}