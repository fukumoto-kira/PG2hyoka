#include "Enemy.h"

bool Enemy::isAlive_ = true;

Enemy::Enemy()
{
	Pos_ = { 360,300 };
	Speed_ = 10;
	Radius_ = 20;
	isAlive_ = true;
	CT_ = 60;
}

Enemy::~Enemy()
{
}

void Enemy::Update()
{
	Pos_.x += Speed_;
	if (1280 - Radius_ <= Pos_.x || 0 + Radius_ >= Pos_.x)
	{
		Speed_ *= -1;
	}
	if (isAlive_ == false)
	{
		CT_--;
		if (CT_ == 0)
		{
			isAlive_ = true;
			CT_ = 60;
		}
	}
}

void Enemy::Draw()
{
	if (isAlive_ == true) {
		Novice::DrawEllipse((int)Pos_.x, (int)Pos_.y, Radius_, Radius_, 0, RED, kFillModeSolid);
	}
}

void Enemy::SetisAlive(bool isAlive)
{
	isAlive_ = isAlive;
}
