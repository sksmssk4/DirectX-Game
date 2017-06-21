// include the basic windows header files and the Direct3D header file
#include <windows.h>
#include <windowsx.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <iostream>

#include "entity.h" 
#include "Bg.h"
#include "Score.h"
#include "Score2.h"
#include "Score3.h"

#include "Hero.h"
#include "Enemy.h"
#include "Bullet.h"
#include "Bullet2.h"
#include "Bullet3.h"
#include "eBullet.h"

#include <mmsystem.h>
#include <Digitalv.h>

// define the screen resolution and keyboard macros

#define SCREEN_WIDTH  840
#define SCREEN_HEIGHT 480
#define KEY_DOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)
#define KEY_UP(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 0 : 1)

#define ENEMY_NUM 10 
#define BULLET_NUM 10
#define BULLET_NUM2 4
#define BG_NUM 10
// include the Direct3D Library file
#pragma comment (lib, "d3d9.lib")
#pragma comment (lib, "d3dx9.lib")
#pragma comment(lib, "Winmm.lib")
// global declarations

using namespace std;

LPDIRECT3D9 d3d;    // the pointer to our Direct3D interface
LPDIRECT3DDEVICE9 d3ddev;    // the pointer to the device class
LPD3DXSPRITE d3dspt;    // the pointer to our Direct3D Sprite interface

//ui
LPDIRECT3DTEXTURE9 sprite_bg;
LPDIRECT3DTEXTURE9 sprite_title;
LPDIRECT3DTEXTURE9 sprite_press;
LPDIRECT3DTEXTURE9 sprite_press2;
//ingame
LPDIRECT3DTEXTURE9 sprite;    // the pointer to the sprite
LPDIRECT3DTEXTURE9 sprite_inbg;
LPDIRECT3DTEXTURE9 sprite_score0;
LPDIRECT3DTEXTURE9 sprite_score1;
LPDIRECT3DTEXTURE9 sprite_score2;
LPDIRECT3DTEXTURE9 sprite_score3;
LPDIRECT3DTEXTURE9 sprite_score4;
LPDIRECT3DTEXTURE9 sprite_score5;
LPDIRECT3DTEXTURE9 sprite_score6;
LPDIRECT3DTEXTURE9 sprite_score7;
LPDIRECT3DTEXTURE9 sprite_score8;
LPDIRECT3DTEXTURE9 sprite_score9;
//주인공 대기 스프라이트
LPDIRECT3DTEXTURE9 sprite_hero; 
LPDIRECT3DTEXTURE9 sprite_hero2;
LPDIRECT3DTEXTURE9 sprite_hero3;
LPDIRECT3DTEXTURE9 sprite_hero4;
//주인공 피격 스프라이트
LPDIRECT3DTEXTURE9 sprite_hero_hit;
//주인공 스킬 스프라이트
LPDIRECT3DTEXTURE9 sprite_hero_skill;
LPDIRECT3DTEXTURE9 sprite_hero_skill2;
LPDIRECT3DTEXTURE9 sprite_hero_skill3;
LPDIRECT3DTEXTURE9 sprite_hero_skill4;
LPDIRECT3DTEXTURE9 sprite_hero_skill5;
LPDIRECT3DTEXTURE9 sprite_hero_skill6;
LPDIRECT3DTEXTURE9 sprite_hero_skill7;
LPDIRECT3DTEXTURE9 sprite_hero_skill8;
//주인공 총알
LPDIRECT3DTEXTURE9 sprite_bullet;
LPDIRECT3DTEXTURE9 sprite_bullet2;
LPDIRECT3DTEXTURE9 sprite_bullet3;
//적 대기
LPDIRECT3DTEXTURE9 sprite_enemy;
//적 총알
LPDIRECT3DTEXTURE9 sprite_enemy_bullet;


//음악파일 재생(ui)
MCI_OPEN_PARMS mci_open;
MCI_PLAY_PARMS mci_play;
int dwID;
//음악파일 재생(ingame)
MCI_OPEN_PARMS mci_open2;
MCI_PLAY_PARMS mci_play2;
int dwID2;

void initD3D(HWND hWnd);    // sets up and initializes Direct3D
void render_frame(void);    // renders a single frame
void cleanD3D(void);		// closes Direct3D and releases memory

bool Scene1 = true; // UI
bool Scene2 = false; // INGAME
void init_game(void);
void do_game_logic(void);
bool sphere_collision_check(float x0, float y0, float size0, float x1, float y1, float size1);


// the WindowProc function prototype
LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

bool sphere_collision_check(float x0, float y0, float size0, float x1, float y1, float size1)
{

	if ((x0 - x1)*(x0 - x1) + (y0 - y1)*(y0 - y1) < (size0 + size1) * (size0 + size1))
		return true;
	else
		return false;
}

enum { MOVE_UP, MOVE_DOWN, MOVE_LEFT, MOVE_RIGHT };


//객체 생성 
Hero hero;
Bullet bullet[BULLET_NUM];
Bullet2 bullet2[BULLET_NUM2];
Bullet3 bullet3[BULLET_NUM2];
Enemy enemy[ENEMY_NUM];
eBullet ebullet[ENEMY_NUM];

Score score;
Score score2;
Score score3;
Bg bg[BG_NUM];


// the entry point for any Windows program
int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
	HWND hWnd;
	WNDCLASSEX wc;

	ZeroMemory(&wc, sizeof(WNDCLASSEX));

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = (WNDPROC)WindowProc;
	wc.hInstance = hInstance;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.lpszClassName = L"WindowClass";

	RegisterClassEx(&wc);

	hWnd = CreateWindowEx(NULL, L"WindowClass", L"Our Direct3D Program",
		WS_EX_DLGMODALFRAME | WS_BORDER, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT,
		NULL, NULL, hInstance, NULL);

	ShowWindow(hWnd, nCmdShow);

	// set up and initialize Direct3D
	initD3D(hWnd);


	//게임 오브젝트 초기화 
	init_game();

	// enter the main loop:

	MSG msg;
	//배경음
	mci_open.lpstrElementName = L"UI_bgm.mp3";
	mci_open.lpstrDeviceType = L"MPEGvideo"; //wav 파일일 경우 WaveAudio
	
	mci_open2.lpstrElementName = L"INGAME_bgm.mp3";
	mci_open2.lpstrDeviceType = L"MPEGvideo";
	
	

	
	while (TRUE)
	{
		DWORD starting_point = GetTickCount();

		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
				break;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		do_game_logic();

		render_frame();

		// check the 'escape' key
		if (KEY_DOWN(VK_ESCAPE))
			PostMessage(hWnd, WM_DESTROY, 0, 0);

		while ((GetTickCount() - starting_point) < 25);
	}

	// clean up DirectX and COM
	cleanD3D();

	return msg.wParam;
}


// this is the main message handler for the program
LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:
	{
		PostQuitMessage(0);
		return 0;
	} break;
	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}


