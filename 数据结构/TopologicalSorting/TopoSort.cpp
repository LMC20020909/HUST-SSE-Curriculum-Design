#include <stdio.h>
#include <stdlib.h>
#define MaxVertexNum 100
typedef char VertexType;
typedef int ArcType;
typedef struct ArcNode {		//�����
	int adjvex;		//�ö����Ӧ���±�
	struct ArcNode* nextarc;		//ָ����һ������ָ��
}ArcNode;
typedef struct VertexNode {		//����
	VertexType data;		//������Ϣ
	int indegree=0;		//���
	int flag = 0;		//�Ƿ񱻷��ʹ�
	ArcNode* firstarc;		//ָ���һ������ָ��
}VertexNode,AdjList[MaxVertexNum];
typedef struct {
	AdjList vertex;		//��������
	int vexnum, arcnum;		//ͼ�ĵ�ǰ�������ͻ���
}ALGraph;

//��������ͼ���ڽӱ�
void CreateALGraph(ALGraph *G) {
	int i, j, k;
	ArcNode* e;
	printf("�����붥�����ͻ�����");
	scanf("%d%d", &G->vexnum, &G->arcnum);
	
	for (i = 1; i <= G->vexnum; i++) {
		printf("�����붥����Ϣ��");
		getchar();
		scanf("%c", & G->vertex[i].data);
		G->vertex[i].firstarc = NULL;
	}
	for (k = 0; k < G->arcnum; k++) {
		printf("�����뻡<vi,vj>�Ļ�β�ͻ�ͷ��ţ�");
		scanf("%d%d", &i, &j);
		G->vertex[j].indegree++;		//��ͷ�������ȼ�1
		e = (ArcNode*)malloc(sizeof(ArcNode));
		e->adjvex = j;
		e->nextarc = G->vertex[i].firstarc;		//���Ի�β����Ϊͷ�ڵ���ڽӱ�����ӻ�ͷ����
		G->vertex[i].firstarc = e;
	}
}

//���ͼ
void PrintGraph(ALGraph G) {
	printf("�������Ϊ%d��\n", G.vexnum);
	for (int i = 1; i <= G.vexnum; i++)
		printf("%c  ", G.vertex[i].data);
	printf("\n������Ϊ%d��\n", G.arcnum);
	for (int j = 1; j <= G.vexnum; j++) {
		if (G.vertex[j].firstarc) {
			ArcNode* p = G.vertex[j].firstarc;
			while (p) {
				printf("%c->%c  ", G.vertex[j].data, G.vertex[p->adjvex].data);
				p = p->nextarc;
			}
		}
	}
	printf("\n");
}

//������ͼG��������
void TopoSort(ALGraph G) {
	int count = 1;
	int vt[MaxVertexNum];		//���ÿ�����Ϊ0�Ķ������
	for(int m=1;m<=G.vexnum;m++) {
		int i;
		for (i = 1; i <= G.vexnum; i++) {
				if (!G.vertex[i].indegree && !G.vertex[i].flag) {		//�ö�������Ϊ0��δ�����ʹ�
					vt[count] = i;
					count++;
					break;
				}
			}
		if (i <= G.vexnum) {
			ArcNode* p = G.vertex[i].firstarc;
			if (!G.vertex[i].flag) {
				while (p) {
					G.vertex[p->adjvex].indegree--;		//��ͷ�������ȼ�1
					p = p->nextarc;		//ɾ���Դ˶���Ϊ��β�Ļ�
				}
				G.vertex[i].flag = 1;	//���˶����־Ϊ�ѱ����ʣ��´ν����ٷ���
			}
		}
	}
	if (count <= G.vexnum)printf("������ͼ���ڻ�·������\n");
	else {
		for (int k = 1; k < count; k++)
			printf("%c  ", G.vertex[vt[k]].data);		//�����������Ľ��
	}
}
int main(void) {
	ALGraph G;
	CreateALGraph(&G);
	PrintGraph(G);
	TopoSort(G);
	return 0;
}