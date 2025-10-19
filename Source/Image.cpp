#include "Image.h"
#include "DxLib.h"
#include <assert.h>

namespace Image
{
	std::map<std::string, int> ui;
	std::map<std::string, int> bg;
}

void Image::Init()
{
	ui["CircleGauge1"] = LoadGraph("data/image/circleGauge1.png"); // �D�F�̉~�Q�[�W
	ui["CircleGauge2"] = LoadGraph("data/image/circleGauge2.png"); // �ΐF�̉~�Q�[�W
	ui["Hp1"] = LoadGraph("data/image/hp1.png"); // �D�F�̉~
	ui["Hp2"] = LoadGraph("data/image/hp2.png"); // �������ԐF�̉~

	bg["Bg"] = LoadGraph("data/image/bg.jpg");
	bg["Film"] = LoadGraph("data/image/film.png");
}

