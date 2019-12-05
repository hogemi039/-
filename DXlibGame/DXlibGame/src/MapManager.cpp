/**
* @file   MapManager.cpp
* @brief  メンバ関数の定義
* @auther 伊藤 広樹
* @date   2019/12/5
*/
#include "MapManager.hpp"
//xmlファイルを読み込ませるためのヘッダ
//サイトからダウンロードしてきたもの
#include "tinyxml2.h"

MapManager::MapManager()
{
	ReadMap();
}

void MapManager::ReadMap()
{
	//XMLファイルの読み込み
	tinyxml2::XMLDocument xml;
	xml.LoadFile("resource/mapdata/testMap.tmx");
	//タグを入れる
	tinyxml2::XMLElement *map = xml.FirstChildElement("map");
	//tileset、layerタグはmapタグの中に書かれているのでmapからとることができる
	tinyxml2::XMLElement *tileset = map->FirstChildElement("tileset");
	tinyxml2::XMLElement *layer = map->FirstChildElement("layer");
	//dataタグはlayerタグの中に書かれているのでlayerからとることができる
	tinyxml2::XMLElement *data = layer->FirstChildElement("data");
	//何番目のチップ番号から始まるか入る
	int firstGid{ 0 };

	/*          値の取得           */
	//tilesetタグのfirstgidの数値を読む
	if (tileset->Attribute("firstgid"))
	{
		//チップの開始番号
		firstGid = atoi(tileset->Attribute("firstgid"));
	}
	//layerタグのwidthの数を読む
	if (layer->Attribute("width"))
	{
		mapWidth = atoi(layer->Attribute("width"));
	}
	//layerタグのheightの数を読む
	if (layer->Attribute("height"))
	{
		mapHeight = atoi(layer->Attribute("height"));
	}

	/*   マップ番号取得   */
	const char* dataStr = data->GetText();
	const char* start = dataStr;
	for (int i = 0; i < mapWidth * mapHeight; i++)
	{
		//カンマを探す
		const char* end = strchr(start, ',');
		/*    文字を配列に入れる    */
 		//TileMapEditorの都合上、何も置かれていないところは０になる
		//空欄は-1にしてあげたい。
		//画像のチップ番号は１から始まるが
		//プログラム上では０から扱いたいので、
		//エディター上の数値にfirstGidを引けば０から扱える

		//エラーの原因候補１-----------------------------
		mapList.push_back(atoi(start)/* - firstGid*/);
		//--------------------------------------------

		//カンマがなかった（最後）なら抜ける
		if (end == nullptr)
		{
			break;
		}
		//カンマ分すすめる
		start = end + 1;
	}
}

int MapManager::GetMapWidth()
{
	return mapWidth;
}

int MapManager::GetMapHeight()
{
	return mapHeight;
}

int MapManager::GetChipNum(int x, int y)
{
	//該当するマップの情報を返す
	//1次元配列でも
	//Y * マップの横幅 + X
	//で、二次元配列のようにして値を取れる
	return mapList.at(y * mapWidth + x);
}

