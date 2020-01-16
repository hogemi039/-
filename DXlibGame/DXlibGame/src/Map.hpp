/**
* @file   Map.hpp
* @brief  ƒ}ƒbƒv‚ğ•`‰æ
* @auther ˆÉ“¡ L÷
* @date   2019/10/14
*/
#ifndef MAP_HPP
#define MAP_HPP
#include "MapManager.hpp"

namespace
{
	//’è”
	const int GROUND_IMAGE_SIZE{ 32 };

	MapManager *mapMng = new MapManager();
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
