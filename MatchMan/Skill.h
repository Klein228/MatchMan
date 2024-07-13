#pragma once
#include"imgLoadCtrl.h"
class Skill
{
public:
	Skill(POINT* initloc, char f, imgLoadCtrl* imgs);
	~Skill();
	void setSpeed(int s);
	void NextLoc();
	void drawSkill();
	POINT getCenter();
private:
	imgLoadCtrl* skillBulletImg;
	POINT location = { 0,0 };
	POINT size = { 0,0 };
	char facing = 'D';
	int nowFrame = 0;
	int maxFrame = 1;
	int speed = 5;
	int last_gn_time = 0;
	int interval_ms = 200;
};