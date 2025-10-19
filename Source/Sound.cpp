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
	// ���K
	scale[1] = LoadSoundMem("data/sound/shuttleRun/1.mp3"); // �h �Ⴂ��
	scale[2] = LoadSoundMem("data/sound/shuttleRun/2.mp3"); // ��
	scale[3] = LoadSoundMem("data/sound/shuttleRun/3.mp3"); // �~
	scale[4] = LoadSoundMem("data/sound/shuttleRun/4.mp3"); // �t�@
	scale[5] = LoadSoundMem("data/sound/shuttleRun/5.mp3"); // �\
	scale[6] = LoadSoundMem("data/sound/shuttleRun/6.mp3"); // ��
	scale[7] = LoadSoundMem("data/sound/shuttleRun/7.mp3"); // �V
	scale[8] = LoadSoundMem("data/sound/shuttleRun/8.mp3"); // �h ������

	// ���ʉ�
	se["Ready"] = LoadSoundMem("data/sound/ready.mp3");
	se["Go"] = LoadSoundMem("data/sound/go.mp3");
	se["Clap"] = LoadSoundMem("data/sound/clap.mp3"); // ����
}