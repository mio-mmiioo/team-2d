#pragma once

namespace Level {
	void Init();

	float CountToTime(int count); // カウントから音階の時間を求める
	int CountToLevel(int count); // カウントからレベルを割り出す
	float RateCount(int count); // カウントからレベルアップまでのパーセントを求める

}
