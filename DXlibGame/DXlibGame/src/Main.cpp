#include "DxLib.h"
#include "player.hpp"
#include "Object.hpp"
#include "BulletManager.hpp"
#include "Timer.hpp"
#include "Input.hpp"

//�萔
const int MAP_WIDTH{ 10 };
const int MAP_HEIGHT{ 10 };
const int GROUND_IMAGE_SIZE{ 32 };
const int map[MAP_HEIGHT][MAP_WIDTH] =
{
	{0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0},

	{0,0,0,0,1,1,0,0,0,0},
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

/**
* @brief �n�ʂƂ̓����蔻��ƍ��W�������߂��֐�
* @param pos �Ώۂ̍��W
*/
bool HitWithGround(Vector2 &pos)
{
	int x = static_cast<int>((pos.x) / GROUND_IMAGE_SIZE);
	int y = static_cast<int>((pos.y) / GROUND_IMAGE_SIZE);
	if (x < MAP_WIDTH && y < MAP_HEIGHT)
	{
		//��ɒn�ʂ�����
		if (map[y][x] != 0)
		{
			pos.y = static_cast<float>(y * GROUND_IMAGE_SIZE);
			return false;
		}
		y++;
		//���ɒn�ʂ��Ȃ�
		if (map[y][x] == 0)
		{
			/*pos.jump_flag = true;*/
			return true;
		}
		//���ɒn�ʂ�����
		if (map[y][x] != 0 || map[y][x + 1] != 0)
		{
			/*pos.jump_flag = false;*/
			pos.y = static_cast<float>((y - 1) * GROUND_IMAGE_SIZE);
			return false;
		}
	}
	return true;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//�t���X�N���[�����[�h����E�B���h�E���[�h�ɕύX
	DxLib::ChangeWindowMode(true);
	//�E�B���h�E�T�C�Y���w��
	DxLib::SetGraphMode(1280, 720, 32);
	if (DxLib_Init() == -1) { return -1; }
	Player *player_ = new Player();
	player_->Init();
	Time::Init();
	DxLib::LoadDivGraph("resource/sheet.png", 70, 10, 7, 32, 32, maphandle);
	DxLib::SetDrawScreen(DX_SCREEN_BACK);
	//ESC�L�[��������, ��ʂ�����烋�[�v�𔲂���
	while (ProcessMessage() == FALSE && CheckHitKey(KEY_INPUT_ESCAPE) == FALSE)
	{
		DxLib::ClearDrawScreen();
		//Input::InputCheck();
		Time::Update();
		player_->Update();
		player_->jumpFlag = HitWithGround(player_->GetPosition());
		DrawMap();
		player_->Render();
		DxLib::ScreenFlip();
	}
	delete player_;
	DxLib_End();
	return 0;
}