// this function initializes and prepares Direct3D for use
void initD3D(HWND hWnd)
{
	d3d = Direct3DCreate9(D3D_SDK_VERSION);

	D3DPRESENT_PARAMETERS d3dpp;

	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.hDeviceWindow = hWnd;
	d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
	d3dpp.BackBufferWidth = SCREEN_WIDTH;
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;


	// create a device class using this information and the info from the d3dpp stuct
	d3d->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp,
		&d3ddev);

	D3DXCreateSprite(d3ddev, &d3dspt);    // create the Direct3D Sprite object


	D3DXCreateTextureFromFileEx(d3ddev,
		L"BackGround2.png",
		840,
		480,
		D3DX_DEFAULT,
		NULL,
		D3DFMT_A8R8G8B8,
		D3DPOOL_MANAGED,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		D3DCOLOR_XRGB(255, 0, 255),
		NULL,
		NULL,
		&sprite_bg);

	D3DXCreateTextureFromFileEx(d3ddev,
		L"Title.png",
		500,
		124,
		D3DX_DEFAULT,
		NULL,
		D3DFMT_A8R8G8B8,
		D3DPOOL_MANAGED,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		D3DCOLOR_XRGB(255, 0, 255),
		NULL,
		NULL,
		&sprite_title);

	D3DXCreateTextureFromFileEx(d3ddev,
		L"press.png",
		562,
		77,
		D3DX_DEFAULT,
		NULL,
		D3DFMT_A8R8G8B8,
		D3DPOOL_MANAGED,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		D3DCOLOR_XRGB(255, 0, 255),
		NULL,
		NULL,
		&sprite_press);

	D3DXCreateTextureFromFileEx(d3ddev,
		L"press2.png",
		562,
		77,
		D3DX_DEFAULT,
		NULL,
		D3DFMT_A8R8G8B8,
		D3DPOOL_MANAGED,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		D3DCOLOR_XRGB(255, 0, 255),
		NULL,
		NULL,
		&sprite_press2);

	D3DXCreateTextureFromFileEx(d3ddev,
		L"inbg.png",
		840,
		481,
		D3DX_DEFAULT,
		NULL,
		D3DFMT_A8R8G8B8,
		D3DPOOL_MANAGED,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		D3DCOLOR_XRGB(255, 0, 255),
		NULL,
		NULL,
		&sprite_inbg);


	D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
		L"Panel3.png",    // the file name
		D3DX_DEFAULT,    // default width
		D3DX_DEFAULT,    // default height
		D3DX_DEFAULT,    // no mip mapping
		NULL,    // regular usage
		D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
		D3DPOOL_MANAGED,    // typical memory handling
		D3DX_DEFAULT,    // no filtering
		D3DX_DEFAULT,    // no mip filtering
		D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
		NULL,    // no image info struct
		NULL,    // not using 256 colors
		&sprite);    // load to sprite

	//////////////////////////////////////////////////////////////////////////////
	D3DXCreateTextureFromFileEx(d3ddev,
		L"score0.png",
		25,
		40,
		D3DX_DEFAULT,
		NULL,
		D3DFMT_A8R8G8B8,
		D3DPOOL_MANAGED,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		D3DCOLOR_XRGB(255, 0, 255),
		NULL,
		NULL,
		&sprite_score0);

	D3DXCreateTextureFromFileEx(d3ddev,
		L"score1.png",
		25,
		40,
		D3DX_DEFAULT,
		NULL,
		D3DFMT_A8R8G8B8,
		D3DPOOL_MANAGED,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		D3DCOLOR_XRGB(255, 0, 255),
		NULL,
		NULL,
		&sprite_score1);

	D3DXCreateTextureFromFileEx(d3ddev,
		L"score2.png",
		25,
		40,
		D3DX_DEFAULT,
		NULL,
		D3DFMT_A8R8G8B8,
		D3DPOOL_MANAGED,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		D3DCOLOR_XRGB(255, 0, 255),
		NULL,
		NULL,
		&sprite_score2);

	D3DXCreateTextureFromFileEx(d3ddev,
		L"score3.png",
		25,
		40,
		D3DX_DEFAULT,
		NULL,
		D3DFMT_A8R8G8B8,
		D3DPOOL_MANAGED,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		D3DCOLOR_XRGB(255, 0, 255),
		NULL,
		NULL,
		&sprite_score3);

	D3DXCreateTextureFromFileEx(d3ddev,
		L"score4.png",
		25,
		40,
		D3DX_DEFAULT,
		NULL,
		D3DFMT_A8R8G8B8,
		D3DPOOL_MANAGED,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		D3DCOLOR_XRGB(255, 0, 255),
		NULL,
		NULL,
		&sprite_score4);

	D3DXCreateTextureFromFileEx(d3ddev,
		L"score5.png",
		25,
		40,
		D3DX_DEFAULT,
		NULL,
		D3DFMT_A8R8G8B8,
		D3DPOOL_MANAGED,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		D3DCOLOR_XRGB(255, 0, 255),
		NULL,
		NULL,
		&sprite_score5);

	D3DXCreateTextureFromFileEx(d3ddev,
		L"score6.png",
		25,
		40,
		D3DX_DEFAULT,
		NULL,
		D3DFMT_A8R8G8B8,
		D3DPOOL_MANAGED,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		D3DCOLOR_XRGB(255, 0, 255),
		NULL,
		NULL,
		&sprite_score6);

	D3DXCreateTextureFromFileEx(d3ddev,
		L"score7.png",
		25,
		40,
		D3DX_DEFAULT,
		NULL,
		D3DFMT_A8R8G8B8,
		D3DPOOL_MANAGED,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		D3DCOLOR_XRGB(255, 0, 255),
		NULL,
		NULL,
		&sprite_score7);

	D3DXCreateTextureFromFileEx(d3ddev,
		L"score8.png",
		25,
		40,
		D3DX_DEFAULT,
		NULL,
		D3DFMT_A8R8G8B8,
		D3DPOOL_MANAGED,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		D3DCOLOR_XRGB(255, 0, 255),
		NULL,
		NULL,
		&sprite_score8);

	D3DXCreateTextureFromFileEx(d3ddev,
		L"score9.png",
		25,
		40,
		D3DX_DEFAULT,
		NULL,
		D3DFMT_A8R8G8B8,
		D3DPOOL_MANAGED,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		D3DCOLOR_XRGB(255, 0, 255),
		NULL,
		NULL,
		&sprite_score9);
	//////////////////////////////////////////////////////////////////////

	//주인공 대기 스프라이트
	D3DXCreateTextureFromFileEx(d3ddev,   
		L"hero.png",  
		64,
		100,
		D3DX_DEFAULT,    
		NULL,   
		D3DFMT_A8R8G8B8,    
		D3DPOOL_MANAGED,    
		D3DX_DEFAULT,   
		D3DX_DEFAULT,   
		D3DCOLOR_XRGB(255, 0, 255),
		NULL,    
		NULL,    
		&sprite_hero);   
	D3DXCreateTextureFromFileEx(d3ddev,
		L"hero2.png",
		64,
		100,
		D3DX_DEFAULT,
		NULL,
		D3DFMT_A8R8G8B8,
		D3DPOOL_MANAGED,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		D3DCOLOR_XRGB(255, 0, 255),
		NULL,
		NULL,
		&sprite_hero2);
	D3DXCreateTextureFromFileEx(d3ddev,
		L"hero3.png",
		64,
		100,
		D3DX_DEFAULT,
		NULL,
		D3DFMT_A8R8G8B8,
		D3DPOOL_MANAGED,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		D3DCOLOR_XRGB(255, 0, 255),
		NULL,
		NULL,
		&sprite_hero3);
	D3DXCreateTextureFromFileEx(d3ddev,
		L"hero4.png",
		64,
		100,
		D3DX_DEFAULT,
		NULL,
		D3DFMT_A8R8G8B8,
		D3DPOOL_MANAGED,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		D3DCOLOR_XRGB(255, 0, 255),
		NULL,
		NULL,
		&sprite_hero4);

	//주인공 스킬 스프라이트
	D3DXCreateTextureFromFileEx(d3ddev,
		L"hero_skill.png",
		99,
		156,
		D3DX_DEFAULT,
		NULL,
		D3DFMT_A8R8G8B8,
		D3DPOOL_MANAGED,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		D3DCOLOR_XRGB(255, 0, 255),
		NULL,
		NULL,
		&sprite_hero_skill);

	//주인공 피격
	D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
		L"hero_hit.png",    // the file name
		D3DX_DEFAULT,    // default width
		D3DX_DEFAULT,    // default height
		D3DX_DEFAULT,    // no mip mapping
		NULL,    // regular usage
		D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
		D3DPOOL_MANAGED,    // typical memory handling
		D3DX_DEFAULT,    // no filtering
		D3DX_DEFAULT,    // no mip filtering
		D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
		NULL,    // no image info struct
		NULL,    // not using 256 colors
		&sprite_hero_hit);    // load to sprite
	//적
	D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
		L"enemy.png",    // the file name
		D3DX_DEFAULT,    // default width
		D3DX_DEFAULT,    // default height
		D3DX_DEFAULT,    // no mip mapping
		NULL,    // regular usage
		D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
		D3DPOOL_MANAGED,    // typical memory handling
		D3DX_DEFAULT,    // no filtering
		D3DX_DEFAULT,    // no mip filtering
		D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
		NULL,    // no image info struct
		NULL,    // not using 256 colors
		&sprite_enemy);    // load to sprite
	//적 총알
	D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
		L"ebullet.png",    // the file name
		30,    // default width
		29,    // default height
		D3DX_DEFAULT,    // no mip mapping
		NULL,    // regular usage
		D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
		D3DPOOL_MANAGED,    // typical memory handling
		D3DX_DEFAULT,    // no filtering
		D3DX_DEFAULT,    // no mip filtering
		D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
		NULL,    // no image info struct
		NULL,    // not using 256 colors
		&sprite_enemy_bullet);    // load to sprite

	D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
		L"bullet.png",    // the file name
		D3DX_DEFAULT,    // default width
		D3DX_DEFAULT,    // default height
		D3DX_DEFAULT,    // no mip mapping
		NULL,    // regular usage
		D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
		D3DPOOL_MANAGED,    // typical memory handling
		D3DX_DEFAULT,    // no filtering
		D3DX_DEFAULT,    // no mip filtering
		D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
		NULL,    // no image info struct
		NULL,    // not using 256 colors
		&sprite_bullet);    // load to sprite

	D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
		L"bullet.png",    // the file name
		D3DX_DEFAULT,    // default width
		D3DX_DEFAULT,    // default height
		D3DX_DEFAULT,    // no mip mapping
		NULL,    // regular usage
		D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
		D3DPOOL_MANAGED,    // typical memory handling
		D3DX_DEFAULT,    // no filtering
		D3DX_DEFAULT,    // no mip filtering
		D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
		NULL,    // no image info struct
		NULL,    // not using 256 colors
		&sprite_bullet2);    // load to sprite

	D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
		L"bullet.png",    // the file name
		D3DX_DEFAULT,    // default width
		D3DX_DEFAULT,    // default height
		D3DX_DEFAULT,    // no mip mapping
		NULL,    // regular usage
		D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
		D3DPOOL_MANAGED,    // typical memory handling
		D3DX_DEFAULT,    // no filtering
		D3DX_DEFAULT,    // no mip filtering
		D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
		NULL,    // no image info struct
		NULL,    // not using 256 colors
		&sprite_bullet3);    // load to sprite

	return;
}


