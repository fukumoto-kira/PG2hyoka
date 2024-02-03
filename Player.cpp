#include "Player.h"

Player::Player()
{
	Pos_ = { 360,600 };
	Speed_ = 5;
	Radius_ = 20;



	keys[256] = { 0 };
	preKeys[256] = { 0 };
}

Player::~Player()
{
}

void Player::Update()
{
	Move();
}

void Player::Draw()
{
	Novice::DrawEllipse((int)Pos_.x, (int)Pos_.y, Radius_, Radius_, 0, WHITE, kFillModeSolid);
}

void Player::Move()
{
	// キー入力を受け取る
	memcpy(preKeys, keys, 256);
	Novice::GetHitKeyStateAll(keys);

	if (keys[DIK_W])
	{
		Pos_.y -= Speed_;
	}
	if (keys[DIK_S])
	{
		Pos_.y += Speed_;
	}
	if (keys[DIK_A])
	{
		Pos_.x -= Speed_;
	}
	if (keys[DIK_D])
	{
		Pos_.x += Speed_;
	}
}

void Player::SetPos(Vector2 Pos)
{
	Pos_ = Pos;
}


