#include "Object2D.h"

Object2D::Object2D()
{
	hImage_ = -1;
	anim_ = { 0, 0 };
	position_ = { 0, 0 };
	imageSize_ = { 0, 0 };
}

Object2D::~Object2D()
{
}

void Object2D::Update()
{
}

void Object2D::Draw()
{
	if (hImage_ > 0) {
		int x = position_.x - imageSize_.x / 2.0f;
		int y = position_.y - imageSize_.y / 2.0f;

		DrawRectGraph(x, y, anim_.x * imageSize_.x, anim_.y * imageSize_.y, imageSize_.x, imageSize_.y, hImage_, TRUE);
	}
}