void init_game(void)
{
	
	//객체 초기화 
	
	bg[0].init(0.0f, 0.0f);
	bg[1].init(SCREEN_WIDTH, 0.0f);
	score.init(600.0f, 30.0f);
	score2.init(630.0f, 30.0f);
	score3.init(660.0f, 30.0f);
	hero.init(150.0f, 300.0f);
	//총알 초기화 
	for (int i = 0; i < BULLET_NUM; i++)
	{
		bullet[i].init(hero.x_pos, hero.y_pos);

	}
	for (int i = 0; i < BULLET_NUM2; i++)
	{
		bullet2[i].init(hero.x_pos, hero.y_pos);
		bullet3[i].init(hero.x_pos, hero.y_pos);
	}
	
	//적들 초기화 
	float distance = 60;
	for (int i = 0; i < ENEMY_NUM; i++)
	{
		enemy[i].init((float)SCREEN_WIDTH + distance, distance);
		distance += distance;
		//}
		//enemy[i].init((float)(SCREEN_WIDTH + (rand() % 300)), rand() % SCREEN_HEIGHT);
	}
	//적 총알 초기화
	for (int i = 0; i < ENEMY_NUM; i++)
	{
		ebullet[i].init(enemy[i].x_pos, enemy[i].y_pos);
	}

}


