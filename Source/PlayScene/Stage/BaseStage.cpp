#include "BaseStage.h"
#include <assert.h>
#include "../../../Library/CsvReader.h"
#include "../Player/Player.h"


BaseStage::BaseStage()
{
	CsvReader* csv = new CsvReader("data/stage/baseStage.csv");
	for (int line = 0; line < csv->GetLines(); line++) {
		std::vector<int> mapLine;
		for (int column = 0; column < csv->GetColumns(line); column++) {
			int c = csv->GetInt(line, column);
			mapLine.push_back(c);
		}
		baseStage_.push_back(mapLine);
	}
	delete csv;

	hImage_ = LoadGraph("data/image/parts.png");
	assert(hImage_ > 0);
	imageSize_ = VECTOR2(64, 64);

	for (int y = 0; y < baseStage_.size(); y++) {
		for (int x = 0; x < baseStage_[y].size(); x++) {
			int c = baseStage_[y][x];
			if (c == 1) {
				int px = x * imageSize_.x + imageSize_.x / 2.0f;
				int py = y * imageSize_.y + imageSize_.y / 2.0f;
				new Player(VECTOR2(px, py));
			}
		}
	}
}

BaseStage::~BaseStage()
{
}

void BaseStage::Update()
{
}

void BaseStage::Draw()
{
	int w = imageSize_.x;
	int h = imageSize_.y;
	for (int y = 0; y < baseStage_.size(); y++) {
		for (int x = 0; x < baseStage_[y].size(); x++) {
			int c = baseStage_[y][x];
			if (c == 2) {
				DrawRectGraph(x * w, y * h, 3 * w, 1 * h, w, h, hImage_, TRUE);
			}
		}
	}
}

void BaseStage::ChooseStage()
{
}
