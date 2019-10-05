#include "DxLib.h"
#include "player.hpp"

// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	Player player_;
	DxLib::ChangeWindowMode(true);
	DxLib::SetGraphMode(1280, 720, 32);
	
	if (DxLib_Init() == -1) { return -1; }
	player_.Init();  //�v���C���[�̏�����
	DxLib::SetDrawScreen(DX_SCREEN_BACK);
	while (ProcessMessage() == FALSE && CheckHitKey(KEY_INPUT_ESCAPE) == FALSE)   //ESC�L�[��������, ��ʂ�����烋�[�v�𔲂���
	{
		DxLib::ClearDrawScreen();
		player_.Update();
		DxLib::ScreenFlip();
	}
	DxLib_End(); 
	return 0;				// �\�t�g�̏I�� 
}