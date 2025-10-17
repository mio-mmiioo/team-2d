#pragma once
#include "../../../Library/Object2D.h"
#include <vector>

class BaseStage : public Object2D {
public:
	BaseStage();
	~BaseStage();
	void Update() override;
	void Draw() override;

	int CheckRight(VECTOR2 pos);
	int CheckLeft(VECTOR2 pos);
	int CheckDown(VECTOR2 pos);
	int CheckUp(VECTOR2 pos);

private:
	void SetStageData(std::vector<std::vector<int>> *stage, const char* filename); // ステージデータをセットするための関数
	void SetStageData(std::vector<std::vector<int>>* stage, const char* filename, int startX, int startY);
	void CreateStage(int number); // ステージを作成する
	void ChooseStage(); // ランダムな値を入手して次のステージを生成するための変数
	bool IsWall(VECTOR2 pos); // 壁かどうか

	std::vector<std::vector<int>> baseStage_; // ステージの両端の部分
	std::vector<std::vector<int>> currentStage_; // 現在のステージ

	int hImage_;
};