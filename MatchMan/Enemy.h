#pragma once
#include"imgLoadCtrl.h"
#include"Player.h"
class Enemy
{
public:
	Enemy(imgLoadCtrl* imgRight, imgLoadCtrl* imgLeft,imgLoadCtrl* imgRfrozen,imgLoadCtrl* imgLfrozen, int delta_ms, POINT loc);
	~Enemy();
	POINT getCenterloc();
	bool getAlive();
	bool movetoplayer(Player* p);
	bool touchedByBullet(Player* p);
	void touchedBySkill(Player* p);
	void draw(int ticknow);
private:
	int interval_ms = 0;
	imgLoadCtrl* enemyIMGRight;
	imgLoadCtrl* enmyImgLeft;
	imgLoadCtrl* enemyIMGRightFrozen;
	imgLoadCtrl* enmyImgLeftFrozen;
	std::pair<double, double> enemy_location = { -60.0,-60.0 };
	std::pair<double, double> direction_vector = { 0,0 };
	POINT enemySize = { 50,50 };
	unsigned char enemyMovespeed = 1;
	bool alive = true;
	int enemyIMGNum = 4;
	int enemyFrameNum = 0;
	int last_time = 0;
	bool facingRight = true;


	bool frozened = false;
	int last_frozened_time_ms = 0;
	int frozen_continue_time_ms = 2000;
	int frozen_frame = 0;
};