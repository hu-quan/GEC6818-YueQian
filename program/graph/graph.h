#ifndef __GRAPH_H__
#define __GRAPH_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXSIZE 100
#define NaN 65535
/* ͼ���ڽӾ����ʾ�� */

typedef struct ArcNode{
	char city[12];  // �û��Ķ�����Ϣ ��������
	int dist;        // �û��ĳ��� �������м�ľ���
	struct ArcNode* next;
}ArcNode,*PArcNode;

typedef struct VexNode {
	char city[12]; 
	struct ArcNode* arc;
}VexNode,*PVexNode;

typedef struct Graph {
	struct VexNode* vex;
	int num; // ������� ���ܳ�����
	int size;
}Graph,*PGraph;

// ��ʼ��һ��ͼ
PGraph
InitGraph();

// ����һ��ͼ
void
Destory(PGraph g);

// Ϊͼ���һ������
void
InsertVex(PGraph g, char*city);

// Ϊͼ�������������һ����
int
InsertArc(PGraph g, char* srccity, char* destcity, int dist);

// ɾ��ͼ���������һ����
int
DeleteArc(PGraph g, char* srccity, char* destcity);

// ɾ��ͼ�е�һ������ ����ɾ�����е������ڽӶ���ı�
int
DeleteVex(PGraph g, char* city);

// ��ʾ��ͨͼ
void
DisplayTrafficMap(PGraph g);

void
InitTrafficMap(PGraph g);

// floyd �㷨 ������ж���֮�����̾���
void
Floyd(PGraph g);

// ��ӡ��������֮������·��
void
ShortestPath(PGraph g, char* src, char* dest);

#endif