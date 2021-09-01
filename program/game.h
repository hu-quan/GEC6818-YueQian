#ifndef __GAME_H__
#define __GAME_H__

#include <time.h>
#include <string.h>
#define MAXVEX 25

// ��¼������Ϣ�Ľṹ��
typedef struct Vex {
	int x;
	int y;
}Vex;

typedef struct game {
	struct Vex* game;
}Game;

// ��ʼ����Ϸ
Game *
InitGameVex(void);

// ��ʼ����������
void
InitVexPosition(Game* g);

// ������Ϸ������ڴ�
void
DestoryGame(Game* g);

// ���������Ӧ�Ķ���
int
LightVex(Game* g, unsigned int x, unsigned int y);

//  ��ʾ��Ŀ
void
ShowChallengVex(Game* g, int *arr,int level);

// game start
int
GameStart();

// ����Ƿ�ش���ȷ
int
IsEqual(int* src, int *dest,int level);

void
Mymemset(int*, int len);

void
SetHard();

void
ShowGameSign(unsigned int x, unsigned int y);

void
InitData(void);

void
InitQuestion(int *,int *,int);
#endif