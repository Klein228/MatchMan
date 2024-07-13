#pragma once
#include"imgLoadCtrl.h"
#include"Enemy.h"
#include<random>
class EnemyCtrl
{
public:
	EnemyCtrl(int time, int interval, imgLoadCtrl* enemyImgR,imgLoadCtrl* enemyImgL,imgLoadCtrl* imgRfrozen, imgLoadCtrl* imgLfrozen);
	~EnemyCtrl();
	void generateEnemy();
	bool runtoplayer(Player* p);
	int touchBullets(Player* p);
	void touchSkills(Player* p);
	void enemiesDraw();
private:
	std::vector<Enemy*> enemies;
	imgLoadCtrl* EnemyImgR;
	imgLoadCtrl* EnemyImgL;
	imgLoadCtrl* EnemyImgRf;
	imgLoadCtrl* EnemyImgLf;
	int last_generate_time = 0;
	const int enemyFrameNum = 4;
	int generate_interval_time = 2000;
	int Frameinterval = 45;
	std::wstring path = L"img/enemy";
	POINT locationGenerate(int frameWidth, int frameHeight);
};