#include "graph.h"

int main()
{
	PGraph g = InitGraph();
	InitTrafficMap(g);
	DisplayTrafficMap(g);
	printf("\n");
	Floyd(g);
	ShortestPath(g, "zhengzhou", "huhehaote");
	Destory(g);
	return 0;
}