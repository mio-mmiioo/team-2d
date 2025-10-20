#pragma once

namespace Level {
	void Update();
	float CountToTime(int count); // カウントから音階の時間を求める
	float RateCount(int count); // カウントからレベルアップまでのパーセントを求める

	void SoundUp(); // レベルアップする音源
}
