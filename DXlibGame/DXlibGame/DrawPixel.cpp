#include "DxLib.h"
#include "player.hpp"
#include "Timer.hpp"

// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	Player player_;
	DxLib::ChangeWindowMode(true);
	DxLib::SetGraphMode(1280, 720, 32);
	
	if (DxLib_Init() == -1) { return -1; }
	//�v���C���[�̏�����
	player_.Init();  
	int color = GetColor(255, 255, 255);
	DxLib::SetDrawScreen(DX_SCREEN_BACK);
	Time::Init();
	//ESC�L�[��������, ��ʂ�����烋�[�v�𔲂���
	while (ProcessMessage() == FALSE && CheckHitKey(KEY_INPUT_ESCAPE) == FALSE)   
	{
		DxLib::ClearDrawScreen();
		Time::Update();
		player_.Update();
		DrawFormatString(100, 100, color, "deltaTime:%f", Time::delta_time);
		DxLib::ScreenFlip();
	}
	DxLib_End(); 
	return 0;
}