#include "Player.h"
#include "../Stage/Stage.h"
#include <assert.h>
#include "../../../Library/Input.h"

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
}

void Player::Draw()
{
	Object2D::Draw();
	Stage* st = FindGameObject<Stage>();
	DrawBox(position_.x - 24, position_.y - 32, position_.x + 24, position_.y + 32, GetColor(255, 0, 0), FALSE);
}
