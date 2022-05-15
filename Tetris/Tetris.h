#pragma once

#include "resource.h"
#include "stdafx.h"
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")
#include <fstream>
#include <cmath>
// ����һ���㣬������ʾ�����λ��
struct Point{
	int x;
	int y;
};

int nType  = 0;     // ��һ��������
int type   = 0;		// ��ǰ��������
int state  = 0;		// ��ǰ����״̬
int tScore = 1;					// ��ǰ�÷�
bool gameOverFlag = false;		// ��Ϸ�Ѿ�����
bool suspendFlag = false;       // ��ͣ��Ϸ
bool targetFlag = false; // ������׼��
bool overflowing = false;
bool magicnum = false;
bool winwin = false;
bool musicplay = true;
bool wudi = false;
bool music_switch = false;
// int savedArray[21][20] = {0};
int workRegion [20][10] = {0};	// ���������ݣ�data[i][j]==0��ʾ��λ��û�б�ռ��
Point point;					// ��ǰ����ĵ�ǰλ��
Point target;					// ��ǰ����Ŀ��λ�ã�������׼��
Point new_point;                // ��������ת��
int bricks[7][4][4][4] =
{
	{   // I�ͷ���
		{{0, 0, 0, 0},
		{0, 0, 0, 0},
		{1, 1, 1, 1},
		{0, 0, 0, 0}},

		{{0, 0, 1, 0},
		{0, 0, 1, 0},
		{0, 0, 1, 0},
		{0, 0, 1, 0}},

		{{0, 0, 0, 0},
		{0, 0, 0, 0},
		{1, 1, 1, 1},
		{0, 0, 0, 0}},

		{{0, 0, 1, 0},
		{0, 0, 1, 0},
		{0, 0, 1, 0},
		{0, 0, 1, 0}}
	},
	{   // T�ͷ���
		{{0, 0, 0, 0},
		{0, 0, 2, 0},
		{0, 2, 2, 2},
		{0, 0, 0, 0}},

		{{0, 0, 0, 0},
		{0, 0, 2, 0},
		{0, 0, 2, 2},
		{0, 0, 2, 0}},

		{{0, 0, 0, 0},
		{0, 0, 0, 0},
		{0, 2, 2, 2},
		{0, 0, 2, 0}},

		{{0, 0, 0, 0},
		{0, 0, 2, 0},
		{0, 2, 2, 0},
		{0, 0, 2, 0}},
	},
	{   // L�ͷ���
		{{0, 3, 0, 0},
		{0, 3, 0, 0},
		{0, 3, 3, 0},
		{0, 0, 0, 0}},

		{{0, 0, 0, 0},
		{3, 3, 3, 0},
		{3, 0, 0, 0},
		{0, 0, 0, 0}},	

		{{3, 3, 0, 0},
		{0, 3, 0, 0},
		{0, 3, 0, 0},
		{0, 0, 0, 0}},	

		{{0, 0, 3, 0},
		{3, 3, 3, 0},
		{0, 0, 0, 0},
		{0, 0, 0, 0}}
	},            
	{	// J�ͷ���
		{{0, 0, 4, 0},
		{0, 0, 4, 0},
		{0, 4, 4, 0},
		{0, 0, 0, 0}},

		{{0, 4, 0, 0},
		{0, 4, 4, 4},
		{0, 0, 0, 0},
		{0, 0, 0, 0}},

		{{0, 0, 4, 4},
		{0, 0, 4, 0},
		{0, 0, 4, 0},
		{0, 0, 0, 0}},

		{{0, 0, 0, 0},
		{0, 4, 4, 4},
		{0, 0, 0, 4},
		{0, 0, 0, 0}}
	},			
	{	// O�ͷ���
		{{0, 0, 0, 0},
		{0, 5, 5, 0},
		{0, 5, 5, 0},
		{0, 0, 0, 0}},

		{{0, 0, 0, 0},
		{0, 5, 5, 0},
		{0, 5, 5, 0},
		{0, 0, 0, 0}},

		{{0, 0, 0, 0},
		{0, 5, 5, 0},
		{0, 5, 5, 0},
		{0, 0, 0, 0}},

		{{0, 0, 0, 0},
		{0, 5, 5, 0},
		{0, 5, 5, 0},
		{0, 0, 0, 0}}
	},		
	{   // S�ͷ���
		{{0, 6, 0, 0},
		{0, 6, 6, 0},
		{0, 0, 6, 0},
		{0, 0, 0, 0}},

		{{0, 0, 0, 0},
		{0, 6, 6, 0},
		{6, 6, 0, 0},
		{0, 0, 0, 0}},

		{{6, 0, 0, 0},
		{6, 6, 0, 0},
		{0, 6, 0, 0},
		{0, 0, 0, 0}},

		{{0, 6, 6, 0},
		{6, 6, 0, 0},
		{0, 0, 0, 0},
		{0, 0, 0, 0}}
	},
	{	// Z�ͷ���
		{{0, 0, 7, 0},
		{0, 7, 7, 0},
		{0, 7, 0, 0},
		{0, 0, 0, 0}},

		{{0, 7, 7, 0},
		{0, 0, 7, 7},
		{0, 0, 0, 0},
		{0, 0, 0, 0}},

		{{0, 0, 0, 7},
		{0, 0, 7, 7},
		{0, 0, 7, 0},
		{0, 0, 0, 0}},

		{{0, 0, 0, 0},
		{0, 7, 7, 0},
		{0, 0, 7, 7},
		{0, 0, 0, 0}}
	}		
};

// ����7�ַ������ɫ
COLORREF BrickColor[7] = {
	RGB(255, 0, 0),
	RGB(0, 255, 0),
	RGB(0, 0, 255),
	RGB(0, 255, 255),
	RGB(255, 150, 0),
	RGB(255, 255, 0),
	RGB(168, 0, 168)
};

// �����ļ����

// �жϵ�ǰ�����Ƿ���������ƶ�
bool CanMoveDown();

// �жϵ�ǰ�����Ƿ���������ƶ�
bool CanMoveLeft();

// �жϵ�ǰ�����Ƿ���������ƶ�
bool CanMoveRight();

// ��ǰ���������ƶ�
void MoveDown();

// ��ǰ���������ƶ�
void MoveLeft();

// ��ǰ���������ƶ�
void MoveRight();

// ��ת��ǰ����
void Rotate();

// ����ǰ����ֱ�����䵽�������λ��
void DropDown();

// ����ǰ����̶��ڵ�ǰλ��
void Fixing();

// ��ȥһ��
void DeleteOneLine(int number);

// ���в���
void DeleteLines();

// ����
void readSaved();
// �浵
void saveNow();
// �ж���Ϸ����
bool GameOver();

// backdoor
bool backdoor(int array[]);

// ������׼��λ��
void ComputeTarget();

// ���¿�ʼ
void Restart();

// ������Ļ
void TDrawScreen(HDC hdc, HWND hWnd);