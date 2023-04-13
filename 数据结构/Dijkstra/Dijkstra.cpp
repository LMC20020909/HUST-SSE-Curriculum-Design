#include <stdio.h>
#include <stdlib.h>

#define MAX   100
#define INF   (((unsigned int)(-1)) >> 1)

//邻接矩阵定义
typedef struct graph {
	char vexs[MAX];			//顶点集合
	int vexnum, edgnum;		//定点数和边数
	int matrix[MAX][MAX];   //邻接矩阵
}Graph, * PGraph;

//边定义
typedef struct EdgeData{
	char start, end;		//边的起点和终点
	int weight;				//边的权重
}Edata;

//返回ch在matrix矩阵中的位置
static int get_position(Graph G, char ch){
	int i;
	for (i = 0; i < G.vexnum; i++)
		if (G.vexs[i] == ch)
			return i;
	return -1;
}

//创建图
Graph* CreatGraph() {
	char c1, c2;
	int vex, edg;
	int i, j, weight, p1, p2;
	Graph* graph;
	graph = (Graph*)malloc(sizeof(Graph));
	//输入顶点数和边数
	printf("请输入顶点数和边数：");
	scanf("%d%d", &vex, &edg);
	getchar();
	if (vex < 1 || edg < 1 || (edg > (vex * (vex - 1)))) {
		printf("输入不符合要求！\n");
		return NULL;
	}
	graph->vexnum = vex;
	graph->edgnum = edg;
	//输入顶点
	printf("请输入顶点\n");
	for (i = 0; i < graph->vexnum; i++) {
		printf("v(%d):",i);
		scanf("%c", &graph->vexs[i]);
		getchar();
	}
	//初始化边的权值
	for (i = 0; i < graph->vexnum; i++) {
		for (j = 0; j < graph->vexnum; j++) {
			if (i == j)
				graph->matrix[i][j] = 0;
			else
				graph->matrix[i][j] = INF;
		}
	}
	//输入边的起点、终点和权值
	printf("请输入边的起点、终点和权值\n");
	for (i = 0; i < graph->edgnum; i++) {
		printf("e(%d):", i);
		scanf("%c%c", &c1, &c2);
		getchar();
		printf("weight:");
		scanf("%d", &weight);
		getchar();
		p1 = get_position(*graph, c1);
		p2 = get_position(*graph, c2);
		if (p1 == -1 || p2 == -1){
			printf("边不符合要求！\n");
			free(graph);
			return NULL;
		}
		graph->matrix[p1][p2] = weight;
	}
	return graph;

}

/*
	Dijkstra
	v0 -- 起始顶点。即计算"顶点v0"到其它顶点的最短路径。
    pre -- 前驱顶点数组,即pre[i]的值是"顶点v0"到"顶点i"的最短路径所经历的全部顶点中，位于"顶点i"之前的那个顶点。
    dijk -- 长度数组,即dijk[i]是"顶点v0"到"顶点i"的最短路径的长度。
*/
void Dijkstra(Graph graph,char v0,int pre[],int dijk[]) {
	int i, j, k= get_position(graph, v0), min, tmp, flag[MAX];		//flag[i]==1表示v0到vi的最短路径已成功获取
	int p0 = get_position(graph, v0);
	//初始化
	for (i = 0; i < graph.vexnum; i++) {
		flag[i] = 0;
		pre[i] = 0;
		dijk[i] = graph.matrix[p0][i];
	}
	flag[p0] = 1;
	dijk[p0] = 0;

	for (i = 0; i < graph.vexnum; i++) {
		min = INF;
		for (j = 0; j < graph.vexnum; j++) {
			if (!flag[j] && dijk[j] < min) {
				min = dijk[j];
				k = j;
			}
		}
		flag[k] = 1;
		for (j = 0; j < graph.vexnum; j++) {
			tmp = graph.matrix[k][j] == INF ? INF : (min + graph.matrix[k][j]);
			if (!flag[j] && tmp < dijk[j]) {
				dijk[j] = tmp;
				pre[j] = k;
			}
		}
	}

	for (j = 0; j < graph.vexnum; j++) {
		if (dijk[j] != INF)
			printf("shortest(%c,%c)=%d\n", v0, graph.vexs[j], dijk[j]);
		else printf("%c到%c不可达\n", v0, graph.vexs[j]);
	}
}

int main(void) {
	if (Graph* graph = CreatGraph()) {
		char v0;
		int pre[MAX] = { 0 }, dijk[MAX] = { 0 };
		printf("请输入所求最短路径的原点：");
		scanf("%c", &v0);
		getchar();
		Dijkstra(*graph, v0, pre, dijk);
	}
	return 0;
}