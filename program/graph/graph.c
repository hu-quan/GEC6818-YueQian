#include "graph.h"

static int dist[MAXSIZE][MAXSIZE] = { 0 };
static int path[MAXSIZE][MAXSIZE];
// 初始化一个图
PGraph
InitGraph()
{
	PGraph g = NULL;
	g = malloc(sizeof(Graph));
	if (g == NULL)
	{
		printf("g is NULL in graph.c");
		return NULL;
	}
	g->vex = malloc(sizeof(VexNode) * MAXSIZE);
	if (g->vex == NULL)
	{
		printf("g->vex is NULL in graph.c");
		free(g);
		return NULL;
	}
	g->size = MAXSIZE;
	g->num = 0;
	return g;
}

// 销毁一个图
void
Destory(PGraph g)
{
	if (g == NULL || g->vex == NULL)
		return;
	for (int i = 0; i < g->num; i++)
	{
		while (g->vex[i].arc)
		{
			PArcNode p = g->vex[i].arc;
			g->vex[i].arc = p->next;
			free(p);
		}
	}
	free(g->vex);
	g->vex = NULL;
	free(g);
	g = NULL;
}

// 为图添加一个顶点
void
InsertVex(PGraph g, char* city)
{
	if (g == NULL || g->vex == NULL)
		return;
	// 空间不足时扩充空间
	if (g->num >= g->size)
	{
		PVexNode newbase = realloc(g->vex, (MAXSIZE + MAXSIZE) * sizeof(VexNode));
		if (newbase == NULL)
		{
			printf("newbase is NULL");
			return;
		}
		g->vex = newbase;
		g->size += MAXSIZE;
	}

	VexNode node;
	node.arc = NULL;
	strcpy(node.city, city);
	g->vex[g->num++] = node;
}

int flag = -1;
// 为图的两个顶点添加一条弧
int
InsertArc(PGraph g, char* srccity, char* destcity, int dist)
{
	if (g == NULL || g->vex == NULL)
		return -1;
	// 找到边的起点城市 并且确定存在终点城市
	int i,j;
	for (i = 0; i < g->num; i++)
	{
		if (!strcmp(g->vex[i].city, srccity))
			break;
	}
	for (j = 0; j < g->num; j++)
	{
		if (!strcmp(g->vex[j].city, destcity))
			break;
	}
	if (i == g->num)
	{
		printf("No find %s\n", srccity);
		return -1;
	}
	if (j == g->num)
	{
		printf("No find %s\n", destcity);
		return -1;
	}

	PArcNode node = NULL;
	node = malloc(sizeof(ArcNode));
	strcpy(node->city, destcity);
	node->dist = dist;
	node->next = NULL;

	if (g->vex[i].arc == NULL)
	{
		g->vex[i].arc = node;
	}

	else
	{
		PArcNode p = g->vex[i].arc;
		while (p->next)
		{
			p = p->next;
		}
		p->next = node;
	}
	if (flag == 1)
	{
		flag = -1;
		return 1;
	}
	flag = 1;
	InsertArc(g, destcity, srccity, dist);  // 无向图双向添加边
}

// 删除图中两顶点的一条边
int
DeleteArc(PGraph g, char* srccity, char* destcity)
{
	if (g == NULL || g->vex == NULL)
		return -1;
	// 找到起始顶点
	int index;
	for (index = 0; index < g->num; index++)
	{
		if (!strcmp(g->vex[index].city, srccity))
			break;
	}
	if (index == g->num)
	{
		printf("No find %s\n", srccity);
		return -1;
	}
	// 在起始顶点的所有边中找到与终点的边
	if (g->vex[index].arc)
	{
		PArcNode p = g->vex[index].arc;
		PArcNode pr = NULL;
		if (!strcmp(p->city, destcity))
		{
			g->vex[index].arc = p->next;
			free(p);
		}
		else
		{
			while (p)
			{
				if (!strcmp(p->city, destcity))
					break;
				pr = p;
				p = p->next;
			}
			if (p == NULL)
			{
				printf("No find Arc of %s and %s!\n", srccity, destcity);
				return -1;
			}
			pr->next = p->next;
			free(p);
		}
	}
	// 起始城市没有邻接城市 无需删除边 直接返回
	else
	{
		printf("No find Arc of %s and %s!\n", srccity, destcity);
		return -1;
	}
	if (flag == 1)
	{	
		flag = -1;
		return 1;
	}
	flag = 1;
	DeleteArc(g, destcity, srccity);
}

// 删除图中的一个顶点 包括删除所有的它与邻接顶点的边
int
DeleteVex(PGraph g, char* city)
{
	if (g == NULL || g->vex == NULL)
		return -1;
	// 找到要删除的根节点
	int index;
	for (index = 0; index < g->num; index++)
	{
		if (!strcmp(g->vex[index].city, city))
			break;
	}
	if (index == g->num)
	{
		printf("No find %s\n", city);
		return -1;
	}
	while (g->vex[index].arc)
	{
		PArcNode p = g->vex[index].arc;
		char destcity[12];
		strcpy(destcity, p->city);
		DeleteArc(g, city, destcity);
	}
	for (int i = index; i < g->num - 1; i++)
	{
		g->vex[i] = g->vex[i + 1];
	}
	g->num--;
	return 1;
}

void
DisplayTrafficMap(PGraph g)
{
	if (g == NULL || g->vex == NULL)
		return;
	for (int i = 0; i < g->num; i++)
	{
		printf("%s ", g->vex[i].city);
		if (g->vex[i].arc)
		{
			PArcNode p = g->vex[i].arc;
			while (p)
			{
				printf("->%s ", p->city);
				p = p->next;
			}
		}
		printf("\n");
	}
}

