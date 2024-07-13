#include"EnemyCtrl.h"

EnemyCtrl::EnemyCtrl(int time, int interval, imgLoadCtrl* enemyImgR, imgLoadCtrl* enemyImgL)
{
	Frameinterval = interval;
	generate_interval_time = time;
	EnemyImgR = enemyImgR;
	EnemyImgL = enemyImgL;
	Enemy* enemy = new Enemy(EnemyImgR,EnemyImgL, Frameinterval, locationGenerate(1280, 720));
	enemies.push_back(enemy);
	last_generate_time = GetTickCount();
};
EnemyCtrl::~EnemyCtrl()
{
	for (size_t i = 0; i < enemies.size(); i++)
	{
		delete enemies[i];
	}
};
void EnemyCtrl::generateEnemy()
{
	if (GetTickCount() - last_generate_time > generate_interval_time)
	{
		Enemy* newEnemy = new Enemy(EnemyImgR, EnemyImgL, Frameinterval, locationGenerate(1280, 720));
		last_generate_time = GetTickCount();
		enemies.push_back(newEnemy);
	}
}
bool EnemyCtrl::runtoplayer(Player* p)
{
	bool touchPlayer = false;
	for (size_t i = 0; i < enemies.size(); i++)
	{
		if (enemies[i]->movetoplayer(p))
			touchPlayer = true;
	}
	return touchPlayer;
}
int EnemyCtrl::touchBullets(Player* p)
{
	std::vector<int> deadIndex;
	Enemy* enemy;
	int deathNum = 0;
	for (size_t i = 0; i < enemies.size(); i++)
	{
		if (enemies[i]->touchedByBullet(p))
		{
			deadIndex.push_back(i);
		}

	}
	deathNum = deadIndex.size();
	for (int i = deadIndex.size() - 1; i >= 0; i--)
	{
		enemy = enemies.at(deadIndex[i]);
		delete enemy;
		enemies[deadIndex[i]] = enemies.back();
		enemies.pop_back();
	}
	return deathNum;
}
int EnemyCtrl::touchSkills(Player* p)
{
	std::vector<int> deadIndex;
	Enemy* enemy;
	int deathNum = 0;
	for (size_t i = 0; i < enemies.size(); i++)
	{
		if (enemies[i]->touchedBySkill(p))
		{
			deadIndex.push_back(i);
		}

	}
	deathNum = deadIndex.size();
	for (int i = deadIndex.size() - 1; i >= 0; i--)
	{
		enemy = enemies.at(deadIndex[i]);
		delete enemy;
		enemies[deadIndex[i]] = enemies.back();
		enemies.pop_back();
	}
	return deathNum;
}
void EnemyCtrl::enemiesDraw()
{
	for (size_t i = 0; i < enemies.size(); i++)
	{
		enemies[i]->draw(GetTickCount());
	}
}
POINT EnemyCtrl::locationGenerate(int frameWidth, int frameHeight)
{
	//x:-60||framewidth y:-60>>height+60
	//x:-60>>width+60 y:-60||height
	POINT randomPoint = { 0,0 };
	int lower_bound = 1;  // 范围的下限
	int upper_bound = 2; // 范围的上限

	// 创建一个随机数生成器
	std::mt19937 generator(std::random_device{}());

	// 创建一个均匀分布的随机数生成器
	std::uniform_int_distribution<int> distribution(lower_bound, upper_bound);
	std::uniform_int_distribution<int> area_rand(-60, frameHeight + 60);
	if (distribution(generator) == 1)
	{
		if (distribution(generator) == 1)randomPoint.x = -60;
		else
		{
			randomPoint.x = frameWidth;
		}
		randomPoint.y = area_rand(generator);
	}
	else
	{
		if (distribution(generator) == 1)randomPoint.y = -60;
		else
		{
			randomPoint.y = frameHeight;
		}
		randomPoint.x = area_rand(generator);
	}
	return randomPoint;
}