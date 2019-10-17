#include "DxLib.h"
#include "player.hpp"
#include "Timer.hpp"

const int MAP_WIDTH = 10;
const int MAP_HEIGHT = 10;
const int GROUND_IMAGE_SIZE = 32;

const int map[MAP_HEIGHT][MAP_WIDTH] =
{
	{0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0},

	{0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0},
	{1,1,1,1,1,1,1,1,1,1},
	{0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0},
};

int maphandle[70];

void DrawMap()
{
	for (int i = 0; i < MAP_HEIGHT; ++i)
	{
		for (int j = 0; j < MAP_WIDTH; ++j)
		{
			if (map[i][j] == 1)
			{
				//1�Ԗڂ̃}�b�v�`�b�v��`�悳����
				DxLib::DrawGraph(j * 32, i * 32, maphandle[1], true);
			}
		}
	}
}

bool HitWithGround(Vector2<float>& pos)
{
	int x = static_cast<int>(pos.x / GROUND_IMAGE_SIZE);
	int y = static_cast<int>(pos.y / GROUND_IMAGE_SIZE);
	if (x < MAP_WIDTH && y < MAP_HEIGHT)
	{
		y++;
		if (map[y][x] == 0)
		{
			/*pos.jump_flag = true;*/
			return true;
		}
		if (map[y][x] != 0)
		{
			/*pos.jump_flag = false;*/
			pos.y = static_cast<float>((y - 1) * 32);
			return false;
		}
	}
	return true;
}

// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	Player player_;
	//�t���X�N���[�����[�h����E�B���h�E���[�h�ɕύX
	DxLib::ChangeWindowMode(true);
	DxLib::SetGraphMode(1280, 720, 32);

	if (DxLib_Init() == -1) { return -1; }
	DxLib::LoadDivGraph("resource/sheet.png", 70, 10, 7, 32, 32, maphandle);
	//�v���C���[�̏�����
	player_.Init();
	DxLib::SetDrawScreen(DX_SCREEN_BACK);
	Time::Init();
	//ESC�L�[��������, ��ʂ�����烋�[�v�𔲂���
	while (ProcessMessage() == FALSE && CheckHitKey(KEY_INPUT_ESCAPE) == FALSE)
	{
		DxLib::ClearDrawScreen();
		Time::Update();
		player_.Update();
		DrawMap();
		player_.jump_flag = HitWithGround(player_.position);
		DxLib::ScreenFlip();
	}
	DxLib_End();
	return 0;
}