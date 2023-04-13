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
typedef struct EdgeData {
	char start, end;		//边的起点和终点
	int weight;				//边的权重
}Edata;

//返回ch在matrix矩阵中的位置
static int get_position(Graph G, char ch) {
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
		printf("v(%d):", i);
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
		if (p1 == -1 || p2 == -1) {
			printf("边不符合要求！\n");
			free(graph);
			return NULL;
		}
		graph->matrix[p1][p2] = weight;
		graph->matrix[p2][p1] = weight;
	}
	return graph;
}

//返回所有的边
Edata* get_edges(Graph graph) {
	int i, j, index=0;
	Edata* edges = (Edata*)malloc(graph.edgnum * sizeof(Edata));
	for (i = 0; i < graph.vexnum; i++) {
		for (j = i + 1; j < graph.vexnum; j++) {
			if (graph.matrix[i][j] != INF) {
				edges[index].start = graph.vexs[i];
				edges[index].end = graph.vexs[j];
				edges[index].weight = graph.matrix[i][j];
				index++;
			}
		}
	}
	return edges;
}

//按边的权值对边进行排序
void sort_edges(Edata* edges, int n) {
	for (int i = 0; i < n - 1; i++) {
		for (int j = 0; j < n - 1 - i; j++) {
			if (edges[j].weight > edges[j + 1].weight) {
				Edata temp = edges[j];
				edges[j] = edges[j + 1];
				edges[j + 1] = temp;
			}

		}
	}
}

//获取边在已有最小生成树中的起点
int get_end(int vends[MAX], int i)
{
	while (vends[i]!=-1)
		i = vends[i];
	return i;
}

//kruskal
void kruskal(Graph graph) {
	int i, m, n, p1, p2;
	int tot = 0;;
	int index = 0;          // rets数组的索引
	int vends[MAX];     // 用于保存"已有最小生成树"中每个顶点在该最小树中的起点。
	Edata rets[MAX];        // 结果数组，保存kruskal最小生成树的边
	Edata* edges;           // 图对应的所有边
	for (int k = 0; k < MAX; k++)
		vends[k] = -1;
	edges = get_edges(graph);
	sort_edges(edges, graph.edgnum);

	for (i = 0; i < graph.edgnum; i++) {
		p1 = get_position(graph, edges[i].start);
		p2 = get_position(graph, edges[i].end);
		m = get_end(vends, p1);
		n = get_end(vends, p2);
		if (m != n) {
			vends[n] = m;
			rets[index++] = edges[i];
		}
	}
	//free(edges);
	//打印"kruskal最小生成树"的信息
	for (i = 0; i < index; i++)
		tot += rets[i].weight;
	printf("Kruskal=%d: ", tot);
	for (i = 0; i < index; i++)
		printf("(%c,%c) ", rets[i].start, rets[i].end);
	printf("\n");
}

int main(void) {
	Graph* graph = CreatGraph();
	kruskal(*graph);
}