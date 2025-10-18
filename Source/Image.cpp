#include "Image.h"
#include "DxLib.h"
#include <assert.h>

namespace Image
{
	std::map<std::string, int> ui;
}

void Image::Init()
{
	ui["CircleGauge1"] = LoadGraph("data/image/circleGauge1.png"); // ŠDF‚Ì‰~ƒQ[ƒW
	ui["CircleGauge2"] = LoadGraph("data/image/circleGauge2.png"); // —ÎF‚Ì‰~ƒQ[ƒW
}

