#include <stdio.h>
#include <stdlib.h>

#define MAX   100
#define INF   (((unsigned int)(-1)) >> 1)

//�ڽӾ�����
typedef struct graph {
	char vexs[MAX];			//���㼯��
	int vexnum, edgnum;		//�������ͱ���
	int matrix[MAX][MAX];   //�ڽӾ���
}Graph, * PGraph;

//�߶���
typedef struct EdgeData{
	char start, end;		//�ߵ������յ�
	int weight;				//�ߵ�Ȩ��
}Edata;

//����ch��matrix�����е�λ��
static int get_position(Graph G, char ch){
	int i;
	for (i = 0; i < G.vexnum; i++)
		if (G.vexs[i] == ch)
			return i;
	return -1;
}

//����ͼ
Graph* CreatGraph() {
	char c1, c2;
	int vex, edg;
	int i, j, weight, p1, p2;
	Graph* graph;
	graph = (Graph*)malloc(sizeof(Graph));
	//���붥�����ͱ���
	printf("�����붥�����ͱ�����");
	scanf("%d%d", &vex, &edg);
	getchar();
	if (vex < 1 || edg < 1 || (edg > (vex * (vex - 1)))) {
		printf("���벻����Ҫ��\n");
		return NULL;
	}
	graph->vexnum = vex;
	graph->edgnum = edg;
	//���붥��
	printf("�����붥��\n");
	for (i = 0; i < graph->vexnum; i++) {
		printf("v(%d):",i);
		scanf("%c", &graph->vexs[i]);
		getchar();
	}
	//��ʼ���ߵ�Ȩֵ
	for (i = 0; i < graph->vexnum; i++) {
		for (j = 0; j < graph->vexnum; j++) {
			if (i == j)
				graph->matrix[i][j] = 0;
			else
				graph->matrix[i][j] = INF;
		}
	}
	//����ߵ���㡢�յ��Ȩֵ
	printf("������ߵ���㡢�յ��Ȩֵ\n");
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
			printf("�߲�����Ҫ��\n");
			free(graph);
			return NULL;
		}
		graph->matrix[p1][p2] = weight;
	}
	return graph;

}

/*
	Dijkstra
	v0 -- ��ʼ���㡣������"����v0"��������������·����
    pre -- ǰ����������,��pre[i]��ֵ��"����v0"��"����i"�����·����������ȫ�������У�λ��"����i"֮ǰ���Ǹ����㡣
    dijk -- ��������,��dijk[i]��"����v0"��"����i"�����·���ĳ��ȡ�
*/
void Dijkstra(Graph graph,char v0,int pre[],int dijk[]) {
	int i, j, k= get_position(graph, v0), min, tmp, flag[MAX];		//flag[i]==1��ʾv0��vi�����·���ѳɹ���ȡ
	int p0 = get_position(graph, v0);
	//��ʼ��
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
		else printf("%c��%c���ɴ�\n", v0, graph.vexs[j]);
	}
}

int main(void) {
	if (Graph* graph = CreatGraph()) {
		char v0;
		int pre[MAX] = { 0 }, dijk[MAX] = { 0 };
		printf("�������������·����ԭ�㣺");
		scanf("%c", &v0);
		getchar();
		Dijkstra(*graph, v0, pre, dijk);
	}
	return 0;
}