void do_game_logic(void)
{
	if (Scene2 == true)
	{

		for (int i = 0; i < BG_NUM; i++)
		{
			bg[i].init(bg[i].x_pos, 0.0f);
			bg[i].x_pos;
			bg[i].move();
		}

		//주인공 처리 
		if (KEY_DOWN(VK_UP))
			hero.move(MOVE_UP);

		if (KEY_DOWN(VK_DOWN))
			hero.move(MOVE_DOWN);

		if (KEY_DOWN(VK_LEFT))
			hero.move(MOVE_LEFT);

		if (KEY_DOWN(VK_RIGHT))
			hero.move(MOVE_RIGHT);

		//주인공 충돌 처리
		if (hero.show() == false)
		{
			for (int i = 0; i < ENEMY_NUM; i++)
			{
				if (hero.check_collision(enemy[i].x_pos, enemy[i].y_pos) == true)
				{
					hero.active();
					hero.hit_init(hero.x_pos, (hero.y_pos) - 5);
				}
				if (hero.check_collision(ebullet[i].x_pos, ebullet[i].y_pos) == true)
				{
					hero.active();
					hero.hit_init(hero.x_pos, (hero.y_pos) - 5);
				}
			}
		}
		//총알 보일 시 주인공 히트상태 해제
		if (hero.show() == true)
		{
			for (int i = 0; i < BULLET_NUM; i++)
			{
				if (bullet[i].bShow == true)
				{
					hero.hit_Show = false;

				}
			}
		}
		//총알 처리 
		static int BCounter = 0;
		static int BCounter2 = 0;
		if (KEY_DOWN(VK_SPACE)) //매직미사일 발사
		{
			for (int i = 0; i < BULLET_NUM; i++)
			{
				BCounter++;
				if (BCounter % 9 == 0)
				{
					if (bullet[i].show() == false)
					{
						bullet[i].active();
						bullet[i].init(hero.x_pos + 20.0f, hero.y_pos);
						break;
					}
				}
			}
			for (int i = 0; i < BULLET_NUM2; i++)
			{
				BCounter2++;
				if (BCounter % 15 == 0)
				{
					if (bullet2[i].show() == false && bullet3[i].show() == false)
					{
						bullet2[i].active();
						bullet3[i].active();
						bullet2[i].init(hero.x_pos + 20.0f, hero.y_pos);
						bullet3[i].init(hero.x_pos + 20.0f, hero.y_pos);
						break;
					}
				}
			}
		}

		static int hit_counter = 0;

		for (int j = 0; j < BULLET_NUM; j++)
		{
			if (bullet[j].show() == true)
			{
				if (bullet[j].x_pos > SCREEN_WIDTH)
					bullet[j].hide();
				else
					bullet[j].move();



				for (int i = 0; i < ENEMY_NUM; i++)
				{
					if (bullet[j].check_collision(enemy[i].x_pos, enemy[i].y_pos) == true)
					{
						hit_counter += 1; //충돌 1회할때마다 1개씩 체크됨
						enemy[i].init((float)(SCREEN_WIDTH + (rand() % 300)), rand() % SCREEN_HEIGHT); // 적이 충돌되면 다시 랜덤으로 등장
						if (hit_counter == 2) // 충돌 횟수 2회시
						{
							score3.score0_show = true;
							score.score0_show = true;
							score2.score0_show = false;
							score2.score1_show = true;
						}
						if (hit_counter == 4) // 충돌 횟수 4회시
						{
							score3.score0_show = true;
							score.score0_show = true;
							score2.score1_show = false;
							score2.score2_show = true;
						}
						if (hit_counter == 6)
						{
							score3.score0_show = true;
							score.score0_show = true;
							score2.score2_show = false;
							score2.score3_show = true;
						}
						if (hit_counter == 8)
						{
							score3.score0_show = true;
							score.score0_show = true;
							score2.score3_show = false;
							score2.score4_show = true;
						}
						if (hit_counter == 10)
						{
							score3.score0_show = true;
							score.score0_show = true;
							score2.score4_show = false;
							score2.score5_show = true;
						}
						if (hit_counter == 12)
						{
							score3.score0_show = true;
							score.score0_show = true;
							score2.score5_show = false;
							score2.score6_show = true;
						}
						if (hit_counter == 14)
						{
							score3.score0_show = true;
							score.score0_show = true;
							score2.score6_show = false;
							score2.score7_show = true;
						}
						if (hit_counter == 16)
						{
							score3.score0_show = true;
							score.score0_show = true;
							score2.score7_show = false;
							score2.score8_show = true;
						}
						if (hit_counter == 18)
						{
							score3.score0_show = true;
							score.score0_show = true;
							score2.score8_show = false;
							score2.score9_show = true;
						}
						if (hit_counter == 20)
						{
							score3.score0_show = true;
							score.score0_show = false;
							score.score1_show = true;
							score2.score9_show = false;
							score2.score0_show = true;
						}
						if (hit_counter == 22)
						{
							score3.score0_show = true;
							score.score1_show = true;
							score2.score0_show = false;
							score2.score1_show = true;
						}
						if (hit_counter == 24)
						{
							score3.score0_show = true;
							score.score1_show = true;
							score2.score1_show = false;
							score2.score2_show = true;
						}
						if (hit_counter == 26)
						{
							score3.score0_show = true;
							score.score1_show = true;
							score2.score2_show = false;
							score2.score3_show = true;
						}
						if (hit_counter == 28)
						{
							score3.score0_show = true;
							score.score1_show = true;
							score2.score3_show = false;
							score2.score4_show = true;
						}
						if (hit_counter == 30)
						{
							score3.score0_show = true;
							score.score1_show = true;
							score2.score4_show = false;
							score2.score5_show = true;
						}
						if (hit_counter == 32)
						{
							score3.score0_show = true;
							score.score1_show = true;
							score2.score5_show = false;
							score2.score6_show = true;
						}
						if (hit_counter == 34)
						{
							score3.score0_show = true;
							score.score1_show = true;
							score2.score6_show = false;
							score2.score7_show = true;
						}
						if (hit_counter == 36)
						{
							score3.score0_show = true;
							score.score1_show = true;
							score2.score7_show = false;
							score2.score8_show = true;
						}
						if (hit_counter == 38)
						{
							score3.score0_show = true;
							score.score1_show = true;
							score2.score8_show = false;
							score2.score9_show = true;
						}
						if (hit_counter == 40)
						{
							score3.score0_show = true;
							score.score2_show = true;
							score.score1_show = false;
							score2.score9_show = false;
							score2.score0_show = true;
						}
						if (hit_counter == 42)
						{
							score3.score0_show = true;
							score.score2_show = true;
							score2.score0_show = false;
							score2.score1_show = true;
						}
						if (hit_counter == 44)
						{
							score3.score0_show = true;
							score.score2_show = true;
							score2.score1_show = false;
							score2.score2_show = true;
						}
						if (hit_counter == 46)
						{
							score3.score0_show = true;
							score.score2_show = true;
							score2.score2_show = false;
							score2.score3_show = true;
						}
						if (hit_counter == 48)
						{
							score3.score0_show = true;
							score.score2_show = true;
							score2.score3_show = false;
							score2.score4_show = true;
						}
						if (hit_counter == 50)
						{
							score3.score0_show = true;
							score.score2_show = true;
							score2.score4_show = false;
							score2.score5_show = true;
						}
						if (hit_counter == 52)
						{
							score3.score0_show = true;
							score.score2_show = true;
							score2.score5_show = false;
							score2.score6_show = true;
						}
						if (hit_counter == 54)
						{
							score3.score0_show = true;
							score.score2_show = true;
							score2.score6_show = false;
							score2.score7_show = true;
						}
						if (hit_counter == 56)
						{
							score3.score0_show = true;
							score.score2_show = true;
							score2.score7_show = false;
							score2.score8_show = true;
						}
						if (hit_counter == 58)
						{
							score3.score0_show = true;
							score.score2_show = true;
							score2.score8_show = false;
							score2.score9_show = true;
						}
						if (hit_counter == 60)
						{
							score3.score0_show = true;
							score.score2_show = false;
							score.score3_show = true;
							score2.score9_show = false;
							score2.score0_show = true;
						}
						if (hit_counter == 62)
						{
							score3.score0_show = true;
							score.score3_show = true;
							score2.score0_show = false;
							score2.score1_show = true;
						}
						if (hit_counter == 64)
						{
							score3.score0_show = true;
							score.score3_show = true;
							score2.score1_show = false;
							score2.score2_show = true;
						}
						if (hit_counter == 66)
						{
							score3.score0_show = true;
							score.score3_show = true;
							score2.score2_show = false;
							score2.score3_show = true;
						}
						if (hit_counter == 68)
						{
							score3.score0_show = true;
							score.score3_show = true;
							score2.score3_show = false;
							score2.score4_show = true;
						}
						if (hit_counter == 70)
						{
							score3.score0_show = true;
							score.score3_show = true;
							score2.score4_show = false;
							score2.score5_show = true;
						}
						if (hit_counter == 72)
						{
							score3.score0_show = true;
							score.score3_show = true;
							score2.score5_show = false;
							score2.score6_show = true;
						}
						if (hit_counter == 74)
						{
							score3.score0_show = true;
							score.score3_show = true;
							score2.score6_show = false;
							score2.score7_show = true;
						}
						if (hit_counter == 76)
						{
							score3.score0_show = true;
							score.score3_show = true;
							score2.score7_show = false;
							score2.score8_show = true;
						}
						if (hit_counter == 78)
						{
							score3.score0_show = true;
							score.score3_show = true;
							score2.score8_show = false;
							score2.score9_show = true;
						}
						if (hit_counter == 80)
						{
							score3.score0_show = true;
							score.score3_show = false;
							score.score4_show = true;
							score2.score9_show = false;
							score2.score0_show = true;
						}
						if (hit_counter == 82)
						{
							score3.score0_show = true;
							score.score4_show = true;
							score2.score0_show = false;
							score2.score1_show = true;
						}
						if (hit_counter == 84)
						{
							score3.score0_show = true;
							score.score4_show = true;
							score2.score1_show = false;
							score2.score2_show = true;
						}
						if (hit_counter == 86)
						{
							score3.score0_show = true;
							score.score4_show = true;
							score2.score2_show = false;
							score2.score3_show = true;
						}
						if (hit_counter == 88)
						{
							score3.score0_show = true;
							score.score4_show = true;
							score2.score3_show = false;
							score2.score4_show = true;
						}
						if (hit_counter == 90)
						{
							score3.score0_show = true;
							score.score4_show = true;
							score2.score4_show = false;
							score2.score5_show = true;
						}
						if (hit_counter == 92)
						{
							score3.score0_show = true;
							score.score4_show = true;
							score2.score5_show = false;
							score2.score6_show = true;
						}
						if (hit_counter == 94)
						{
							score3.score0_show = true;
							score.score4_show = true;
							score2.score6_show = false;
							score2.score7_show = true;
						}
						if (hit_counter == 96)
						{
							score3.score0_show = true;
							score.score4_show = true;
							score2.score7_show = false;
							score2.score8_show = true;
						}
						if (hit_counter == 98)
						{
							score3.score0_show = true;
							score.score4_show = true;
							score2.score8_show = false;
							score2.score9_show = true;
						}
						if (hit_counter == 100)
						{
							score3.score0_show = true;
							score.score4_show = false;
							score.score5_show = true;
							score2.score9_show = false;
							score2.score0_show = true;
						}
					}
				}
			}
		}
		for (int j = 0; j < BULLET_NUM2; j++)
		{
			if (bullet2[j].show() == true)
			{
				if (bullet2[j].x_pos > SCREEN_WIDTH)
					bullet2[j].hide();
				else
					bullet2[j].move();


				for (int i = 0; i < ENEMY_NUM; i++)
				{
					if (bullet2[j].check_collision(enemy[i].x_pos, enemy[i].y_pos) == true)
					{
						hit_counter += 1;
						enemy[i].init((float)(SCREEN_WIDTH + (rand() % 300)), rand() % SCREEN_HEIGHT);
						if (hit_counter == 2) // 충돌 횟수 2회시
						{
							score3.score0_show = true;
							score.score0_show = true;
							score2.score0_show = false;
							score2.score1_show = true;
						}
						if (hit_counter == 4) // 충돌 횟수 4회시
						{
							score3.score0_show = true;
							score.score0_show = true;
							score2.score1_show = false;
							score2.score2_show = true;
						}
						if (hit_counter == 6)
						{
							score3.score0_show = true;
							score.score0_show = true;
							score2.score2_show = false;
							score2.score3_show = true;
						}
						if (hit_counter == 8)
						{
							score3.score0_show = true;
							score.score0_show = true;
							score2.score3_show = false;
							score2.score4_show = true;
						}
						if (hit_counter == 10)
						{
							score3.score0_show = true;
							score.score0_show = true;
							score2.score4_show = false;
							score2.score5_show = true;
						}
						if (hit_counter == 12)
						{
							score3.score0_show = true;
							score.score0_show = true;
							score2.score5_show = false;
							score2.score6_show = true;
						}
						if (hit_counter == 14)
						{
							score3.score0_show = true;
							score.score0_show = true;
							score2.score6_show = false;
							score2.score7_show = true;
						}
						if (hit_counter == 16)
						{
							score3.score0_show = true;
							score.score0_show = true;
							score2.score7_show = false;
							score2.score8_show = true;
						}
						if (hit_counter == 18)
						{
							score3.score0_show = true;
							score.score0_show = true;
							score2.score8_show = false;
							score2.score9_show = true;
						}
						if (hit_counter == 20)
						{
							score3.score0_show = true;
							score.score0_show = false;
							score.score1_show = true;
							score2.score9_show = false;
							score2.score0_show = true;
						}
						if (hit_counter == 22)
						{
							score3.score0_show = true;
							score.score1_show = true;
							score2.score0_show = false;
							score2.score1_show = true;
						}
						if (hit_counter == 24)
						{
							score3.score0_show = true;
							score.score1_show = true;
							score2.score1_show = false;
							score2.score2_show = true;
						}
						if (hit_counter == 26)
						{
							score3.score0_show = true;
							score.score1_show = true;
							score2.score2_show = false;
							score2.score3_show = true;
						}
						if (hit_counter == 28)
						{
							score3.score0_show = true;
							score.score1_show = true;
							score2.score3_show = false;
							score2.score4_show = true;
						}
						if (hit_counter == 30)
						{
							score3.score0_show = true;
							score.score1_show = true;
							score2.score4_show = false;
							score2.score5_show = true;
						}
						if (hit_counter == 32)
						{
							score3.score0_show = true;
							score.score1_show = true;
							score2.score5_show = false;
							score2.score6_show = true;
						}
						if (hit_counter == 34)
						{
							score3.score0_show = true;
							score.score1_show = true;
							score2.score6_show = false;
							score2.score7_show = true;
						}
						if (hit_counter == 36)
						{
							score3.score0_show = true;
							score.score1_show = true;
							score2.score7_show = false;
							score2.score8_show = true;
						}
						if (hit_counter == 38)
						{
							score3.score0_show = true;
							score.score1_show = true;
							score2.score8_show = false;
							score2.score9_show = true;
						}
						if (hit_counter == 40)
						{
							score3.score0_show = true;
							score.score2_show = true;
							score.score1_show = false;
							score2.score9_show = false;
							score2.score0_show = true;
						}
						if (hit_counter == 42)
						{
							score3.score0_show = true;
							score.score2_show = true;
							score2.score0_show = false;
							score2.score1_show = true;
						}
						if (hit_counter == 44)
						{
							score3.score0_show = true;
							score.score2_show = true;
							score2.score1_show = false;
							score2.score2_show = true;
						}
						if (hit_counter == 46)
						{
							score3.score0_show = true;
							score.score2_show = true;
							score2.score2_show = false;
							score2.score3_show = true;
						}
						if (hit_counter == 48)
						{
							score3.score0_show = true;
							score.score2_show = true;
							score2.score3_show = false;
							score2.score4_show = true;
						}
						if (hit_counter == 50)
						{
							score3.score0_show = true;
							score.score2_show = true;
							score2.score4_show = false;
							score2.score5_show = true;
						}
						if (hit_counter == 52)
						{
							score3.score0_show = true;
							score.score2_show = true;
							score2.score5_show = false;
							score2.score6_show = true;
						}
						if (hit_counter == 54)
						{
							score3.score0_show = true;
							score.score2_show = true;
							score2.score6_show = false;
							score2.score7_show = true;
						}
						if (hit_counter == 56)
						{
							score3.score0_show = true;
							score.score2_show = true;
							score2.score7_show = false;
							score2.score8_show = true;
						}
						if (hit_counter == 58)
						{
							score3.score0_show = true;
							score.score2_show = true;
							score2.score8_show = false;
							score2.score9_show = true;
						}
						if (hit_counter == 60)
						{
							score3.score0_show = true;
							score.score2_show = false;
							score.score3_show = true;
							score2.score9_show = false;
							score2.score0_show = true;
						}
						if (hit_counter == 62)
						{
							score3.score0_show = true;
							score.score3_show = true;
							score2.score0_show = false;
							score2.score1_show = true;
						}
						if (hit_counter == 64)
						{
							score3.score0_show = true;
							score.score3_show = true;
							score2.score1_show = false;
							score2.score2_show = true;
						}
						if (hit_counter == 66)
						{
							score3.score0_show = true;
							score.score3_show = true;
							score2.score2_show = false;
							score2.score3_show = true;
						}
						if (hit_counter == 68)
						{
							score3.score0_show = true;
							score.score3_show = true;
							score2.score3_show = false;
							score2.score4_show = true;
						}
						if (hit_counter == 70)
						{
							score3.score0_show = true;
							score.score3_show = true;
							score2.score4_show = false;
							score2.score5_show = true;
						}
						if (hit_counter == 72)
						{
							score3.score0_show = true;
							score.score3_show = true;
							score2.score5_show = false;
							score2.score6_show = true;
						}
						if (hit_counter == 74)
						{
							score3.score0_show = true;
							score.score3_show = true;
							score2.score6_show = false;
							score2.score7_show = true;
						}
						if (hit_counter == 76)
						{
							score3.score0_show = true;
							score.score3_show = true;
							score2.score7_show = false;
							score2.score8_show = true;
						}
						if (hit_counter == 78)
						{
							score3.score0_show = true;
							score.score3_show = true;
							score2.score8_show = false;
							score2.score9_show = true;
						}
						if (hit_counter == 80)
						{
							score3.score0_show = true;
							score.score3_show = false;
							score.score4_show = true;
							score2.score9_show = false;
							score2.score0_show = true;
						}
						if (hit_counter == 82)
						{
							score3.score0_show = true;
							score.score4_show = true;
							score2.score0_show = false;
							score2.score1_show = true;
						}
						if (hit_counter == 84)
						{
							score3.score0_show = true;
							score.score4_show = true;
							score2.score1_show = false;
							score2.score2_show = true;
						}
						if (hit_counter == 86)
						{
							score3.score0_show = true;
							score.score4_show = true;
							score2.score2_show = false;
							score2.score3_show = true;
						}
						if (hit_counter == 88)
						{
							score3.score0_show = true;
							score.score4_show = true;
							score2.score3_show = false;
							score2.score4_show = true;
						}
						if (hit_counter == 90)
						{
							score3.score0_show = true;
							score.score4_show = true;
							score2.score4_show = false;
							score2.score5_show = true;
						}
						if (hit_counter == 92)
						{
							score3.score0_show = true;
							score.score4_show = true;
							score2.score5_show = false;
							score2.score6_show = true;
						}
						if (hit_counter == 94)
						{
							score3.score0_show = true;
							score.score4_show = true;
							score2.score6_show = false;
							score2.score7_show = true;
						}
						if (hit_counter == 96)
						{
							score3.score0_show = true;
							score.score4_show = true;
							score2.score7_show = false;
							score2.score8_show = true;
						}
						if (hit_counter == 98)
						{
							score3.score0_show = true;
							score.score4_show = true;
							score2.score8_show = false;
							score2.score9_show = true;
						}
						if (hit_counter == 100)
						{
							score3.score0_show = true;
							score.score4_show = false;
							score.score5_show = true;
							score2.score9_show = false;
							score2.score0_show = true;
						}
					}
				}
			}
		}
		for (int j = 0; j < BULLET_NUM2; j++)
		{
			if (bullet3[j].show() == true)
			{
				if (bullet3[j].x_pos > SCREEN_WIDTH)
					bullet3[j].hide();
				else
					bullet3[j].move();

				//충돌 처리(충돌한 횟수 체크해서 스코어 계산)
				for (int i = 0; i < ENEMY_NUM; i++)
				{
					if (bullet3[j].check_collision(enemy[i].x_pos, enemy[i].y_pos) == true)
					{
						hit_counter += 1;
						enemy[i].init((float)(SCREEN_WIDTH + (rand() % 300)), rand() % SCREEN_HEIGHT);
						if (hit_counter == 2) // 충돌 횟수 1회시
						{
							score3.score0_show = true;
							score.score0_show = true;
							score2.score0_show = false;
							score2.score1_show = true;
						}
						if (hit_counter == 2) // 충돌 횟수 2회시
						{
							score3.score0_show = true;
							score.score0_show = true;
							score2.score0_show = false;
							score2.score1_show = true;
						}
						if (hit_counter == 4) // 충돌 횟수 4회시
						{
							score3.score0_show = true;
							score.score0_show = true;
							score2.score1_show = false;
							score2.score2_show = true;
						}
						if (hit_counter == 6)
						{
							score3.score0_show = true;
							score.score0_show = true;
							score2.score2_show = false;
							score2.score3_show = true;
						}
						if (hit_counter == 8)
						{
							score3.score0_show = true;
							score.score0_show = true;
							score2.score3_show = false;
							score2.score4_show = true;
						}
						if (hit_counter == 10)
						{
							score3.score0_show = true;
							score.score0_show = true;
							score2.score4_show = false;
							score2.score5_show = true;
						}
						if (hit_counter == 12)
						{
							score3.score0_show = true;
							score.score0_show = true;
							score2.score5_show = false;
							score2.score6_show = true;
						}
						if (hit_counter == 14)
						{
							score3.score0_show = true;
							score.score0_show = true;
							score2.score6_show = false;
							score2.score7_show = true;
						}
						if (hit_counter == 16)
						{
							score3.score0_show = true;
							score.score0_show = true;
							score2.score7_show = false;
							score2.score8_show = true;
						}
						if (hit_counter == 18)
						{
							score3.score0_show = true;
							score.score0_show = true;
							score2.score8_show = false;
							score2.score9_show = true;
						}
						if (hit_counter == 20)
						{
							score3.score0_show = true;
							score.score0_show = false;
							score.score1_show = true;
							score2.score9_show = false;
							score2.score0_show = true;
						}
						if (hit_counter == 22)
						{
							score3.score0_show = true;
							score.score1_show = true;
							score2.score0_show = false;
							score2.score1_show = true;
						}
						if (hit_counter == 24)
						{
							score3.score0_show = true;
							score.score1_show = true;
							score2.score1_show = false;
							score2.score2_show = true;
						}
						if (hit_counter == 26)
						{
							score3.score0_show = true;
							score.score1_show = true;
							score2.score2_show = false;
							score2.score3_show = true;
						}
						if (hit_counter == 28)
						{
							score3.score0_show = true;
							score.score1_show = true;
							score2.score3_show = false;
							score2.score4_show = true;
						}
						if (hit_counter == 30)
						{
							score3.score0_show = true;
							score.score1_show = true;
							score2.score4_show = false;
							score2.score5_show = true;
						}
						if (hit_counter == 32)
						{
							score3.score0_show = true;
							score.score1_show = true;
							score2.score5_show = false;
							score2.score6_show = true;
						}
						if (hit_counter == 34)
						{
							score3.score0_show = true;
							score.score1_show = true;
							score2.score6_show = false;
							score2.score7_show = true;
						}
						if (hit_counter == 36)
						{
							score3.score0_show = true;
							score.score1_show = true;
							score2.score7_show = false;
							score2.score8_show = true;
						}
						if (hit_counter == 38)
						{
							score3.score0_show = true;
							score.score1_show = true;
							score2.score8_show = false;
							score2.score9_show = true;
						}
						if (hit_counter == 40)
						{
							score3.score0_show = true;
							score.score2_show = true;
							score.score1_show = false;
							score2.score9_show = false;
							score2.score0_show = true;
						}
						if (hit_counter == 42)
						{
							score3.score0_show = true;
							score.score2_show = true;
							score2.score0_show = false;
							score2.score1_show = true;
						}
						if (hit_counter == 44)
						{
							score3.score0_show = true;
							score.score2_show = true;
							score2.score1_show = false;
							score2.score2_show = true;
						}
						if (hit_counter == 46)
						{
							score3.score0_show = true;
							score.score2_show = true;
							score2.score2_show = false;
							score2.score3_show = true;
						}
						if (hit_counter == 48)
						{
							score3.score0_show = true;
							score.score2_show = true;
							score2.score3_show = false;
							score2.score4_show = true;
						}
						if (hit_counter == 50)
						{
							score3.score0_show = true;
							score.score2_show = true;
							score2.score4_show = false;
							score2.score5_show = true;
						}
						if (hit_counter == 52)
						{
							score3.score0_show = true;
							score.score2_show = true;
							score2.score5_show = false;
							score2.score6_show = true;
						}
						if (hit_counter == 54)
						{
							score3.score0_show = true;
							score.score2_show = true;
							score2.score6_show = false;
							score2.score7_show = true;
						}
						if (hit_counter == 56)
						{
							score3.score0_show = true;
							score.score2_show = true;
							score2.score7_show = false;
							score2.score8_show = true;
						}
						if (hit_counter == 58)
						{
							score3.score0_show = true;
							score.score2_show = true;
							score2.score8_show = false;
							score2.score9_show = true;
						}
						if (hit_counter == 60)
						{
							score3.score0_show = true;
							score.score2_show = false;
							score.score3_show = true;
							score2.score9_show = false;
							score2.score0_show = true;
						}
						if (hit_counter == 62)
						{
							score3.score0_show = true;
							score.score3_show = true;
							score2.score0_show = false;
							score2.score1_show = true;
						}
						if (hit_counter == 64)
						{
							score3.score0_show = true;
							score.score3_show = true;
							score2.score1_show = false;
							score2.score2_show = true;
						}
						if (hit_counter == 66)
						{
							score3.score0_show = true;
							score.score3_show = true;
							score2.score2_show = false;
							score2.score3_show = true;
						}
						if (hit_counter == 68)
						{
							score3.score0_show = true;
							score.score3_show = true;
							score2.score3_show = false;
							score2.score4_show = true;
						}
						if (hit_counter == 70)
						{
							score3.score0_show = true;
							score.score3_show = true;
							score2.score4_show = false;
							score2.score5_show = true;
						}
						if (hit_counter == 72)
						{
							score3.score0_show = true;
							score.score3_show = true;
							score2.score5_show = false;
							score2.score6_show = true;
						}
						if (hit_counter == 74)
						{
							score3.score0_show = true;
							score.score3_show = true;
							score2.score6_show = false;
							score2.score7_show = true;
						}
						if (hit_counter == 76)
						{
							score3.score0_show = true;
							score.score3_show = true;
							score2.score7_show = false;
							score2.score8_show = true;
						}
						if (hit_counter == 78)
						{
							score3.score0_show = true;
							score.score3_show = true;
							score2.score8_show = false;
							score2.score9_show = true;
						}
						if (hit_counter == 80)
						{
							score3.score0_show = true;
							score.score3_show = false;
							score.score4_show = true;
							score2.score9_show = false;
							score2.score0_show = true;
						}
						if (hit_counter == 82)
						{
							score3.score0_show = true;
							score.score4_show = true;
							score2.score0_show = false;
							score2.score1_show = true;
						}
						if (hit_counter == 84)
						{
							score3.score0_show = true;
							score.score4_show = true;
							score2.score1_show = false;
							score2.score2_show = true;
						}
						if (hit_counter == 86)
						{
							score3.score0_show = true;
							score.score4_show = true;
							score2.score2_show = false;
							score2.score3_show = true;
						}
						if (hit_counter == 88)
						{
							score3.score0_show = true;
							score.score4_show = true;
							score2.score3_show = false;
							score2.score4_show = true;
						}
						if (hit_counter == 90)
						{
							score3.score0_show = true;
							score.score4_show = true;
							score2.score4_show = false;
							score2.score5_show = true;
						}
						if (hit_counter == 92)
						{
							score3.score0_show = true;
							score.score4_show = true;
							score2.score5_show = false;
							score2.score6_show = true;
						}
						if (hit_counter == 94)
						{
							score3.score0_show = true;
							score.score4_show = true;
							score2.score6_show = false;
							score2.score7_show = true;
						}
						if (hit_counter == 96)
						{
							score3.score0_show = true;
							score.score4_show = true;
							score2.score7_show = false;
							score2.score8_show = true;
						}
						if (hit_counter == 98)
						{
							score3.score0_show = true;
							score.score4_show = true;
							score2.score8_show = false;
							score2.score9_show = true;
						}
						if (hit_counter == 100)
						{
							score3.score0_show = true;
							score.score4_show = false;
							score.score5_show = true;
							score2.score9_show = false;
							score2.score0_show = true;
						}
					}
				}
			}
		}

		float distance = 60;
		//적들 처리 
		for (int i = 0; i < ENEMY_NUM; i++)
		{
			if (enemy[i].x_pos < 0)
			{
				enemy[i].init((float)SCREEN_WIDTH + distance, distance);
				distance += distance;
			}
			else
				enemy[i].move();
		}
		//적 총알 처리
		for (int i = 0; i < ENEMY_NUM; i++)
		{
			if (ebullet[i].show() == false)
			{
				ebullet[i].active();
				ebullet[i].init(enemy[i].x_pos, enemy[i].y_pos);
				
			}
		}
		for (int i = 0; i < ENEMY_NUM; i++)
		{
			if (ebullet[i].show() == true)
			{
				if (ebullet[i].x_pos < -64)
				{
					ebullet[i].hide();
					ebullet[i].move();
				}
				else
					ebullet[i].move();
				if (ebullet[i].check_collision(hero.x_pos, hero.y_pos) == true)
				{
					hero.active();
					hero.hit_init(hero.x_pos, (hero.y_pos) - 5);
				}
			}
		}
		if (KEY_DOWN(VK_CONTROL)) //넉백스킬(신라천정)
		{
			sndPlaySoundA("C:\\Users\\Administrator.MSDN-SPECIAL\\Desktop\\Matrices49860489\\Skill.wav", SND_ASYNC | SND_NODEFAULT | SND_ASYNC);
			for (int i = 0; i < ENEMY_NUM; i++)
			{
				if (enemy[i].x_pos < 600)
				{
					enemy[i].init(enemy[i].x_pos + 600, enemy[i].y_pos);
					ebullet[i].init(ebullet[i].x_pos + 600, ebullet[i].y_pos);
				}
			}
		}

	}
}


