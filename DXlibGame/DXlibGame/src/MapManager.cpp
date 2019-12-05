/**
* @file   MapManager.cpp
* @brief  �����o�֐��̒�`
* @auther �ɓ� �L��
* @date   2019/12/5
*/
#include "MapManager.hpp"
//xml�t�@�C����ǂݍ��܂��邽�߂̃w�b�_
//�T�C�g����_�E�����[�h���Ă�������
#include "tinyxml2.h"

MapManager::MapManager()
{
	ReadMap();
}

void MapManager::ReadMap()
{
	//XML�t�@�C���̓ǂݍ���
	tinyxml2::XMLDocument xml;
	xml.LoadFile("resource/mapdata/testMap.tmx");
	//�^�O������
	tinyxml2::XMLElement *map = xml.FirstChildElement("map");
	//tileset�Alayer�^�O��map�^�O�̒��ɏ�����Ă���̂�map����Ƃ邱�Ƃ��ł���
	tinyxml2::XMLElement *tileset = map->FirstChildElement("tileset");
	tinyxml2::XMLElement *layer = map->FirstChildElement("layer");
	//data�^�O��layer�^�O�̒��ɏ�����Ă���̂�layer����Ƃ邱�Ƃ��ł���
	tinyxml2::XMLElement *data = layer->FirstChildElement("data");
	//���Ԗڂ̃`�b�v�ԍ�����n�܂邩����
	int firstGid{ 0 };

	/*          �l�̎擾           */
	//tileset�^�O��firstgid�̐��l��ǂ�
	if (tileset->Attribute("firstgid"))
	{
		//�`�b�v�̊J�n�ԍ�
		firstGid = atoi(tileset->Attribute("firstgid"));
	}
	//layer�^�O��width�̐���ǂ�
	if (layer->Attribute("width"))
	{
		mapWidth = atoi(layer->Attribute("width"));
	}
	//layer�^�O��height�̐���ǂ�
	if (layer->Attribute("height"))
	{
		mapHeight = atoi(layer->Attribute("height"));
	}

	/*   �}�b�v�ԍ��擾   */
	const char* dataStr = data->GetText();
	const char* start = dataStr;
	for (int i = 0; i < mapWidth * mapHeight; i++)
	{
		//�J���}��T��
		const char* end = strchr(start, ',');
		/*    ������z��ɓ����    */
 		//TileMapEditor�̓s����A�����u����Ă��Ȃ��Ƃ���͂O�ɂȂ�
		//�󗓂�-1�ɂ��Ă��������B
		//�摜�̃`�b�v�ԍ��͂P����n�܂邪
		//�v���O������ł͂O���爵�������̂ŁA
		//�G�f�B�^�[��̐��l��firstGid�������΂O���爵����

		//�G���[�̌������P-----------------------------
		mapList.push_back(atoi(start)/* - firstGid*/);
		//--------------------------------------------

		//�J���}���Ȃ������i�Ō�j�Ȃ甲����
		if (end == nullptr)
		{
			break;
		}
		//�J���}�������߂�
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
	//�Y������}�b�v�̏���Ԃ�
	//1�����z��ł�
	//Y * �}�b�v�̉��� + X
	//�ŁA�񎟌��z��̂悤�ɂ��Ēl������
	return mapList.at(y * mapWidth + x);
}

