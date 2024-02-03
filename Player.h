#pragma once
#include<Vector2.h>
#include<Novice.h>

class Player
{
public:
	Player();
	~Player();

	void Update();
	void Draw();
	void Move();

	Vector2 GetPos() { return Pos_; };
	int GetRadius() { return Radius_; };
	void SetPos(Vector2 Pos);
	
private:
	Vector2 Pos_;
	int Speed_;
	int Radius_;



	// キー入力結果を受け取る箱
	char keys[256];
	char preKeys[256];

};