// this is the function used to render a single frame 디스플레이
void render_frame(void)
{

	if (KEY_DOWN(VK_TAB))
	{
		Scene1 = false;
		Scene2 = true;
	}

	if (Scene1 == true)
	{
		//ui 배경음 재생
		mciSendCommand(NULL, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE, (DWORD)(LPVOID)&mci_open);
		dwID = mci_open.wDeviceID;
		mciSendCommand(dwID, MCI_PLAY, MCI_NOTIFY, (DWORD)(LPVOID)&mci_play);

		d3ddev->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);

		d3ddev->BeginScene();    // begins the 3D scene

		d3dspt->Begin(D3DXSPRITE_ALPHABLEND);
		
		RECT part; // ui 배경
		SetRect(&part, 0, 0, 840, 480);
		D3DXVECTOR3 center(0.0f, 0.0f, 0.0f);
		D3DXVECTOR3 position(0.0f, 0.0f, 0.0f);
		d3dspt->Draw(sprite_bg, &part, &center, &position, D3DCOLOR_ARGB(255, 255, 255, 255));

		RECT tpart;// ui 타이틀
		SetRect(&tpart, 0, 0,500, 124);
		D3DXVECTOR3 tcenter(0.0f, 0.0f, 0.0f);
		D3DXVECTOR3 tposition(160.0f, 50.0f, 0.0f);
		d3dspt->Draw(sprite_title, &tpart, &tcenter, &tposition, D3DCOLOR_ARGB(255, 255, 255, 255));

		RECT ppart; // ui PRESS
		SetRect(&ppart, 0, 0, 562, 77);
		D3DXVECTOR3 pcenter(0.0f, 0.0f, 0.0f);
		D3DXVECTOR3 pposition(130.0f, 360.0f, 0.0f);
		static int pcounter = 0;
		pcounter = pcounter + 1;
		if (pcounter >= 42) pcounter = 0;
		if(pcounter < 22)
			d3dspt->Draw(sprite_press, &ppart, &pcenter, &pposition, D3DCOLOR_ARGB(255, 255, 255, 255));
		if(pcounter > 22)
			d3dspt->Draw(sprite_press2, &ppart, &pcenter, &pposition, D3DCOLOR_ARGB(255, 255, 255, 255));
		
	
		

		d3dspt->End();    // end sprite drawing

		d3ddev->EndScene();    // ends the 3D scene

		d3ddev->Present(NULL, NULL, NULL, NULL);

		return;


	}
	if (Scene2 == true )
	{
		bool skill = false;
		//ui 배경음 끄기
		mciSendCommand(1, MCI_SEEK, MCI_SEEK_TO_START, (DWORD)(LPVOID)NULL);

		//ingame 배경음 재생
		mciSendCommand(NULL, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE, (DWORD)(LPVOID)&mci_open2);
		dwID2 = mci_open2.wDeviceID;
		mciSendCommand(dwID2, MCI_PLAY, MCI_DGV_PLAY_REPEAT, (DWORD)(LPVOID)&mci_play2); // MCI_NOTIFY(loop해제) , REPEAT
		// clear the window to a deep blue
		d3ddev->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);

		d3ddev->BeginScene();    // begins the 3D scene

		d3dspt->Begin(D3DXSPRITE_ALPHABLEND);

		RECT ipart;// ingame 배경
		SetRect(&ipart, 0, 0, 840, 480);
		D3DXVECTOR3 icenter(0.0f, 0.0f, 0.0f);
		for (int i = 0; i < BG_NUM; i++)
		{
			D3DXVECTOR3 iposition(bg[i].x_pos, 0.0f, 0.0f);
			d3dspt->Draw(sprite_inbg, &ipart, &icenter, &iposition, D3DCOLOR_ARGB(255, 255, 255, 255));
		}
		//스코어 첫째자리
		if (score3.score0_show == true) // score 0점을 불러온다
		{
			RECT Spart1;
			SetRect(&Spart1, 0, 0, 25, 40);
			D3DXVECTOR3 Scenter1(0.0f, 0.0f, 0.0f);
			D3DXVECTOR3 Sposition1(score3.x_pos, score3.y_pos, 0.0f);
			d3dspt->Draw(sprite_score0, &Spart1, &Scenter1, &Sposition1, D3DCOLOR_ARGB(255, 255, 255, 255));
		}
		//스코어 둘째자리

		if (score2.score0_show == true ) // score 0점을 불러온다
		{
			RECT Spart1;
			SetRect(&Spart1, 0, 0, 25, 40);
			D3DXVECTOR3 Scenter1(0.0f, 0.0f, 0.0f);
			D3DXVECTOR3 Sposition1(score2.x_pos, score2.y_pos, 0.0f);
			d3dspt->Draw(sprite_score0, &Spart1, &Scenter1, &Sposition1, D3DCOLOR_ARGB(255, 255, 255, 255));
		}

		if (score2.score1_show == true) // score 10점을 불러온다
		{
			RECT Spart2;
			SetRect(&Spart2, 0, 0, 25, 40);
			D3DXVECTOR3 Scenter2(0.0f, 0.0f, 0.0f);
			D3DXVECTOR3 Sposition2(score2.x_pos, score2.y_pos, 0.0f);
			d3dspt->Draw(sprite_score1, &Spart2, &Scenter2, &Sposition2, D3DCOLOR_ARGB(255, 255, 255, 255));
		}

		if (score2.score2_show == true)// score 20점을 불러온다
		{
			RECT Spart3;
			SetRect(&Spart3, 0, 0, 25, 40);
			D3DXVECTOR3 Scenter3(0.0f, 0.0f, 0.0f);
			D3DXVECTOR3 Sposition3(score2.x_pos, score2.y_pos, 0.0f);
			d3dspt->Draw(sprite_score2, &Spart3, &Scenter3, &Sposition3, D3DCOLOR_ARGB(255, 255, 255, 255));
		}

		if (score2.score3_show == true)//score 30점을 불러온다
		{
			RECT Spart4;
			SetRect(&Spart4, 0, 0, 25, 40);
			D3DXVECTOR3 Scenter4(0.0f, 0.0f, 0.0f);
			D3DXVECTOR3 Sposition4(score2.x_pos, score2.y_pos, 0.0f);
			d3dspt->Draw(sprite_score3, &Spart4, &Scenter4, &Sposition4, D3DCOLOR_ARGB(255, 255, 255, 255));
		}

		if (score2.score4_show == true)//score 40점을 불러온다
		{
			RECT Spart5;
			SetRect(&Spart5, 0, 0, 25, 40);
			D3DXVECTOR3 Scenter5(0.0f, 0.0f, 0.0f);
			D3DXVECTOR3 Sposition5(score2.x_pos, score2.y_pos, 0.0f);
			d3dspt->Draw(sprite_score4, &Spart5, &Scenter5, &Sposition5, D3DCOLOR_ARGB(255, 255, 255, 255));
		}

		if (score2.score5_show == true)//score 50점을 불러온다
		{
			RECT Spart6;
			SetRect(&Spart6, 0, 0, 25, 40);
			D3DXVECTOR3 Scenter6(0.0f, 0.0f, 0.0f);
			D3DXVECTOR3 Sposition6(score2.x_pos, score2.y_pos, 0.0f);
			d3dspt->Draw(sprite_score5, &Spart6, &Scenter6, &Sposition6, D3DCOLOR_ARGB(255, 255, 255, 255));
		}
		if (score2.score6_show == true)//score 60점을 불러온다
		{
			RECT Spart7;
			SetRect(&Spart7, 0, 0, 25, 40);
			D3DXVECTOR3 Scenter7(0.0f, 0.0f, 0.0f);
			D3DXVECTOR3 Sposition7(score2.x_pos, score2.y_pos, 0.0f);
			d3dspt->Draw(sprite_score6, &Spart7, &Scenter7, &Sposition7, D3DCOLOR_ARGB(255, 255, 255, 255));
		}
		if (score2.score7_show == true)//score 70점을 불러온다
		{
			RECT Spart8;
			SetRect(&Spart8, 0, 0, 25, 40);
			D3DXVECTOR3 Scenter8(0.0f, 0.0f, 0.0f);
			D3DXVECTOR3 Sposition8(score2.x_pos, score2.y_pos, 0.0f);
			d3dspt->Draw(sprite_score7, &Spart8, &Scenter8, &Sposition8, D3DCOLOR_ARGB(255, 255, 255, 255));
		}
		if (score2.score8_show == true)//score 80점을 불러온다
		{
			RECT Spart9;
			SetRect(&Spart9, 0, 0, 25, 40);
			D3DXVECTOR3 Scenter9(0.0f, 0.0f, 0.0f);
			D3DXVECTOR3 Sposition9(score2.x_pos, score2.y_pos, 0.0f);
			d3dspt->Draw(sprite_score8, &Spart9, &Scenter9, &Sposition9, D3DCOLOR_ARGB(255, 255, 255, 255));
		}
		if (score2.score9_show == true)//score 90점을 불러온다
		{
			RECT Spart10;
			SetRect(&Spart10, 0, 0, 25, 40);
			D3DXVECTOR3 Scenter10(0.0f, 0.0f, 0.0f);
			D3DXVECTOR3 Sposition10(score2.x_pos, score2.y_pos, 0.0f);
			d3dspt->Draw(sprite_score9, &Spart10, &Scenter10, &Sposition10, D3DCOLOR_ARGB(255, 255, 255, 255));
		}
		// 스코어 셋째자리
		if (score.score0_show == true) // score 0점을 불러온다
		{
			RECT Spart1;
			SetRect(&Spart1, 0, 0, 25, 40);
			D3DXVECTOR3 Scenter1(0.0f, 0.0f, 0.0f);
			D3DXVECTOR3 Sposition1(score.x_pos, score.y_pos, 0.0f);
			d3dspt->Draw(sprite_score0, &Spart1, &Scenter1, &Sposition1, D3DCOLOR_ARGB(255, 255, 255, 255));
		}

		if (score.score1_show == true) // score 10점을 불러온다
		{
			RECT Spart2;
			SetRect(&Spart2, 0, 0, 25, 40);
			D3DXVECTOR3 Scenter2(0.0f, 0.0f, 0.0f);
			D3DXVECTOR3 Sposition2(score.x_pos, score.y_pos, 0.0f);
			d3dspt->Draw(sprite_score1, &Spart2, &Scenter2, &Sposition2, D3DCOLOR_ARGB(255, 255, 255, 255));
		}

		if (score.score2_show == true)// score 20점을 불러온다
		{
			RECT Spart3;
			SetRect(&Spart3, 0, 0, 25, 40);
			D3DXVECTOR3 Scenter3(0.0f, 0.0f, 0.0f);
			D3DXVECTOR3 Sposition3(score.x_pos, score.y_pos, 0.0f);
			d3dspt->Draw(sprite_score2, &Spart3, &Scenter3, &Sposition3, D3DCOLOR_ARGB(255, 255, 255, 255));
		}

		if (score.score3_show == true)//score 30점을 불러온다
		{
			RECT Spart4;
			SetRect(&Spart4, 0, 0, 25, 40);
			D3DXVECTOR3 Scenter4(0.0f, 0.0f, 0.0f);
			D3DXVECTOR3 Sposition4(score.x_pos, score.y_pos, 0.0f);
			d3dspt->Draw(sprite_score3, &Spart4, &Scenter4, &Sposition4, D3DCOLOR_ARGB(255, 255, 255, 255));
		}

		if (score.score4_show == true)//score 40점을 불러온다
		{
			RECT Spart5;
			SetRect(&Spart5, 0, 0, 25, 40);
			D3DXVECTOR3 Scenter5(0.0f, 0.0f, 0.0f);
			D3DXVECTOR3 Sposition5(score.x_pos, score.y_pos, 0.0f);
			d3dspt->Draw(sprite_score4, &Spart5, &Scenter5, &Sposition5, D3DCOLOR_ARGB(255, 255, 255, 255));
		}

		if (score.score5_show == true)//score 50점을 불러온다
		{
			RECT Spart6;
			SetRect(&Spart6, 0, 0, 25, 40);
			D3DXVECTOR3 Scenter6(0.0f, 0.0f, 0.0f);
			D3DXVECTOR3 Sposition6(score.x_pos, score.y_pos, 0.0f);
			d3dspt->Draw(sprite_score5, &Spart6, &Scenter6, &Sposition6, D3DCOLOR_ARGB(255, 255, 255, 255));
		}
		if (score.score6_show == true)//score 60점을 불러온다
		{
			RECT Spart7;
			SetRect(&Spart7, 0, 0, 25, 40);
			D3DXVECTOR3 Scenter7(0.0f, 0.0f, 0.0f);
			D3DXVECTOR3 Sposition7(score.x_pos, score.y_pos, 0.0f);
			d3dspt->Draw(sprite_score6, &Spart7, &Scenter7, &Sposition7, D3DCOLOR_ARGB(255, 255, 255, 255));
		}
		if (score.score7_show == true)//score 70점을 불러온다
		{
			RECT Spart8;
			SetRect(&Spart8, 0, 0, 25, 40);
			D3DXVECTOR3 Scenter8(0.0f, 0.0f, 0.0f);
			D3DXVECTOR3 Sposition8(score.x_pos, score.y_pos, 0.0f);
			d3dspt->Draw(sprite_score7, &Spart8, &Scenter8, &Sposition8, D3DCOLOR_ARGB(255, 255, 255, 255));
		}
		if (score.score8_show == true)//score 80점을 불러온다
		{
			RECT Spart9;
			SetRect(&Spart9, 0, 0, 25, 40);
			D3DXVECTOR3 Scenter9(0.0f, 0.0f, 0.0f);
			D3DXVECTOR3 Sposition9(score.x_pos, score.y_pos, 0.0f);
			d3dspt->Draw(sprite_score8, &Spart9, &Scenter9, &Sposition9, D3DCOLOR_ARGB(255, 255, 255, 255));
		}
		if (score.score9_show == true)//score 90점을 불러온다
		{
			RECT Spart10;
			SetRect(&Spart10, 0, 0, 25, 40);
			D3DXVECTOR3 Scenter10(0.0f, 0.0f, 0.0f);
			D3DXVECTOR3 Sposition10(score.x_pos, score.y_pos, 0.0f);
			d3dspt->Draw(sprite_score9, &Spart10, &Scenter10, &Sposition10, D3DCOLOR_ARGB(255, 255, 255, 255));
		}
		//주인공 대기 스프라이트
		static int counter = 0;
		if (hero.hit_Show == false)
		{							
			RECT part1;
			SetRect(&part1, 0, 0, 64, 100);
			D3DXVECTOR3 center1(0.0f, 0.0f, 0.0f);
			D3DXVECTOR3 position1(hero.x_pos, hero.y_pos, 0.0f);
			
			counter += 1 ;
			if (counter >= 20) counter = 0;
		
			switch (counter / 5)
			{
			case 0:
				d3dspt->Draw(sprite_hero, &part1, &center1, &position1, D3DCOLOR_ARGB(255, 255, 255, 255));
				break;
			case 1:
				d3dspt->Draw(sprite_hero2, &part1, &center1, &position1, D3DCOLOR_ARGB(255, 255, 255, 255));
				break;
			case 2:
				d3dspt->Draw(sprite_hero3, &part1, &center1, &position1, D3DCOLOR_ARGB(255, 255, 255, 255));
				break;
			case 3:
				d3dspt->Draw(sprite_hero4, &part1, &center1, &position1, D3DCOLOR_ARGB(255, 255, 255, 255));
				break;
			}
		}
		//주인공 피격 스프라이트
		if (hero.hit_Show == true)
		{
			RECT part_1;
			SetRect(&part_1, 0, 0, 64, 64);
			D3DXVECTOR3 center_1(0.0f, 0.0f, 0.0f);
			D3DXVECTOR3 position_1(hero.x_pos, hero.y_pos, 0.0f);
			d3dspt->Draw(sprite_hero_hit, &part_1, &center_1, &position_1, D3DCOLOR_ARGB(255, 255, 255, 255));
		}
	
		//주인공 스킬 스프라이트
		if (KEY_DOWN(VK_CONTROL))
		{
			skill = true;
		}
		if (hero.hit_Show == false)
		{
			if (skill == true)
			{
				RECT part_1;
				SetRect(&part_1, 0, 0, 64, 100);
				D3DXVECTOR3 center_1(0.0f, 0.0f, 0.0f);
				D3DXVECTOR3 position_1(hero.x_pos, hero.y_pos, 0.0f);
				d3dspt->Draw(sprite_hero_skill, &part_1, &center_1, &position_1, D3DCOLOR_ARGB(255, 255, 255, 255));
			}
		}
		////총알 
		for (int i = 0; i < BULLET_NUM; i++)
		{
			if (bullet[i].bShow == true)
			{
				RECT part1;
				SetRect(&part1, 0, 0, 64, 64);
				D3DXVECTOR3 center1(0.0f, 0.0f, 0.0f);    // center at the upper-left corner
				D3DXVECTOR3 position1(bullet[i].x_pos, bullet[i].y_pos, 0.0f);    // position at 50, 50 with no depth
				d3dspt->Draw(sprite_bullet, &part1, &center1, &position1, D3DCOLOR_ARGB(255, 255, 255, 255));
			}
		}
		for (int i = 0; i < BULLET_NUM2; i++)
		{
			if (bullet2[i].bShow == true)  //여기에요
			{
				RECT part1;
				SetRect(&part1, 0, 0, 64, 64);
				D3DXVECTOR3 center1(0.0f, 0.0f, 0.0f);    // center at the upper-left corner
				D3DXVECTOR3 position1(bullet2[i].x_pos, bullet2[i].y_pos, 0.0f);    // position at 50, 50 with no depth
				d3dspt->Draw(sprite_bullet2, &part1, &center1, &position1, D3DCOLOR_ARGB(255, 255, 255, 255));
			}
		}
		for (int i = 0; i < BULLET_NUM2; i++)
		{
			if (bullet3[i].bShow == true)
			{
				RECT part1;
				SetRect(&part1, 0, 0, 64, 64);
				D3DXVECTOR3 center1(0.0f, 0.0f, 0.0f);    // center at the upper-left corner
				D3DXVECTOR3 position1(bullet3[i].x_pos, bullet3[i].y_pos, 0.0f);    // position at 50, 50 with no depth
				d3dspt->Draw(sprite_bullet2, &part1, &center1, &position1, D3DCOLOR_ARGB(255, 255, 255, 255));
			}
		}
		////에네미 
		RECT part2;
		SetRect(&part2, 0, 0, 64, 64);
		D3DXVECTOR3 center2(0.0f, 0.0f, 0.0f);    // center at the upper-left corner

		for (int i = 0; i < ENEMY_NUM; i++)
		{
			D3DXVECTOR3 position2(enemy[i].x_pos, enemy[i].y_pos, 0.0f);    // position at 50, 50 with no depth
			d3dspt->Draw(sprite_enemy, &part2, &center2, &position2, D3DCOLOR_ARGB(255, 255, 255, 255));
		}
		//적총알
		RECT part3;
		SetRect(&part3, 0, 0, 30, 29);
		D3DXVECTOR3 center3(0.0f, 0.0f, 0.0f);    // center at the upper-left corner
		for (int i = 0; i < ENEMY_NUM; i++)
		{
			D3DXVECTOR3 position3(ebullet[i].x_pos, ebullet[i].y_pos, 0.0f);    // position at 50, 50 with no depth
			if (ebullet[i].bShow == true)
			{
				d3dspt->Draw(sprite_enemy_bullet, &part3, &center3, &position3, D3DCOLOR_ARGB(255, 255, 255, 255));
			}
		}


		d3dspt->End();    // end sprite drawing

		d3ddev->EndScene();    // ends the 3D scene

		d3ddev->Present(NULL, NULL, NULL, NULL);

		return;
	}
}


// this is the function that cleans up Direct3D and COM
void cleanD3D(void)
{
	sprite->Release();
	d3ddev->Release();
	d3d->Release();

	sprite_bg->Release();
	sprite_title->Release();
	sprite_press->Release();
	sprite_press2->Release();
	//객체 해제 
	sprite_inbg->Release();

	//sprite_hero->Release();
	//sprite_hero2->Release();
	//sprite_hero3->Release();
	//sprite_hero4->Release();
	//sprite_hero_hit->Release();
	//sprite_hero_skill->Release();
	//sprite_bullet->Release();
	//sprite_bullet2->Release();
	//sprite_bullet3->Release();

	sprite_enemy->Release();
	sprite_enemy_bullet->Release();

	return;
}
