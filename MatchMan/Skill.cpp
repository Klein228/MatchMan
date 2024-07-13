#include"Skill.h"

Skill::Skill(POINT* initloc, char f, imgLoadCtrl* imgs)
{
	location = *initloc;
	facing = f;
	skillBulletImg = imgs;
	size = { imgs->getImages()->at(nowFrame)->getwidth(),imgs->getImages()->at(nowFrame)->getheight() };
}
Skill::~Skill() {}
void Skill::setSpeed(int s)
{
	speed = s;
}
void Skill::NextLoc()
{
	if (GetTickCount() - last_gn_time < interval_ms)return;
	switch (facing)
	{
	case 'D':
		location.x += speed;
		break;
	case 'A':
		location.x -= speed;
		break;
	case 'W':
		location.y -= speed;
		break;
	case 'S':
		location.y += speed;
		break;
	default:
		location.x += speed;
		break;
	}
}
void Skill::drawSkill()
{
	skillBulletImg->draw(&location, nowFrame);
	nowFrame = (nowFrame + 1) % maxFrame;
	//last_gn_time = GetTickCount();
}
POINT Skill::getCenter()
{
	return { location.x + size.x,location.y + size.y };
}