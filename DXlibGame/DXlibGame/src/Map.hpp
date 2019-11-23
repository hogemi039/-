/**
* @file   Map.hpp
* @brief  マップの読み込み、
* @auther 伊藤 広樹
* @date   2019/10/14
*/
#ifndef MAP_HPP
#define MAP_HPP

namespace
{

	//定数
	const int MAP_WIDTH{ 10 };
	const int MAP_HEIGHT{ 10 };
	const int GROUND_IMAGE_SIZE{ 32 };
	const int map[MAP_HEIGHT][MAP_WIDTH] =
	{
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{1,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,1,0,0,0,1},

		{1,0,0,0,1,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,1},
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
					//1番目のマップチップを描画させる
					DxLib::DrawGraph(j * 32, i * 32, maphandle[1], true);
				}
			}
		}
	}

	bool HitWithGround(int x, int y)
	{
		if (map[y][x] == 1)
		{
			return true;
		}
		return false;
	}
}

#endif
