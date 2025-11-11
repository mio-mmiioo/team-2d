#include "BaseStage.h"
#include <assert.h>
#include "../../../Library/CsvReader.h"
#include "../Player/Player.h"

namespace BASESTAGE {
	char filename[64]; // 生成するcurrentStage_のファイル名
}

BaseStage::BaseStage()
{
	hImage_ = LoadGraph("data/image/parts.png");
	assert(hImage_ > 0);
	imageSize_ = VECTOR2(64, 64);
	isPlayerAlive_ = true; // プレイヤー生きてる
	SetStageData(&baseStage_, "data/stage/baseStage.csv");
	SetStageData(&currentStage_, "data/stage/stage000.csv", BASESTAGE::ADD_X, BASESTAGE::ADD_Y);
}

BaseStage::~BaseStage()
{
	SceneManager::ChangeScene("RESULT");
}

void BaseStage::Update()
{
	if (isPlayerAlive_ == false)
	{
		DestroyMe();
	}
}

void BaseStage::Draw()
{
	int w = imageSize_.x;
	int h = imageSize_.y;

	for (int y = baseStage_.size() - 1 - BASESTAGE::ADD_Y; y >= -BASESTAGE::ADD_Y; y--) {
		for (int x = baseStage_[0].size() - 1; x >= 0; x--) {
			int c = baseStage_[y + BASESTAGE::ADD_Y][x];
			if (c == 2) {
				DrawRectGraph(x * w, y * h, 3 * w, 1 * h, w, h, hImage_, TRUE);
			}
			if (c == 3)
			{
				DrawRectGraph(x * w, y * h, 0, 1 * h, w, h, hImage_, TRUE);
			}
			if (c == 4)
			{
				DrawRectGraph(x * w, y * h, 4 * w, 1 * h, w, h, hImage_, TRUE);
			}
		}
	}
}

int BaseStage::CheckRight(VECTOR2 pos)
{
	if (IsWall(pos) == false) {
		return 0;
	}
	// チップにどれくらいめり込んでいるかを返す
	int x = pos.x / imageSize_.x;
	int dx = pos.x - x * imageSize_.x;
	return dx + 1;
}

int BaseStage::CheckLeft(VECTOR2 pos)
{
	if (IsWall(pos) == false) {
		return 0;
	}
	int x = pos.x / imageSize_.x;
	int dx = pos.x - x * imageSize_.x;
	return imageSize_.x - dx;
}

int BaseStage::CheckDown(VECTOR2 pos)
{
	if (IsWall(pos) == false) {
		return 0;
	}
	int y = pos.y / imageSize_.y;
	int dy = pos.y - y * imageSize_.y;
	return dy + 1;
}

int BaseStage::CheckUp(VECTOR2 pos)
{
	if (IsWall(pos) == false) {
		return 0;
	}
	int y = pos.y / imageSize_.y;
	int dy = pos.y - y * imageSize_.y;
	return imageSize_.y - dy;
}

void BaseStage::ChooseStage(int level)
{
	// プレイヤーのクリアカウント(走った回数)によって、登場させたいstageを変えたいならここで変える
	int nextStageNumber = rand() % 4 + 1;
	CreateStage(nextStageNumber, level);
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
				int py = y * imageSize_.y + imageSize_.y / 2.0f - BASESTAGE::ADD_Y * imageSize_.y;
				new Player(VECTOR2(px, py));
			}
		}
	}
}

void BaseStage::SetStageData(std::vector<std::vector<int>>* stage, const char* filename, int startX, int startY)
{
	stage->clear();
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
			baseStage_[y + startY][x + startX] = (*stage)[y][x];
			if (c == 1) {
				int px = x * imageSize_.x + imageSize_.x / 2.0f;
				int py = y * imageSize_.y + imageSize_.y / 2.0f;
				new Player(VECTOR2(px, py));
			}
		}
	}
}

void BaseStage::CreateStage(int number, int level)
{
	sprintf_s<64>(BASESTAGE::filename, "data/stage/stage%03.csv", number);
	SetStageData(&currentStage_, BASESTAGE::filename, 4, 4);
}


bool BaseStage::IsWall(VECTOR2 pos)
{
	// チップの場所を特定する
	int x = pos.x / imageSize_.x;
	int y = pos.y / imageSize_.y + BASESTAGE::ADD_Y;
	if (y < 0 || y >= baseStage_.size()) {
		return false;
	}
	if (x < 0 || x >= baseStage_[y].size()) {
		return false;
	}
	// チップの番号を見て、壁かどうか確定する 壁じゃない番号を記入する
	switch (baseStage_[y][x]) { 
	case 0:
	case 1:
		return false;
	}
	return true;
}
