#include "Image.h"
#include "DxLib.h"
#include <assert.h>

namespace Image
{
	std::map<std::string, int> ui;
}

void Image::Init()
{
	ui["CircleGauge"] = LoadGraph("data/image/circleGauge.png"); // —ÎF‚Ì‰~ƒQ[ƒW
}

