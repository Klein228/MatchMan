#pragma once
#include"imgLoadCtrl.h"
#include"Skill.h"
#include"Bullet.h"
class Player
{
public:
	Player(imgLoadCtrl* imgs, imgLoadCtrl* imgW, int delta_ms, int bulletNum, int bulDis, int bulSpd, int bulinterval_ms, imgLoadCtrl* bulCtrl, imgLoadCtrl* skill);
	~Player();
	void play(ExMessage msg);
	POINT getCenterloc();
	std::vector<POINT>* getBulletLoc();
	std::vector<POINT>* getSkillLoc();
	void plrdraw(int ticknow, bool Touched);
	POINT getPoint();
	POINT getplayerSize();
	void setBulletsLoc();
	void setBulletAngle();
	void addAngle(int d);
	int getSkillDistance();
private:
	int interval_ms = 0;
	imgLoadCtrl* playerIMG;
	imgLoadCtrl* playerIMGwhite;
	bool touched = false;
	int white_continue_time_ms = 2000;
	int white_begin_time_ms = 0;
	bool last_white_frame = false;
	POINT plr_location = { 640,320 };//玩家当前位置记录
	char Facing = 'D';
	POINT direction_vector = { 0,0 };
	POINT plrSize = { 80,120 };
	unsigned char plrMovespeed = 3;
	//const double ObliqueVector = 1.0 / sqrt(2);
	int playerImgNum = 6;
	int last_time = 0;
	int plrFrameNum = 0;//玩家图片当前渲染帧数

	bool plrMoveRight = false;
	bool plrMoveLeft = false;
	bool plrMoveUp = false;
	bool plrMoveDown = false;
	//子弹
	imgLoadCtrl* bulletsImgs;
	std::vector<Bullet*> bullets;
	std::vector<POINT> bulletsLocation;
	int bulletsLast_refresh_time = 0;
	int bullet_interval_ms = 10;
	int bulletsNum = 0;
	int bulletDistance = 100;
	int bulletVSpeed = 1;
	int waveDistance = 0;
	const int waveAraeMax = 30;
	bool waveUp = true;
	int bulletSpeed = 5;
	//技能
	imgLoadCtrl* skillImg;
	std::vector<Skill*> skills;
	std::vector<POINT> skillsLocation;
	int skillDistance = 50;
};