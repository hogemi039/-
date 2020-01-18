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
	//�t���X�N���[�����[�h����E�B���h�E���[�h�ɕύX
	DxLib::ChangeWindowMode(true);
	//�E�B���h�E�T�C�Y���w��
	DxLib::SetGraphMode(1280, 720, 32);
	if (DxLib::DxLib_Init() == -1) { return -1; }

	int backgroundImg = LoadGraph("resource/image/background.png");
	
	Player *player_ = new Player();
	Enemy *enemy_ = new Enemy();
	player_->Init();
	Time::Init();
	MapInit();
	DxLib::SetDrawScreen(DX_SCREEN_BACK);
	//ESC�L�[��������, ��ʂ�����烋�[�v�𔲂���
	while (DxLib::ProcessMessage() == 0 && !Input::GetInstance().GetKeyDown(KEY_INPUT_ESCAPE))
	{
		DxLib::ClearDrawScreen();
		DxLib::DrawGraph(0, 0, backgroundImg, TRUE);

		Input::GetInstance().Update();
		Time::Update();
		player_->Update();
		enemy_->Update();
		player_->SetTargetActive(enemy_->GetActive());
		//�����蔻��̂��߁A�W�I�̍��W�Ɠ����蔻��̃T�C�Y�����
		player_->SetTargetPosition(enemy_->GetPosition());
		player_->SetTargetSize(enemy_->GetSize());
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