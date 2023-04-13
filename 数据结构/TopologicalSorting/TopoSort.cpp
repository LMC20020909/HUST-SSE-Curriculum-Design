#include <stdio.h>
#include <stdlib.h>
#define MaxVertexNum 100
typedef char VertexType;
typedef int ArcType;
typedef struct ArcNode {		//弧结点
	int adjvex;		//该顶点对应的下标
	struct ArcNode* nextarc;		//指向下一条弧的指针
}ArcNode;
typedef struct VertexNode {		//顶点
	VertexType data;		//顶点信息
	int indegree=0;		//入度
	int flag = 0;		//是否被访问过
	ArcNode* firstarc;		//指向第一条弧的指针
}VertexNode,AdjList[MaxVertexNum];
typedef struct {
	AdjList vertex;		//顶点数组
	int vexnum, arcnum;		//图的当前顶点数和弧数
}ALGraph;

//建立有向图的邻接表
void CreateALGraph(ALGraph *G) {
	int i, j, k;
	ArcNode* e;
	printf("请输入顶点数和弧数：");
	scanf("%d%d", &G->vexnum, &G->arcnum);
	
	for (i = 1; i <= G->vexnum; i++) {
		printf("请输入顶点信息：");
		getchar();
		scanf("%c", & G->vertex[i].data);
		G->vertex[i].firstarc = NULL;
	}
	for (k = 0; k < G->arcnum; k++) {
		printf("请输入弧<vi,vj>的弧尾和弧头序号：");
		scanf("%d%d", &i, &j);
		G->vertex[j].indegree++;		//弧头顶点的入度加1
		e = (ArcNode*)malloc(sizeof(ArcNode));
		e->adjvex = j;
		e->nextarc = G->vertex[i].firstarc;		//向以弧尾顶点为头节点的邻接表中添加弧头顶点
		G->vertex[i].firstarc = e;
	}
}

//输出图
void PrintGraph(ALGraph G) {
	printf("顶点个数为%d个\n", G.vexnum);
	for (int i = 1; i <= G.vexnum; i++)
		printf("%c  ", G.vertex[i].data);
	printf("\n弧条数为%d条\n", G.arcnum);
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

//对有向图G拓扑排序
void TopoSort(ALGraph G) {
	int count = 1;
	int vt[MaxVertexNum];		//存放每次入度为0的顶点序号
	for(int m=1;m<=G.vexnum;m++) {
		int i;
		for (i = 1; i <= G.vexnum; i++) {
				if (!G.vertex[i].indegree && !G.vertex[i].flag) {		//该顶点的入度为0且未被访问过
					vt[count] = i;
					count++;
					break;
				}
			}
		if (i <= G.vexnum) {
			ArcNode* p = G.vertex[i].firstarc;
			if (!G.vertex[i].flag) {
				while (p) {
					G.vertex[p->adjvex].indegree--;		//弧头顶点的入度减1
					p = p->nextarc;		//删除以此顶点为弧尾的弧
				}
				G.vertex[i].flag = 1;	//将此顶点标志为已被访问，下次将不再访问
			}
		}
	}
	if (count <= G.vexnum)printf("该有向图存在回路，错误\n");
	else {
		for (int k = 1; k < count; k++)
			printf("%c  ", G.vertex[vt[k]].data);		//输出拓扑排序的结果
	}
}
int main(void) {
	ALGraph G;
	CreateALGraph(&G);
	PrintGraph(G);
	TopoSort(G);
	return 0;
}