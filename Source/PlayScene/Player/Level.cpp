#include "Level.h"

Level::Level()
{
	count_ = { 7,15,23,32,41,51,61,72,83,94 }; // 
	level_ = { 9.0f,8.0f,7.58f,7.20f,6.86f,6.55f,6.26f,6.00f,5.76f,5.54f };
}

Level::~Level()
{
}

void Level::Update()
{
}

void Level::Draw()
{
}

int Level::CountToLevel(int count)
{

	for (int i = 0; i < count_.size(); i++)
	{

	}
}

float Level::LevelToTime(int level)
{
}
