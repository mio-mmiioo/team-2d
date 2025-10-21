#include "Level.h"
#include "DxLib.h"
#include <vector>
#include "../../Data.h"

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
