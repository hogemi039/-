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
	Enemy *enemy_ = new Enemy();
	player_->Init();
	Time::Init();
	MapInit();
	DxLib::SetDrawScreen(DX_SCREEN_BACK);
	//ESCキーを押すか, 画面を閉じたらループを抜ける
	while (DxLib::ProcessMessage() == 0 && !Input::GetInstance().GetKeyDown(KEY_INPUT_ESCAPE))
	{
		DxLib::ClearDrawScreen();
		Input::GetInstance().Update();
		Time::Update();
		DrawMap();
		player_->Update();
		enemy_->Update();
		//当たり判定のため、標的の座標と当たり判定のサイズを取る
		player_->SetTargetPosition(enemy_->GetPosition());
		player_->SetTargetSize(enemy_->GetSize());
		enemy_->SetCollisionFlag(player_->GetCollisionFlag());
		player_->Render();
		enemy_->Render();

		DxLib::ScreenFlip();
	}
	delete player_;
	DxLib_End();
	return 0;
}