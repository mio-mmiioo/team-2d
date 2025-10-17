#include "Player.h"
#include "../Stage/BaseStage.h"
#include <assert.h>
#include "../../../Library/Input.h"

namespace PLAYER {
	float moveSpeed = 1.0f;
}

Player::Player(VECTOR2 pos)
{
	hImage_ = LoadGraph("data/image/tamadot.png");
	assert(hImage_ > 0);

	imageSize_ = VECTOR2(64, 64);
	anim_ = { 0, 0 };
	position_ = pos;
}

Player::~Player()
{
}

void Player::Update()
{
	VECTOR2 move;
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

	position_ = position_ + (move * PLAYER::moveSpeed);

	// ステージとの当たり判定・位置修正
	{
		BaseStage* st = FindGameObject<BaseStage>();

		if (move.x < 0)
		{
			int push = st->CheckLeft(position_ + VECTOR2(-24, -31)); // 左上
			position_.x += push;
			push = st->CheckLeft(position_ + VECTOR2(-24, 31)); // 左下
			position_.x += push;
		}
		if (move.x > 0)
		{
			int push = st->CheckRight(position_ + VECTOR2(24, -31)); // 右上
			position_.x -= push;
			push = st->CheckRight(position_ + VECTOR2(24, 31)); // 右下
			position_.x -= push;
		}
		if (move.y < 0)
		{
			int push = st->CheckUp(position_ + VECTOR2(24, -32)); // 右上
			position_.y += push;
			push = st->CheckUp(position_ + VECTOR2(-24, -32)); // 左上
			position_.y += push;
		}
		if (move.y > 0)
		{
			int push = st->CheckDown(position_ + VECTOR2(24, 32)); // 右下
			position_.y -= push;
			push = st->CheckDown(position_ + VECTOR2(-24, 32)); // 左下
			position_.y -= push;
		}
	}



}

void Player::Draw()
{
	Object2D::Draw();

	DrawBox(position_.x - 24, position_.y - 32, position_.x + 24, position_.y + 32, GetColor(255, 0, 0), FALSE); // 当たり判定の線
}
