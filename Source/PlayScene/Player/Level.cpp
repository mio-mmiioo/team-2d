#include "Level.h"
#include "DxLib.h"
#include <vector>
#include "../../../Library/Time.h"
#include "../../Sound.h"

namespace Level {
	std::vector<int> count_ = { 0, 7,15,23,32,41,51,61,72,83,94 };
	std::vector<float> level_ = { 9.0f,8.0f,7.58f,7.20f,6.86f,6.55f,6.26f,6.00f,5.76f,5.54f };

	float timer_ = 0.0f; // 次の音を鳴らすまでのタイマー
	int counter_ = 0; // 現在の音が何番目か
	const float TIME = 1.0f;
	const int COUNT = 3;
}

void Level::Update()
{
	if (Level::timer_ > 0)
	{
		Level::timer_ -= Time::DeltaTime();
		if (timer_ <= 0)
		{
			counter_ += 1;
			PlaySoundMem(Sound::scale[counter_], DX_PLAYTYPE_BACK, TRUE);
			
			if (counter_ < Level::COUNT)
			{
				timer_ = timer_ + Level::TIME;
			}
		}
	}
}

float Level::CountToTime(int count)
{
	for (int i = Level::count_.size() - 1; i >= 0; i--)
	{
		if (count >= Level::count_[i])
		{
			return Level::level_[i];
		}
	}
}

float Level::RateCount(int count)
{
	float rate;
	for (int i = Level::count_.size() - 1; i >= 0; i--)
	{
		if (count >= Level::count_[i])
		{
			rate = ((float)count - (float)Level::count_[i]) / ((float)Level::count_[i + 1] - (float)Level::count_[i]) * 100;
			return rate;
		}
	}
}

void Level::SoundUp()
{
	timer_ = Level::TIME;
}
