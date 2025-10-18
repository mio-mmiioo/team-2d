#include "Player.h"
#include "../Stage/BaseStage.h"
#include <assert.h>
#include "../../../Library/Input.h"
#include "../../Sound.h"
#include "../../Screen.h" // プレイヤーが画面外に出ていないか判定するのに使用

namespace PLAYER {
	float moveSpeed = 1.0f;
	int halfSizeX = 24;
	const int MAX_HP = 2;

	const float GRAVITY = 0.05f;
	const float JUMP_HEIGHT = 64.0f * 2.0f;//ブロックの高さ基準
	const float JUMP_V0 = -sqrtf(2.0f * GRAVITY * JUMP_HEIGHT);
}

Player::Player(VECTOR2 pos)
{
	hImage_ = LoadGraph("data/image/tamadot.png");
	assert(hImage_ > 0);

	imageSize_ = VECTOR2(64, 64);
	anim_ = { 0, 0 };
	position_ = pos;
	hp_ = PLAYER::MAX_HP; // シャトルランは2回失敗したら失格
	soundTimer_ = 9.0f;   // 9回音を鳴らす、この書き方よくないかも、、、
	isGoRight_ = true;	  // 最初は右に進む
	counter_ = 0;
	onGround_ = false;
	velocityY_ = 0;
}

Player::~Player()
{
}

void Player::Update()
{
	soundTimer_ -= Time::DeltaTime();
	
	SoundShuttleRun(); // まだ中身書いてない

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

		if (onGround_ == true)
		{
			if (Input::IsKeyDown(KEY_INPUT_SPACE))
			{
				velocityY_ = PLAYER::JUMP_V0;
			}
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
		// 左右のめり込み判定
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
		}

		// 重力をかける
		position_.y += velocityY_;
		velocityY_ += PLAYER::GRAVITY;
		onGround_ = false;
		
		// 上下のめり込み判定
		{
			if (velocityY_ < 0.0f)
			{
				int push = st->CheckUp(position_ + VECTOR2(PLAYER::halfSizeX, -(imageSize_.y / 2))); // 右上
				if (push > 0)
				{
					velocityY_ = 0.0f;
					position_.y += push;
				}
				push = st->CheckUp(position_ + VECTOR2(-PLAYER::halfSizeX, -(imageSize_.y / 2))); // 左上
				if (push > 0)
				{
					velocityY_ = 0.0f;
					position_.y += push;
				}
			}
			else
			{
				int push = st->CheckDown(position_ + VECTOR2(PLAYER::halfSizeX, imageSize_.y / 2)); // 右下
				if (push > 0)
				{
					onGround_ = true;
					velocityY_ = 0.0f;
					position_.y -= push - 1;
				}
				push = st->CheckDown(position_ + VECTOR2(-PLAYER::halfSizeX, imageSize_.y / 2)); // 左下
				if (push > 0)
				{
					onGround_ = true;
					velocityY_ = 0.0f;
					position_.y -= push - 1;
				}
			}
		}

		// 画面外にプレイヤーを行かせないように位置を修正
		{
			if (position_.x < PLAYER::halfSizeX)
			{
				position_.x = PLAYER::halfSizeX;
			}
			else if (position_.x > Screen::WIDTH - PLAYER::halfSizeX)
			{
				position_.x = Screen::WIDTH - PLAYER::halfSizeX;
			}
		}
	}

	// クリア判定など
	if (soundTimer_ <= 0)
	{
		// ステージをクリアできたか確認
		if (IsClear() == false)
		{
			hp_ -= 1;

			// 本来のゴール地点にワープさせる
			if (isGoRight_ == true)
			{
				position_.x = BASESTAGE::LINE_POS_RIGHT + imageSize_.x;
			}
			else
			{
				position_.x = BASESTAGE::LINE_POS_LEFT - imageSize_.x;
			}
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
	DrawFormatString(100, 120, GetColor(255, 255, 255), "カウンター：%04d", counter_);
	DrawFormatString(100, 140, GetColor(255, 255, 255), "HP：%04d", hp_);


	DrawLine(BASESTAGE::LINE_POS_LEFT, 0, BASESTAGE::LINE_POS_LEFT, Screen::HEIGHT, GetColor(255, 255, 255));
	DrawLine(BASESTAGE::LINE_POS_RIGHT, 0, BASESTAGE::LINE_POS_RIGHT, Screen::HEIGHT, GetColor(255, 255, 255));

	if (isGoRight_)
	{
		DrawFormatString(100, 160, GetColor(255, 255, 255), "みぎに進む");
		DrawLine(BASESTAGE::LINE_POS_RIGHT, 0, BASESTAGE::LINE_POS_RIGHT, Screen::HEIGHT, GetColor(255, 0, 0));
	}
	else
	{
		DrawFormatString(100, 160, GetColor(255, 255, 255), "ひだりに進む");
		DrawLine(BASESTAGE::LINE_POS_LEFT, 0, BASESTAGE::LINE_POS_LEFT, Screen::HEIGHT, GetColor(255, 0, 0));
	}

	if (onGround_)
	{
		DrawFormatString(100, 180, GetColor(255, 255, 255), "地面に足がついている");
	}
	else
	{
		DrawFormatString(100, 180, GetColor(255, 255, 255), "地面に足が付いていない");
	}
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

void Player::SoundShuttleRun()
{
	if (isGoRight_ == true) // 1,2,3,...
	{

	}
	else // 8,7,6,...
	{

	}
}
