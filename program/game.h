#ifndef __GAME_H__
#define __GAME_H__

#include <time.h>
#include <string.h>
#define MAXVEX 25

// 记录顶点信息的结构体
typedef struct Vex {
	int x;
	int y;
}Vex;

typedef struct game {
	struct Vex* game;
}Game;

// 初始化游戏
Game *
InitGameVex(void);

// 初始化顶点坐标
void
InitVexPosition(Game* g);

// 销毁游戏申请的内存
void
DestoryGame(Game* g);

// 点击点亮相应的顶点
int
LightVex(Game* g, unsigned int x, unsigned int y);

//  显示题目
void
ShowChallengVex(Game* g, int *arr,int level);

// game start
int
GameStart();

// 检查是否回答正确
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