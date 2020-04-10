/**
* @file   Map.hpp
* @brief  マップを描画
* @auther 伊藤 広樹
* @date   2019/10/14
*/
#ifndef MAP_HPP
#define MAP_HPP
#include "MapManager.hpp"
#include "Camera.hpp"

namespace
{
	//定数
	const int GROUND_IMAGE_SIZE{ 32 };

	MapManager* mapMng = new MapManager();
	int maphandle[70];

	void MapInit()
	{
		DxLib::LoadDivGraph("resource/image/sheet.png", 70, 10, 7, 32, 32, maphandle);
	}

	void DrawMap()
	{
		for (int y = 0; y < mapMng->GetMapHeight(); y++)
		{
			for (int x = 0; x < mapMng->GetMapWidth(); x++)
			{
				if (mapMng->GetChipNum(x, y) != -1)
				{
					DxLib::DrawGraph(static_cast<int>((x - Camera::position_.x / 32) * 32), static_cast<int>((y - Camera::position_.y / 32) * 32), maphandle[mapMng->GetChipNum(x, y)], true);
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
