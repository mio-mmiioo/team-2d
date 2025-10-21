#include "Level.h"
#include "DxLib.h"
#include <vector>
#include "../../../Library/Time.h"
#include "../../Sound.h"
#include "../../Data.h"

namespace Level {
	//std::vector<int> count_ = { 0, 7,15,23,32,41,51,61,72,83,94 };
	//std::vector<float> level_ = { 9.0f,8.0f,7.58f,7.20f,6.86f,6.55f,6.26f,6.00f,5.76f,5.54f };
}

void Level::Update()
{
}

float Level::CountToTime(int count)
{
	for (int i = Data::levelUpCount.size() - 1; i >= 0; i--)
	{
		if (count >= Data::levelUpCount[i])
		{
			return Data::levelTime[i];
		}
	}
}

float Level::RateCount(int count)
{
	float rate;
	for (int i = Data::levelUpCount.size() - 1; i >= 0; i--)
	{
		if (count >= Data::levelUpCount[i])
		{
			rate = ((float)count - (float)Data::levelUpCount[i]) / ((float)Data::levelUpCount[i + 1] - (float)Data::levelUpCount[i]) * 100;
			return rate;
		}
	}
}
