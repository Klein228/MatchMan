#include<graphics.h>
#include<iostream>
#include<string>
#include <vector>
#include<random>
#include<cmath>
#include<Windows.h>
#include"imgLoadCtrl.h"
#include"Bullet.h"
#include"Player.h"
#include"Enemy.h"
#include"EnemyCtrl.h"
#pragma comment(lib,"MSIMG32.LIB")
#pragma comment(lib,"Winmm.lib")


inline void putimageultra(int x, int y, IMAGE *img)//ͼ����ƺ���
{
	int w = img->getwidth();
	int h = img->getheight();
	AlphaBlend(GetImageHDC(NULL), x, y, w, h,
		GetImageHDC(img), 0, 0, w, h, { AC_SRC_OVER,0,255,AC_SRC_ALPHA });
}
int main()
{
	//���ڳ�ʼ��

	initgraph(1280, 720);
	int screenWidth = GetSystemMetrics(SM_CXSCREEN);
	int screenHeight = GetSystemMetrics(SM_CYSCREEN);

	// ���㴰�ھ��е�����
	int windowWidth = getwidth(); // ���ڿ��
	int windowHeight =getheight(); // ���ڸ߶�
	int x = (screenWidth - windowWidth) / 2;
	int y = (screenHeight - windowHeight) / 2;

	// ��ȡ���ھ��
	HWND hwnd = GetHWnd();

	// ���ô���λ�ã�������ʾ
	SetWindowPos(hwnd, HWND_TOP, x, y, windowWidth, windowHeight, SWP_SHOWWINDOW);

	//music
	mciSendString(_T("open music/bgm.mp3 alias bgm"), NULL, 0, NULL);
	mciSendString(_T("open music/hit.wav alias hit"), NULL, 0, NULL);
	
	//������������Ⱦ
	BeginBatchDraw();

	int score = 0;
	//���ر���
	IMAGE background;
	loadimage(&background, _T("img/background.png"));
	RECT r = { 0, 0, 639, 479 };
	std::wstring Scorecharacter;
	Scorecharacter = L"��ǰ�÷֣� " + std::to_wstring(score);
	drawtext(Scorecharacter.c_str(), &r, DT_CENTER | DT_TOP | DT_SINGLELINE);
	//���ؿ�ʼ��Ϸѡ��
	IMAGE startBackground;
	loadimage(&startBackground, _T("img/startBG.png"));

	IMAGE startButton;
	loadimage(&startButton, _T("img/start.png"));

	IMAGE quitButton;
	loadimage(&quitButton, _T("img/quit.png"));


	const int enemy_refresh_interval = 2000;
	const int touchjudgeDistance = 40;

	std::wstring path = L"img/player";
	const int playerImgNum = 6;
	const int playerFrameInterval_ms = 60;
	const int bulletNum = 3;
	const int distancePtoBullet = 80;
	const int bulletSpeed = 5;
	const int bulletFrameInterval_ms = 10;
	imgLoadCtrl playerImg(&path, playerImgNum, { 80,120 });
	imgLoadCtrl playerImgWhite(&path, playerImgNum, { 80,120 });
	playerImgWhite.setWhite();

	std::wstring bulpath = L"img/basketball";
	const int bulletImgNum = 1;
	imgLoadCtrl bulletImg(&bulpath, bulletImgNum, { 20,20 });

	std::wstring enemypath = L"img/enemy";
	const int enemyImgNum = 4;
	const int enemyFrameInterval_ms = 100;
	imgLoadCtrl enemyImgRight(&enemypath, enemyImgNum, { 50,50 });
	imgLoadCtrl enemyImgLeft(&enemypath, enemyImgNum, { 50,50 });
	enemyImgLeft.setConvert();
	//
	std::wstring skillpath = L"img/chicken";
	const int skillImgNum = 1;
	imgLoadCtrl skillImg(&skillpath, skillImgNum, { 50,50 });

	Player *player=new Player(&playerImg, &playerImgWhite, playerFrameInterval_ms, bulletNum, distancePtoBullet, bulletSpeed, bulletFrameInterval_ms, &bulletImg,&skillImg);

	EnemyCtrl *enemies=new EnemyCtrl(enemy_refresh_interval, enemyFrameInterval_ms,&enemyImgRight,&enemyImgLeft);

	bool playerDead = false;
	bool gameover = false;
	bool startgame = false;
	bool quitFlag = false;
	bool touched = false;
	while (!quitFlag)
	{
		DWORD start_time = GetTickCount();
		//�¼�����
		ExMessage msg;
		while (peekmessage(&msg))
		{
			if (startgame&&(!playerDead))
			{
				(*player).play(msg);
				if (msg.message == WM_KEYDOWN)
				{
					if (msg.vkcode==VK_ESCAPE)
					{
						startgame = false;
						playerDead = true;
					}
				}
			}
			else
			{
				if (msg.message == WM_LBUTTONDOWN)
				{
					if (msg.x <= getwidth() / 2 - startButton.getwidth() / 2 + startButton.getwidth() && msg.x >= getwidth() / 2 - startButton.getwidth() / 2 &&
						msg.y <= getheight() * 2 / 3 + startButton.getheight() && msg.y >= getheight() * 2 / 3)
					{
						startgame = true;
						playerDead = false;
						mciSendString(_T("play bgm repeat from 0"), NULL, 0, NULL);
						enemies = new EnemyCtrl(enemy_refresh_interval,enemyFrameInterval_ms, &enemyImgRight,&enemyImgLeft);
					}
					else if (msg.x <= getwidth() / 2 - startButton.getwidth() / 2 + startButton.getwidth() && msg.x >= getwidth() / 2 - startButton.getwidth() / 2 &&
							 msg.y <= getheight() * 2 / 3 + 2*startButton.getheight() && msg.y >= getheight() * 2 / 3+startButton.getheight())
					{
						quitFlag = true;
					}
					
				}
			}
			
		}
		
		if (!startgame)
		{

			cleardevice();
			putimageultra(0, 0, &startBackground);
			putimageultra(getwidth() / 2 - startButton.getwidth() / 2, getheight() * 2 / 3, &startButton);
			putimageultra(getwidth() / 2 - startButton.getwidth() / 2, getheight() * 2 / 3 + quitButton.getheight(), &quitButton);
			FlushBatchDraw();
		}
		else
		{
			enemies->generateEnemy();
			score += enemies->touchBullets(player);
			score += enemies->touchSkills(player);
			touched = enemies->runtoplayer(player);

			//ͼ�����
			cleardevice();
			putimageultra(0, 0, &background);
			player->plrdraw(GetTickCount(),touched);
			enemies->enemiesDraw();
			Scorecharacter = L"��ǰ�÷֣� " + std::to_wstring(score);
			drawtext(Scorecharacter.c_str(), &r, DT_CENTER | DT_TOP | DT_SINGLELINE);
			if (gameover)
			{
				mciSendString(L"stop bgm", NULL, 0, NULL); // ֹͣ����
				mciSendString(L"close bgm", NULL, 0, NULL); // �رղ��ͷ���Դ
				mciSendString(L"stop hit", NULL, 0, NULL); // ֹͣ����
				mciSendString(L"close hit", NULL, 0, NULL); // �رղ��ͷ���Դ
				MessageBox(GetHWnd(), L"YOU LOSE!!", L"��Ϸ����", 1);
				delete enemies;
				gameover = false;
				startgame = false;
				playerDead = true;
			}
			FlushBatchDraw();
		}
		
		DWORD end_time = GetTickCount();
		DWORD delta_time = end_time - start_time;
		if (delta_time < 1000 / 60)
		{
			Sleep(1000 / 60 - delta_time);
		}
	}
	
	EndBatchDraw();
	closegraph();
	return 0;
}