#include<stdio.h>
#include<stdlib.h>
typedef struct node {
	int data;
	int bf;		//balance flag 平衡因子的缩写
	struct node* lchild, * rchild;
}BitNode, * BiTree;

//之所以要用** 是因为参数传递情况下要更改指针指向内容的需要地址传递
//右调整：对以p为根的二叉树右旋   该树 左子树深度大于右子树
//调整后：根节点为p节点的左孩子，同时将p节点左孩子的右孩子接在p节点的左孩子
//然后将p节点作为新根的右孩子
void rightRotate(BiTree* p) {
	BiTree L = (*p)->lchild;
	(*p)->lchild = L->rchild;
	L->rchild = (*p);
	*p = L;
}

//左调整：同理，只是将以p为根的二叉树左旋，该树的右子树深度大于左子树
//调整好：根节点为p的右孩子，同时将p节点的右孩子的左孩子加在p节点的右孩子
//然后将p节点作为新的根节点的左孩子

void leftRotate(BiTree* p) {
	BiTree R = (*p)->rchild;
	(*p)->rchild = R->lchild;
	R->lchild = (*p);
	*p = R;
}

//处理LL 和LR 两种类型的旋状  LL型旋转只需要右旋一次 LR型又分三种情况
//但是LR型的处理方法都是先根据根节点的左孩子左旋转一次变为LL型然后再又旋转
void LL_LRBalance(BiTree* p) {
	BiTree L = (*p)->lchild;
	BiTree R;
	switch (L->bf) {
	case 1://若为1,则表示新节点插在左孩子的左子树上，为LL型
		(*p)->bf = L->bf = 0;
		rightRotate(p);
		break;
	case -1://若为-1,则表示插入到左孩子的右子树上，为LR型
		R = L->rchild;
		switch (R->bf) {
		case 0:
			(*p)->bf = L->bf = 0; break;
		case 1:
			(*p)->bf = -1; R->bf = L->bf = 0; break;
		case -1:
			(*p)->bf = R->bf = 0; L->bf = 1; break;

		}
		leftRotate(&((*p)->lchild));
		rightRotate(p);
		break;
	}
}


void RR_RLBalance(BiTree* p) {
	BiTree R = (*p)->rchild;
	BiTree L;
	switch (R->bf) {
	case -1:
		(*p)->bf = R->bf = 0;
		leftRotate(p);
		break;
	case 1:
		L = R->lchild;
		switch (L->bf) {
		case 0: (*p)->bf = R->bf = 0; break;
		case 1: (*p)->bf = L->bf = 0; R->bf = -1; break;
		case -1: (*p)->bf = 1; L->bf = R->bf = 0; break;
		}
		rightRotate(&(*p)->rchild);
		leftRotate(p);
		break;
	}
}

//输入参数p为根节点指针 key为被插入的关键字 chain表示插入节点后是否引起调整
//初始为0 
int insertAVL(BiTree* p, int key, int* chain) {
	//表示未在树中找到key，直接生成新的节点，用于存储key
	if ((*p) == NULL) {
		(*p) = (BitNode*)malloc(sizeof(BitNode));
		(*p)->bf = 0;
		(*p)->lchild = (*p)->rchild = NULL;
		(*p)->data = key;
		*chain = 1;
	}
	else {
		//表示树中有相同的关键字，表示插入失败
		if (key == (*p)->data) {
			*chain = 0;
			printf("有相同关键字，插入失败！\n");
			return 0;
		}
		//表示插入值小于当前的结点key，则递归在当前结点的左子树插入
		if (key < (*p)->data) {
			//如果插入不成功
			if (!insertAVL(&(*p)->lchild, key, chain)) return 0;

			if (*chain) {		//此处在递归调用退出时调用，表示新节点在p左子树插入
				switch ((*p)->bf) {

					//if p的平衡因子为0 那么在其左子树插入，将变为1
					//树的高度增加，会产生平衡引子的变化  不用调整
				case 0:(*p)->bf = 1; *chain = 1; break;

					//if p的平衡因子为1,那么在其左子树插入，平衡被破坏，
					//需要进行调整，调整之后，不会导致树的高度增加，则结束

				case 1: LL_LRBalance(p); *chain = 0;  break;

					//if p的平衡因子为-1，那么在其左孩子插入节点，则bf变为0,
					//树的平衡没有破坏，反应结束
				case -1:(*p)->bf = 0; *chain = 0;  break;
				}
			}
		}
		else
		{
			if (!insertAVL(&(*p)->rchild, key, chain)) return 0;
			if (*chain) {
				{
					switch ((*p)->bf) {
					case 0: (*p)->bf = -1; *chain = 1; break;
					case 1: (*p)->bf = 0; *chain = 0; break;
					case -1:RR_RLBalance(p); *chain = 0; break;
					}
				}
			}
		}
	}
	return 1;
}

//中序遍历
void InOrder(BiTree t) {
	if (t != NULL) {
		InOrder(t->lchild);
		printf("%d  ", t->data);
		InOrder(t->rchild);
	}
}

//前序遍历
void PreOrder(BiTree t) {
	if (t != NULL) {
		printf("%d  ", t->data);
		PreOrder(t->lchild);
		PreOrder(t->rchild);
	}
}
int main(void) {
	BiTree T = NULL;
	int chain, test, count = 0, height = 0;
	printf("请输入你想插入的数据：");
	while ((scanf("%d", &test)) != EOF) {
		count++;
		insertAVL(&T, test, &chain);
		if (chain)height++;
		printf("中序遍历的结果：");
		InOrder(T);
		printf("\n树高为%d", height);
		printf("\n请输入你想插入的数据：");
	}
	printf("前序遍历的结果：");
	PreOrder(T);
	return 0;
}
