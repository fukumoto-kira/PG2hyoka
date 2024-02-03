#pragma once
#include<Vector2.h>
#include<Novice.h>

class Enemy
{
public:
	Enemy();
	~Enemy();

	void Update();
	void Draw();

	Vector2 GetPos() { return Pos_; };
	int GetRadius() { return Radius_; };
	void SetisAlive(bool isAlive);

private:
	Vector2 Pos_;
	int Speed_;
	int Radius_;
	static bool isAlive_;
	int CT_;
};

