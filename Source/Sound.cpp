#include "Sound.h"
#include "DxLib.h"
#include <assert.h>

namespace Sound
{
	std::map<int, int> se;
}

void Sound::Init()
{
	se[1] = LoadSoundMem("data/sound/shuttleRun/1.mp3"); // �h �Ⴂ��
	se[2] = LoadSoundMem("data/sound/shuttleRun/2.mp3"); // ��
	se[3] = LoadSoundMem("data/sound/shuttleRun/3.mp3"); // �~
	se[4] = LoadSoundMem("data/sound/shuttleRun/4.mp3"); // �t�@
	se[5] = LoadSoundMem("data/sound/shuttleRun/5.mp3"); // �\
	se[6] = LoadSoundMem("data/sound/shuttleRun/6.mp3"); // ��
	se[7] = LoadSoundMem("data/sound/shuttleRun/7.mp3"); // �V
	se[8] = LoadSoundMem("data/sound/shuttleRun/8.mp3"); // �h ������
}