#pragma once
#include"imgLoadCtrl.h"
#include"Player.h"
class Enemy
{
public:
	Enemy(imgLoadCtrl* imgRight, imgLoadCtrl* imgLeft, int delta_ms, POINT loc);
	~Enemy();
	POINT getCenterloc();
	bool getAlive();
	bool movetoplayer(Player* p);
	bool touchedByBullet(Player* p);
	bool touchedBySkill(Player* p);
	void draw(int ticknow);
private:
	int interval_ms = 0;
	imgLoadCtrl* enemyIMGRight;
	imgLoadCtrl* enmyImgLeft;
	std::pair<double, double> enemy_location = { -60.0,-60.0 };
	std::pair<double, double> direction_vector = { 0,0 };
	POINT enemySize = { 50,50 };
	unsigned char enemyMovespeed = 1;
	bool alive = true;
	int enemyIMGNum = 4;
	int enemyFrameNum = 0;
	int last_time = 0;
	bool facingRight = true;
};