void
InitTrafficMap(PGraph g)
{
	if (g == NULL || g->vex == NULL)
		return;

	// 添加所有的城市
	InsertVex(g, "beijing");
	InsertVex(g, "tianjin");
	InsertVex(g, "xuzhou");
	InsertVex(g, "zhengzhou");
	InsertVex(g, "haerbin");
	InsertVex(g, "changchun");
	InsertVex(g, "shenyang");
	InsertVex(g, "dalian"); 
	InsertVex(g, "shanghai");
	InsertVex(g, "nanchang");
	InsertVex(g, "fuzhou");
	InsertVex(g, "zhuzhou");
	InsertVex(g, "wuhan");
	InsertVex(g, "guangzhou");
	InsertVex(g, "shenzhen");
	InsertVex(g, "liuzhou");
	InsertVex(g, "nanning");
	InsertVex(g, "guiyang"); 
	InsertVex(g, "kunming");
	InsertVex(g, "chengdu");
	InsertVex(g, "xian");
	InsertVex(g, "lanzhou");
	InsertVex(g, "xining");
	InsertVex(g, "huhehaote");
	InsertVex(g, "wulumuqi");

	// 添加所有边
	InsertArc(g, "haerbin","changchun",242);
	InsertArc(g, "changchun", "shenyang", 305);
	InsertArc(g, "shenyang", "dalian",397);
	InsertArc(g, "shenyang", "tianjin",704);
	InsertArc(g, "beijing", "tianjin", 137);
	InsertArc(g, "beijing", "zhengzhou", 695);
	InsertArc(g, "zhengzhou", "xuzhou", 349);
	InsertArc(g, "xuzhou", "tianjin", 674);
	InsertArc(g, "xuzhou", "shanghai", 651);
	InsertArc(g, "shanghai", "nanchang",825);
	InsertArc(g, "nanchang", "fuzhou",622);
	InsertArc(g, "nanchang", "zhuzhou",367);
	InsertArc(g, "zhuzhou", "guangzhou",675);
	InsertArc(g, "guangzhou", "shenzhen",140);
	InsertArc(g, "zhuzhou", "wuhan",409);
	InsertArc(g, "wuhan", "zhengzhou",534);
	InsertArc(g, "zhuzhou", "guiyang",902);
	InsertArc(g, "zhuzhou", "liuzhou",672);
	InsertArc(g, "liuzhou", "nanning",255);
	InsertArc(g, "guiyang", "liuzhou",607);
	InsertArc(g, "guiyang", "kunming",639);
	InsertArc(g, "guiyang", "chengdu",967);
	InsertArc(g, "kunming", "chengdu",1100);
	InsertArc(g, "chengdu", "xian",842);
	InsertArc(g, "xian", "zhengzhou",511);
	InsertArc(g, "xian", "lanzhou",676);
	InsertArc(g, "lanzhou", "xining",216);
	InsertArc(g, "lanzhou", "huhehaote",1145);
	InsertArc(g, "huhehaote", "beijing",668);
	InsertArc(g, "lanzhou", "wulumuqi",1892);

}

void
Floyd(PGraph g)
{
	if (g == NULL || g->vex == NULL)
		return;
	// 邻接表的最短路径需转换成邻接矩阵的最短路径
	// 先得到各顶点之间的距离矩阵
	int j;
	// 把所有邻接顶点和它们之间的距离初始化
	for (int i = 0; i < g->num; i++)
	{
		if (g->vex[i].arc)
		{
			PArcNode p = g->vex[i].arc;
			while (p)
			{
				char city[12];
				strcpy(city, p->city);
				for (j = 0; j < g->num; j++)
				{
					if (!strcmp(g->vex[j].city, city))
						break;
				}
				dist[i][j] = p->dist;
				dist[j][i] = p->dist;
				p = p->next;
			}
		}
	}
	for (int i = 0; i < g->num; i++)
	{
		for (int k = 0; k < g->num; k++)
		{
			if (i != k && !dist[i][k])
			{
				dist[i][k] = NaN;
			}
			if (dist[i][k] != NaN)
			{
				path[i][k] = k;
			}
			else
			{
				path[i][k] = i;
			}
		}
	}
	
	// Floyd算法核心部分
	for (int k = 0; k < g->num; k++)
	{
		// i 起点
		for (int i = 0; i < g->num; i++)
		{
			// j 终点
			for (int j = 0; j < g->num; j++)
			{
				if (dist[i][j] > (dist[i][k] + dist[k][j]))
				{
					dist[i][j] = dist[i][k] + dist[k][j];
					path[i][j] = path[i][k];
				}
			}
		}
	}
	
}


void
ShortestPath(PGraph g, char* srccity, char* destcity)
{
	if (g == NULL || g->vex == NULL)
		return;
	int src, dest;
	for (src = 0; src < g->num; src++)
	{
		if (!strcmp(g->vex[src].city, srccity))
			break;
	}
	for (dest = 0; dest < g->num; dest++)
	{
		if (!strcmp(g->vex[dest].city, destcity))
			break;
	}
	if (src == g->num)
	{
		printf("No find %s", srccity);
		return;
	}
	if (dest == g->num)
	{
		printf("No find %s", destcity);
		return;
	}

	// 打印最短路径
	printf("%s -> %s : %d \n", g->vex[src].city, g->vex[dest].city, dist[src][dest]);
	int k = path[src][dest];
	printf("path: %s", g->vex[src].city);
	while (k != dest)
	{
			printf("-> %s", g->vex[k].city);
			k = path[k][dest];
	}
	printf("-> %s\n", g->vex[dest].city);
}
