/**
* @file   Map.hpp
* @brief  マップを描画
* @auther 伊藤 広樹
* @date   2019/10/14
*/
#ifndef MAP_HPP
#define MAP_HPP
#include "MapManager.hpp"

namespace
{
	////定数
	//const int MAP_WIDTH{ 10 };
	//const int MAP_HEIGHT{ 10 };
	const int GROUND_IMAGE_SIZE{ 32 };
	//const int map[MAP_HEIGHT][MAP_WIDTH] =
	//{
	//	{0,0,0,0,0,0,0,0,0,0},
	//	{0,0,0,0,0,0,0,0,0,0},
	//	{0,0,0,0,0,0,0,0,0,0},
	//	{1,0,0,0,0,0,0,0,0,1},
	//	{1,0,0,0,0,1,0,0,0,1},

	//	{1,0,0,0,1,0,0,0,0,1},
	//	{1,0,0,0,0,0,0,0,0,1},
	//	{1,1,1,1,1,1,1,1,1,1},
	//	{0,0,0,0,0,0,0,0,0,0},
	//	{0,0,0,0,0,0,0,0,0,0},
	//};
	MapManager *mapMng = new MapManager();
	int maphandle[70];

	void MapInit()
	{
		DxLib::LoadDivGraph("resource/image/sheet.png", 70, 10, 7, 32, 32, maphandle);
	}
	//void DrawMap()
	//{
	//	for (int i = 0; i < MAP_HEIGHT; ++i)
	//	{
	//		for (int j = 0; j < MAP_WIDTH; ++j)
	//		{
	//			if (map[i][j] == 1)
	//			{
	//				//1番目のマップチップを描画させる
	//				DxLib::DrawGraph(j * 32, i * 32, maphandle[1], true);
	//			}
	//		}
	//	}
	//}
	void DrawMap()
	{
		for (int y = 0; y < mapMng->GetMapHeight(); y++)
		{
			for (int x = 0; x < mapMng->GetMapWidth(); x++)
			{
				if (mapMng->GetChipNum(x, y) != -1)
				{
					DxLib::DrawGraph(x * 32, y * 32, maphandle[mapMng->GetChipNum(x, y)], true);
				}
			}
		}
	}



	bool GetMapState(int x, int y)
	{
		if (mapMng->GetChipNum(x, y) != -1)
		{
			return true;
		}
		return false;
	}
}

#endif
