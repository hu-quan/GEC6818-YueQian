#ifndef __GRAPH_H__
#define __GRAPH_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXSIZE 100
#define NaN 65535
/* 图的邻接矩阵表示法 */

typedef struct ArcNode{
	char city[12];  // 该弧的顶点信息 即城市名
	int dist;        // 该弧的长度 即两城市间的距离
	struct ArcNode* next;
}ArcNode,*PArcNode;

typedef struct VexNode {
	char city[12]; 
	struct ArcNode* arc;
}VexNode,*PVexNode;

typedef struct Graph {
	struct VexNode* vex;
	int num; // 顶点个数 即总城市数
	int size;
}Graph,*PGraph;

// 初始化一个图
PGraph
InitGraph();

// 销毁一个图
void
Destory(PGraph g);

// 为图添加一个顶点
void
InsertVex(PGraph g, char*city);

// 为图的两个顶点添加一条弧
int
InsertArc(PGraph g, char* srccity, char* destcity, int dist);

// 删除图中两顶点的一条边
int
DeleteArc(PGraph g, char* srccity, char* destcity);

// 删除图中的一个顶点 包括删除所有的它与邻接顶点的边
int
DeleteVex(PGraph g, char* city);

// 显示交通图
void
DisplayTrafficMap(PGraph g);

void
InitTrafficMap(PGraph g);

// floyd 算法 求出所有顶点之间的最短距离
void
Floyd(PGraph g);

// 打印两个城市之间的最短路径
void
ShortestPath(PGraph g, char* src, char* dest);

#endif