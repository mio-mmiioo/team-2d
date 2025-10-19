#include "Sound.h"
#include "DxLib.h"
#include <assert.h>

namespace Sound
{
	std::map<int, int> scale;
	std::map<std::string, int> se;
}

void Sound::Init()
{
	// 音階
	scale[1] = LoadSoundMem("data/sound/shuttleRun/1.mp3"); // ド 低い方
	scale[2] = LoadSoundMem("data/sound/shuttleRun/2.mp3"); // レ
	scale[3] = LoadSoundMem("data/sound/shuttleRun/3.mp3"); // ミ
	scale[4] = LoadSoundMem("data/sound/shuttleRun/4.mp3"); // ファ
	scale[5] = LoadSoundMem("data/sound/shuttleRun/5.mp3"); // ソ
	scale[6] = LoadSoundMem("data/sound/shuttleRun/6.mp3"); // ラ
	scale[7] = LoadSoundMem("data/sound/shuttleRun/7.mp3"); // シ
	scale[8] = LoadSoundMem("data/sound/shuttleRun/8.mp3"); // ド 高い方

	// 効果音
	se["Ready"] = LoadSoundMem("data/sound/ready.mp3");
	se["Go"] = LoadSoundMem("data/sound/go.mp3");
	se["Clap"] = LoadSoundMem("data/sound/clap.mp3"); // 拍手
}