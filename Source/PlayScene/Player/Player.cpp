#include "Player.h"
#include "../Stage/Stage.h"
#include <assert.h>
#include "../../../Library/Input.h"

namespace PLAYER {
	float moveSpeed = 0.5f;
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
		move.y -= 1;
	}

	position_ = move * PLAYER::moveSpeed;
}

void Player::Draw()
{
	Object2D::Draw();
	Stage* st = FindGameObject<Stage>();
	DrawBox(position_.x - 24, position_.y - 32, position_.x + 24, position_.y + 32, GetColor(255, 0, 0), FALSE); // ìñÇΩÇËîªíËÇÃê¸
}
