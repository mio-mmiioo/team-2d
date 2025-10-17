#include "Player.h"
#include "../Stage/BaseStage.h"
#include <assert.h>
#include "../../../Library/Input.h"

namespace PLAYER {
	float moveSpeed = 1.0f;
	int halfSizeX = 24;
	const int MAX_HP = 2;
}

Player::Player(VECTOR2 pos)
{
	hImage_ = LoadGraph("data/image/tamadot.png");
	assert(hImage_ > 0);

	imageSize_ = VECTOR2(64, 64);
	anim_ = { 0, 0 };
	position_ = pos;
	hp_ = PLAYER::MAX_HP; // シャトルランは2回失敗したら失格
	soundTimer_ = 9.0f; // 9回音を鳴らす、この書き方よくないかも、、、
	isGoRight_ = true; // 最初は右に進む
	counter_ = 0;
}

Player::~Player()
{
}

void Player::Update()
{
	soundTimer_ -= Time::DeltaTime();
	VECTOR2 move;

	// キーの入力
	{
		if (Input::IsKeyKeep(KEY_INPUT_D))
		{
			move.x += 1;
		}
		if (Input::IsKeyKeep(KEY_INPUT_A))
		{
			move.x -= 1;
		}
		if (Input::IsKeyKeep(KEY_INPUT_W))
		{
			move.y -= 1;
		}
		if (Input::IsKeyKeep(KEY_INPUT_S))
		{
			move.y += 1;
		}

		if (Input::IsKeyDown(KEY_INPUT_G)) // 雑にプレイヤーを殺害
		{
			hp_ -= 1;
		}
	}

	position_ = position_ + (move * PLAYER::moveSpeed);

	BaseStage* st = FindGameObject<BaseStage>();

	// ステージとの当たり判定・位置修正
	{
		if (move.x < 0)
		{
			int push = st->CheckLeft(position_ + VECTOR2(-PLAYER::halfSizeX, -(imageSize_.y / 2 - 1))); // 左上
			position_.x += push;
			push = st->CheckLeft(position_ + VECTOR2(-PLAYER::halfSizeX, imageSize_.y / 2 - 1)); // 左下
			position_.x += push;
		}
		if (move.x > 0)
		{
			int push = st->CheckRight(position_ + VECTOR2(PLAYER::halfSizeX, -(imageSize_.y / 2 - 1))); // 右上
			position_.x -= push;
			push = st->CheckRight(position_ + VECTOR2(PLAYER::halfSizeX, imageSize_.y / 2 - 1)); // 右下
			position_.x -= push;
		}
		if (move.y < 0)
		{
			int push = st->CheckUp(position_ + VECTOR2(PLAYER::halfSizeX, -(imageSize_.y / 2))); // 右上
			position_.y += push;
			push = st->CheckUp(position_ + VECTOR2(-PLAYER::halfSizeX, -(imageSize_.y / 2))); // 左上
			position_.y += push;
		}
		if (move.y > 0)
		{
			int push = st->CheckDown(position_ + VECTOR2(PLAYER::halfSizeX, imageSize_.y / 2 - 1)); // 右下
			position_.y -= push;
			push = st->CheckDown(position_ + VECTOR2(-PLAYER::halfSizeX, imageSize_.y / 2 - 1)); // 左下
			position_.y -= push;
		}
	}



	if (soundTimer_ <= 0)
	{

		// ステージをクリアできたか確認
		if (IsClear() == false)
		{
			hp_ -= 1;
		}
		else
		{
			if (hp_ < PLAYER::MAX_HP)
			{
				hp_ = PLAYER::MAX_HP;
			}
		}

		if (hp_ <= 0)
		{
			st->SetPlayerAlive(false);
			DestroyMe();
		}
		// ステージをセット
		st->ChooseStage(0); // 現段階では機能してない

		// 向かう方向を変更
		if (isGoRight_ == true)
		{
			isGoRight_ = false;
		}
		else
		{
			isGoRight_ = true;
		}
		soundTimer_ = 9.0f;
	}
}

void Player::Draw()
{
	Object2D::Draw();

	DrawBox(position_.x - 24, position_.y - 32, position_.x + 24, position_.y + 32, GetColor(255, 0, 0), FALSE); // 当たり判定の線
	DrawFormatString(100, 100, GetColor(255, 255, 255), "%04f", soundTimer_);
	DrawFormatString(100, 120, GetColor(255, 255, 255), "%04d", counter_);
	DrawFormatString(100, 140, GetColor(255, 255, 255), "%04d", hp_);
}

bool Player::IsClear()
{
	counter_ += 1;
	if (isGoRight_ == true) // 右に進んでいる場合
	{
		if (BASESTAGE::LINE_POS_RIGHT <= position_.x)
		{
			return true;
		}
	}
	else // 左に進んでいる場合
	{
		if (BASESTAGE::LINE_POS_LEFT >= position_.x)
		{
			return true;
		}
	}
	return false;
}
