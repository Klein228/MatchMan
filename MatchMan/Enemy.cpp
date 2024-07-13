#include"Enemy.h"

Enemy::Enemy(imgLoadCtrl* imgRight, imgLoadCtrl* imgLeft, imgLoadCtrl* imgRfrozen, imgLoadCtrl* imgLfrozen, int delta_ms, POINT loc)
{
	interval_ms = delta_ms;
	enemyIMGRight = imgRight;
	enmyImgLeft = imgLeft;
	enmyImgLeftFrozen = imgLfrozen;
	enemyIMGRightFrozen = imgRfrozen;
	TCHAR plrpath[256];
	enemy_location.first = loc.x;
	enemy_location.second = loc.y;
};
Enemy::~Enemy() {};
POINT Enemy::getCenterloc()
{
	return { static_cast<long>(enemy_location.first) + enemySize.x / 2, static_cast<long>(enemy_location.second) + enemySize.y / 2 };
}
bool Enemy::getAlive()
{
	return alive;
}
bool Enemy::movetoplayer(Player* p)
{
	POINT playerCenter = p->getCenterloc();
	POINT enemycenter = getCenterloc();
	direction_vector = { playerCenter.x - enemycenter.x,playerCenter.y - enemycenter.y };
	if (direction_vector.first > 0)facingRight = true;
	else facingRight = false;
	if ((playerCenter.x <= enemy_location.first + enemySize.x) && (playerCenter.x >= enemy_location.first) &&
		(playerCenter.y <= enemy_location.second + enemySize.y) && (playerCenter.y >= enemy_location.second))
	{
		return true;
	}
	if(!frozened)
	{
		enemy_location.first += enemyMovespeed * (direction_vector.first / sqrt(direction_vector.first * direction_vector.first + direction_vector.second * direction_vector.second));
		enemy_location.second += enemyMovespeed * (direction_vector.second / sqrt(direction_vector.first * direction_vector.first + direction_vector.second * direction_vector.second));
	}
	return false;
}
bool Enemy::touchedByBullet(Player* p)
{
	for (size_t i = 0; i < p->getBulletLoc()->size(); i++)
	{
		POINT bulletLocation = p->getBulletLoc()->at(i);
		if ((bulletLocation.x <= (enemy_location.first + enemySize.x)) &&
			(bulletLocation.x >= enemy_location.first) &&
			(bulletLocation.y <= (enemy_location.second + enemySize.y)) &&
			(bulletLocation.y >= enemy_location.second))
		{
			alive = false;
			mciSendString(_T("play hit from 0"), NULL, 0, NULL);
			return true;
		}
	}
	return false;
}
void Enemy::touchedBySkill(Player* p)
{
	int d = p->getSkillDistance();
	for (size_t i = 0; i < p->getSkillLoc()->size(); i++)
	{
		POINT skillLocation = p->getSkillLoc()->at(i);
		POINT delta = { skillLocation.x - enemy_location.first,skillLocation.y - enemy_location.second };

		if (sqrt(delta.x * delta.x + delta.y * delta.y) < d)
		{
			//alive = false;
			if (!frozened)
			{
				mciSendString(_T("play hit from 0"), NULL, 0, NULL);
				frozen_frame = enemyFrameNum;
				frozened = true;
				last_frozened_time_ms = GetTickCount();
			}
			
			
		}
	}
}
void Enemy::draw(int ticknow)
{
	if (!alive)return;
	if (ticknow - last_time > interval_ms)
	{
		enemyFrameNum = (enemyFrameNum + 1) % enemyIMGNum;
		last_time = ticknow;
	}
	POINT temp = { enemy_location.first,enemy_location.second };
	if (facingRight)
	{
		if (frozened)
		{
			if (GetTickCount() - last_frozened_time_ms < frozen_continue_time_ms)
			{
				enemyIMGRightFrozen->draw(&temp, frozen_frame);
			}
			else
			{
				frozened = false;
				enemyIMGRight->draw(&temp, enemyFrameNum);
			}
		}
		else
		{
			enemyIMGRight->draw(&temp, enemyFrameNum);
		}
		
	}
	else
	{
		if (frozened)
		{
			if (GetTickCount() - last_frozened_time_ms < frozen_continue_time_ms)
			{
				enmyImgLeftFrozen->draw(&temp, frozen_frame);
			}
			else
			{
				frozened = false;
				enmyImgLeft->draw(&temp, enemyFrameNum);
			}
		}
		else
		{
			enmyImgLeft->draw(&temp, enemyFrameNum);
		}
		
	}
}
