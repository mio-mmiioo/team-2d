#pragma once
#include "../../../Library/Object2D.h"
#include <vector>

class BaseStage : public Object2D {
public:
	BaseStage();
	~BaseStage();
	void Update() override;
	void Draw() override;

private:
	void SetStageData(std::vector<std::vector<int>> *stage, const char* filename); // ステージデータをセットするための関数
	void CreateStage(int number);
	void ChooseStage(); // ランダムな値を入手して次のステージを生成するための変数

	std::vector<std::vector<int>> baseStage_; // ステージの両端の部分
	std::vector<std::vector<int>> currentStage_; // 現在のステージ

	int hImage_;
};