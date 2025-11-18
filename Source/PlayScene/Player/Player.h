#pragma once
#include "../../../Library/Object2D.h"

class Player : public Object2D {
public:
	Player(VECTOR2 pos);
	~Player();
	void Update() override;
	void Draw() override;
private:
	bool IsClear();			// ステージをクリアできたか 時間内に線を踏むことができたか
	void SoundShuttleRun(); // soundTimer_をもとにシャトルランの音を再現する
	void SetSoundTime();

	int hp_;
	float timer_;			// 9の倍数にして
	float soundScaleTimer_;	// timer_を9等分したくらいの時間
	int soundScaleCounter_;	// 音階で鳴らすためのカウンター
	bool isGoRight_;		// true→右に進んでいる false→左に進んでいる
	int counter_;			// クリア(線を踏んだ)回数

	// 重力関連
	bool onGround_;			// 地面に足がついている
	float velocityY_;
	float jumpV0;			// ジャンプの高さ

	// 開始音
	float startTimer_;		// 開始音を鳴らすタイマー
	int soundStartCounter_;	// 音を鳴らす回数をカウントする

	// アニメーション関連
	float animTimer_;

	// データ作成しやすくする関連
	int nextStageNumber_;
	int flagNumber_;
};