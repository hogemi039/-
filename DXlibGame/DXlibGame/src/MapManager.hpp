/**
* @file   MapManager.hpp
* @brief  ƒ}ƒbƒv‚Ì“Ç‚İ‚İ
* @auther ˆÉ“¡ L÷
* @date   2019/12/5
*/
#ifndef MAPMANAGER_HPP
#define MAPMANAGER_HPP
#include <vector>

class MapManager
{
private:
	std::vector<int> mapList{};
	int mapWidth{};
	int mapHeight{};
	void ReadMap();
public:
	int GetMapWidth();
	int GetMapHeight();
	int GetChipNum(int, int);
	MapManager();
	~MapManager() = default;
};
#endif
