#include "Level.h"
#include <vector>

namespace Level {
	std::vector<int> count_ = { 0, 7,15,23,32,41,51,61,72,83,94 };
	std::vector<float> level_ = { 9.0f,8.0f,7.58f,7.20f,6.86f,6.55f,6.26f,6.00f,5.76f,5.54f };

	float CountToTime(int count)
	{
		for (int i = count_.size() - 1; i >= 0; i--)
		{
			if (count >= count_[i])
			{
				return level_[i];
			}
		}
	}
}
