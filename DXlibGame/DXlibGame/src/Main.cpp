﻿#include "DxLib.h"
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

	int backgroundImg = LoadGraph("resource/image/background.png");

	Player* player_ = new Player();
	Enemy* enemy_ = new Enemy();
	player_->Init();
	Time::Init();
	MapInit();
	DxLib::SetDrawScreen(DX_SCREEN_BACK);
	//ESCキーを押すか, 画面を閉じたらループを抜ける
	while (DxLib::ProcessMessage() == 0 && !Input::GetInstance().GetKeyDown(KEY_INPUT_ESCAPE))
	{
		DxLib::ClearDrawScreen();
		DxLib::DrawGraph(0, 0, backgroundImg, TRUE);
		Input::GetInstance().Update();
		Time::Update();
		player_->Update();
		enemy_->Update();
		//敵が生きているかをプレイヤーに保持させておく
		player_->SetTargetActive(enemy_->GetActive());
		//当たり判定のため、標的の座標と当たり判定のサイズを取る
		player_->SetTargetPosition(enemy_->GetPosition() - Vector2{ 16.f, 16.f });
		player_->SetTargetSize(enemy_->GetSize() - Vector2{ 16.f, 16.f });
		enemy_->SetCollisionFlag(player_->GetCollisionFlag());
		auto e_pos = enemy_->GetPosition();
		DrawMap();
		player_->Render();
		enemy_->Render();
		DxLib::ScreenFlip();
	}
	delete player_;
	DxLib_End();
	return 0;
}
