#include"Player.h"
#ifndef PI
#define PI 3.1415925
#endif // !PI
Player::Player(imgLoadCtrl* imgs,imgLoadCtrl* imgW, int delta_ms, int bulletNum, int bulDis, int bulSpd, int bulinterval_ms, imgLoadCtrl* bulCtrl, imgLoadCtrl* skill)
{
	bulletsNum = bulletNum;
	bulletDistance = bulDis;
	bulletSpeed = bulSpd;
	bullet_interval_ms = bulinterval_ms;
	bulletsImgs = bulCtrl;

	interval_ms = delta_ms;
	skillImg = skill;
	playerIMG = imgs;
	playerIMGwhite = imgW;
	playerImgNum = imgs->getImagesNum();
	for (size_t i = 0; i < bulletNum; i++)
	{
		Bullet* bullet = new Bullet(bulletsImgs);
		bullets.push_back(bullet);
	}
	setBulletAngle();

};
Player::~Player()
{
	for (size_t i = 0; i < bullets.size(); i++)
	{
		delete bullets[i];
	}
	for (size_t i = 0; i < skills.size(); i++)
	{
		delete skills[i];
	}
};
void Player::play(ExMessage msg)
{
	if (msg.message == WM_KEYDOWN)
	{
		switch (msg.vkcode)
		{
		case 'D':
			Facing = 'D';
			direction_vector.x = 1;
			plrMoveRight = true;
			break;
		case 'A':
			Facing = 'A';
			direction_vector.x = -1;
			plrMoveLeft = true;
			break;
		case 'W':
			Facing = 'W';
			direction_vector.y = -1;
			plrMoveUp = true;
			break;
		case 'S':
			Facing = 'S';
			direction_vector.y = 1;
			plrMoveDown = true;
			break;
		case 'K':
			skills.push_back(new Skill(&plr_location, Facing, skillImg));
			break;
		default:
			break;
		}

	}
	else if (msg.message == WM_KEYUP)
	{
		switch (msg.vkcode)
		{
		case 'D':
			direction_vector.x = 0;
			plrMoveRight = false;
			break;
		case 'A':
			direction_vector.x = 0;
			plrMoveLeft = false;
			break;
		case 'W':
			direction_vector.y = 0;
			plrMoveUp = false;
			break;
		case 'S':
			direction_vector.y = 0;
			plrMoveDown = false;
			break;
		default:
			break;
		}
	}

}
POINT Player::getCenterloc()
{
	return { plr_location.x + plrSize.x / 2, plr_location.y + plrSize.y / 2 };
}
std::vector<POINT>* Player::getBulletLoc()
{
	return &bulletsLocation;
}
std::vector<POINT>* Player::getSkillLoc()
{
	return &skillsLocation;
}
void Player::plrdraw(int ticknow,bool Touched)
{
	if (Touched)
	{
		this->touched = true;
		white_begin_time_ms = GetTickCount();
	}
	if (direction_vector.x != 0 || direction_vector.y != 0)
	{
		plr_location.x += plrMovespeed * (direction_vector.x / sqrt(direction_vector.x * direction_vector.x + direction_vector.y * direction_vector.y));
		plr_location.y += plrMovespeed * (direction_vector.y / sqrt(direction_vector.x * direction_vector.x + direction_vector.y * direction_vector.y));
	}
	if (ticknow - last_time > interval_ms)
	{
		plrFrameNum = (plrFrameNum + 1) % playerImgNum;
		last_time = ticknow;
	}

	if (plr_location.x < 0)plr_location.x = 0;
	else if (plr_location.x > 1220)plr_location.x = 1220;
	if (plr_location.y < 0)plr_location.y = 0;
	else if (plr_location.y > 640)plr_location.y = 640;

	if (touched)
	{
		if (GetTickCount() - white_begin_time_ms > white_continue_time_ms)
		{
			this->touched = false;
		}
		else
		{
			if (last_white_frame)
			{
				playerIMG->draw(&plr_location, plrFrameNum);
				last_white_frame = false;
			}
			else
			{
				playerIMGwhite->draw(&plr_location, plrFrameNum);
				last_white_frame = true;
			}
		}
		
	}
	else
	{
		playerIMG->draw(&plr_location, plrFrameNum);
	}
	

	setBulletsLoc();
	for (size_t i = 0; i < bullets.size(); i++)
	{
		bullets[i]->draw();
	}
	skillsLocation.clear();
	for (size_t i = 0; i < skills.size(); i++)
	{
		skills[i]->NextLoc();
		skillsLocation.push_back(skills[i]->getCenter());
		skills[i]->drawSkill();
	}
}
POINT Player::getPoint()
{
	return plr_location;
}
POINT Player::getplayerSize()
{
	return plrSize;
}
void Player::setBulletsLoc()
{
	POINT loc = { 0,0 };
	POINT center = getCenterloc();
	if (GetTickCount() - bulletsLast_refresh_time > bullet_interval_ms)
	{
		bulletsLocation.clear();
		for (size_t i = 0; i < bullets.size(); i++)
		{
			loc.y = center.y + (bulletDistance + waveDistance) * sin(bullets[i]->getAngle() * PI / 180.0);
			loc.x = center.x + (bulletDistance + waveDistance) * cos(bullets[i]->getAngle() * PI / 180.0);
			bullets[i]->setLoc(loc);
			bulletsLocation.push_back(loc);
		}

		addAngle(bulletSpeed);
		if (waveUp)
		{
			if (waveDistance >= waveAraeMax)waveUp = false;
			waveDistance += bulletVSpeed;
		}
		else
		{
			if (waveDistance <= 0)waveUp = true;
			waveDistance -= bulletVSpeed;
		}
		bulletsLast_refresh_time = GetTickCount();
	}
}
void Player::setBulletAngle()
{
	if (bulletsNum == 0)return;
	int deltaangle = 360 / bulletsNum;
	for (size_t i = 0; i < bullets.size(); i++)
	{
		bullets[i]->setAngle(deltaangle * i);
	}
}
void Player::addAngle(int d)
{
	for (size_t i = 0; i < bullets.size(); i++)
	{
		bullets[i]->setAngle((bullets[i]->getAngle() + d) % 360);
	}
}
int Player::getSkillDistance()
{
	return skillDistance;
}