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
	void ChooseStage(); // ランダムな値を入手して次のステージを生成するための変数

	std::vector<std::vector<int>> baseStage_; // ステージの両端の部分

	int hImage_;
};