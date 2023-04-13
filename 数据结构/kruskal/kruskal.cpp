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
typedef struct EdgeData {
	char start, end;		//�ߵ������յ�
	int weight;				//�ߵ�Ȩ��
}Edata;

//����ch��matrix�����е�λ��
static int get_position(Graph G, char ch) {
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
		printf("v(%d):", i);
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
		if (p1 == -1 || p2 == -1) {
			printf("�߲�����Ҫ��\n");
			free(graph);
			return NULL;
		}
		graph->matrix[p1][p2] = weight;
		graph->matrix[p2][p1] = weight;
	}
	return graph;
}

//�������еı�
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

//���ߵ�Ȩֵ�Ա߽�������
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

//��ȡ����������С�������е����
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
	int index = 0;          // rets���������
	int vends[MAX];     // ���ڱ���"������С������"��ÿ�������ڸ���С���е���㡣
	Edata rets[MAX];        // ������飬����kruskal��С�������ı�
	Edata* edges;           // ͼ��Ӧ�����б�
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
	//��ӡ"kruskal��С������"����Ϣ
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