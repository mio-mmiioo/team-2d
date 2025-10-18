#include "Sound.h"
#include "DxLib.h"
#include <assert.h>

namespace Sound
{
	std::map<int, int> se;
}

void Sound::Init()
{
	se[1] = LoadSoundMem("data/sound/shuttleRun/1.mp3"); // ド 低い方
	se[2] = LoadSoundMem("data/sound/shuttleRun/2.mp3"); // レ
	se[3] = LoadSoundMem("data/sound/shuttleRun/3.mp3"); // ミ
	se[4] = LoadSoundMem("data/sound/shuttleRun/4.mp3"); // ファ
	se[5] = LoadSoundMem("data/sound/shuttleRun/5.mp3"); // ソ
	se[6] = LoadSoundMem("data/sound/shuttleRun/6.mp3"); // ラ
	se[7] = LoadSoundMem("data/sound/shuttleRun/7.mp3"); // シ
	se[8] = LoadSoundMem("data/sound/shuttleRun/8.mp3"); // ド 高い方
}