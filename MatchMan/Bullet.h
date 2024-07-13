#pragma once
#include"Bullet.h"
#include<graphics.h>
#include"imgLoadCtrl.h"
class Bullet
{
public:
	Bullet(imgLoadCtrl* imgs);
	~Bullet();
	void setLoc(POINT p);
	POINT getLoc();
	int getAngle();
	void setAngle(int a);
	void draw();
private:
	const int imgNum = 1;
	int nowFrameImg = 0;
	POINT bulletLocation = { -100,-100 };
	POINT bulletSize = { 20,20 };
	int angle = 0;
	imgLoadCtrl* bulletImg;
};