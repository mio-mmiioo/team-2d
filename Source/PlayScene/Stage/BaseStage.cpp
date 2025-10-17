#include "BaseStage.h"
#include <assert.h>
#include "../../../Library/CsvReader.h"
#include "../Player/Player.h"

namespace BASESTAGE {
	char filename[64]; // 生成するcurrentStage_のファイル名
	const int LINE_POS_LEFT = 256; // currentStageを描画し始める位置を設定
}

BaseStage::BaseStage()
{
	hImage_ = LoadGraph("data/image/parts.png");
	assert(hImage_ > 0);
	imageSize_ = VECTOR2(64, 64);

	SetStageData(&baseStage_, "data/stage/baseStage.csv");
	CreateStage(1); // 最初のステージを生成
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

	for (int y = 0; y < currentStage_.size(); y++) {
		for (int x = 0; x < currentStage_[y].size(); x++) {
			int c = currentStage_[y][x];
			if (c == 2) {
				DrawRectGraph(x * w + BASESTAGE::LINE_POS_LEFT, y * h, 3 * w, 1 * h, w, h, hImage_, TRUE);
			}
		}
	}
}

void BaseStage::SetStageData(std::vector<std::vector<int>> *stage, const char* filename)
{
	CsvReader* csv = new CsvReader(filename);
	for (int line = 0; line < csv->GetLines(); line++) {
		std::vector<int> mapLine;
		for (int column = 0; column < csv->GetColumns(line); column++) {
			int c = csv->GetInt(line, column);
			mapLine.push_back(c);
		}
		stage->push_back(mapLine);
	}
	delete csv;

	for (int y = 0; y < stage->size(); y++) {
		for (int x = 0; x < (*stage)[y].size(); x++) {
			int c = (*stage)[y][x];
			if (c == 1) {
				int px = x * imageSize_.x + imageSize_.x / 2.0f;
				int py = y * imageSize_.y + imageSize_.y / 2.0f;
				new Player(VECTOR2(px, py));
			}
		}
	}
}

void BaseStage::CreateStage(int number)
{
	sprintf_s<64>(BASESTAGE::filename, "data/stage/stage%02d.csv", number);
	SetStageData(&currentStage_, BASESTAGE::filename);
}

void BaseStage::ChooseStage()
{
}
