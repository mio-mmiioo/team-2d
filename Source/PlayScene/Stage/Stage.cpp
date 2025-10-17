#include "Stage.h"
#include <assert.h>
#include <vector>
#include "../../../Library/CsvReader.h"
#include "../Player/Player.h"

Stage::Stage(int number)
{
	char filename[64];
	sprintf_s<64>(filename, "data/stage/stage%02d.csv", number);
	stage_.clear();

	// ステージデータの読み込み
	CsvReader* csv = new CsvReader(filename);
	for (int line = 0; line < csv->GetLines(); line++) {
		std::vector<int> mapLine;
		for (int column = 0; column < csv->GetColumns(line); column++) {
			int c = csv->GetInt(line, column);
			mapLine.push_back(c);
		}
		stage_.push_back(mapLine);
	}
	delete csv;

	hImage_ = LoadGraph("data/image/parts.png");
	assert(hImage_ > 0);
	imageSize_ = VECTOR2(64, 64);

	for (int y = 0; y < stage_.size(); y++) {
		for (int x = 0; x < stage_[y].size(); x++) {
			int c = stage_[y][x];
		}
	}
}

Stage::~Stage()
{
}

void Stage::Update()
{
}

void Stage::Draw()
{
	int w = imageSize_.x;
	int h = imageSize_.y;
	for (int y = 0; y < stage_.size(); y++) {
		for (int x = 0; x < stage_[y].size(); x++) {
			int c = stage_[y][x];
			if (c == 2) {
				DrawRectGraph(x * w, y * h, 3 * w, 1 * h, w, h, hImage_, TRUE);
			}
		}
	}
}
