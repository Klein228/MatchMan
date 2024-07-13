#pragma once
#include"imgLoadCtrl.h"
#include"Enemy.h"
#include<random>
class EnemyCtrl
{
public:
	EnemyCtrl(int time, int interval, imgLoadCtrl* enemyImgR,imgLoadCtrl* enemyImgL);
	~EnemyCtrl();
	void generateEnemy();
	bool runtoplayer(Player* p);
	int touchBullets(Player* p);
	int touchSkills(Player* p);
	void enemiesDraw();
private:
	std::vector<Enemy*> enemies;
	imgLoadCtrl* EnemyImgR;
	imgLoadCtrl* EnemyImgL;
	int last_generate_time = 0;
	const int enemyFrameNum = 4;
	int generate_interval_time = 2000;
	int Frameinterval = 45;
	std::wstring path = L"img/enemy";
	POINT locationGenerate(int frameWidth, int frameHeight);
};