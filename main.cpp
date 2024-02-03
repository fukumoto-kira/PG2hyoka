#include <Novice.h>
#include"Player.h"
#include<Vector2.h>
#include"Enemy.h"

const char kWindowTitle[] = "LC1B_21_フクモト_キラ";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	Enemy* enemy = new Enemy;
	Player* player = new Player;

	const int MaxBullet = 20;
	float BulletPosX[MaxBullet] = { 0 };
	float BulletPosY[MaxBullet] = { 0 };
	int BulletSpeed = 10;
	int BulletRadius = 10;
	int BulletAlive[MaxBullet] = { 0 };
	int count = -1;
	int Kill = 0;
	float distX = 0;
	float distY = 0;
	float dist = 0;
	int radius = 0;

	enum Scene {
		TITLE,
		GAME,
		CLEAR,
		GAMEOVER
	};
	int scene = TITLE;

	int title = Novice::LoadTexture("./resource/PG2 title.png");
	int clear = Novice::LoadTexture("./resource/clear.png");
	int gameover = Novice::LoadTexture("./resource/gameover.png");

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///
		switch (scene)
		{
		case TITLE:
			if (keys[DIK_SPACE] && preKeys[DIK_SPACE] == 0)
			{
				scene = GAME;
				player->SetPos({ 360,600 });
				Kill = 0;
			}

			break;
		case GAME:
			
			enemy->Update();
			player->Update();

			if (keys[DIK_SPACE] && preKeys[DIK_SPACE] == 0)
			{
				count++;
				if (count == MaxBullet + 1)
				{
					count = 0;
				}
				BulletAlive[count] = 1;
				BulletPosX[count] = player->GetPos().x;
				BulletPosY[count] = player->GetPos().y;
			}
			for (int i = 0; i < MaxBullet; i++)
			{
				if (BulletAlive[i] == 1)
				{
					BulletPosY[i] -= BulletSpeed;

					distX = float(BulletPosX[i] - enemy->GetPos().x);
					distY = float(BulletPosY[i] - enemy->GetPos().y);
					dist = (distX * distX) + (distY * distY);
					radius = BulletRadius + enemy->GetRadius();
					if (dist <= radius * radius) {
						enemy->SetisAlive(false);
						BulletAlive[i] = 0;
						Kill++;
						if (Kill == 3)
						{
							scene = CLEAR;
						}
					}
				}
			}
			distX = float(player->GetPos().x - enemy->GetPos().x);
			distY = float(player->GetPos().y - enemy->GetPos().y);
			dist = (distX * distX) + (distY * distY);
			radius = player->GetRadius() + enemy->GetRadius();
			if (dist <= radius * radius) {
				scene = GAMEOVER;
			}

			break;
		case CLEAR:
			if (keys[DIK_SPACE] && preKeys[DIK_SPACE] == 0)
			{
				scene = TITLE;

			}
			break;
		case GAMEOVER:
			if (keys[DIK_SPACE] && preKeys[DIK_SPACE] == 0)
			{
				scene = TITLE;

			}
			break;
		}
		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///
		switch (scene)
		{
		case TITLE:
			Novice::DrawSprite(0, 0, title, 1, 1, 0.0f, WHITE);
			break;

		case GAME:
			for (int i = 0; i < MaxBullet; i++)
			{
				if (BulletAlive[i] == 1)
				{
					Novice::DrawEllipse((int)BulletPosX[i], (int)BulletPosY[i], BulletRadius, BulletRadius, 0, WHITE, kFillModeSolid);
				}

			}
			player->Draw();
			enemy->Draw();

			break;
		case CLEAR:
			Novice::DrawSprite(0, 0, clear, 1, 1, 0.0f, WHITE);
			break;
		case GAMEOVER:
			Novice::DrawSprite(0, 0, gameover, 1, 1, 0.0f, WHITE);
			break;
		}
		
		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	delete player;
	delete enemy;

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
