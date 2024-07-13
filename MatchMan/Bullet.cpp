#include"Bullet.h"
Bullet::Bullet(imgLoadCtrl* imgs)
{
	bulletImg = imgs;
};
Bullet::~Bullet() {};
void Bullet::setLoc(POINT p)
{
	bulletLocation = p;
}
POINT Bullet::getLoc()
{
	return bulletLocation;
}
int Bullet::getAngle()
{
	return angle;
}
void Bullet::setAngle(int a)
{
	angle = a;
}
void Bullet::draw()
{
	bulletImg->draw(&bulletLocation, nowFrameImg);
	nowFrameImg = (nowFrameImg + 1) % imgNum;
}