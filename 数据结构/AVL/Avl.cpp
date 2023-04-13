#include<stdio.h>
#include<stdlib.h>
typedef struct node {
	int data;
	int bf;		//balance flag ƽ�����ӵ���д
	struct node* lchild, * rchild;
}BitNode, * BiTree;

//֮����Ҫ��** ����Ϊ�������������Ҫ����ָ��ָ�����ݵ���Ҫ��ַ����
//�ҵ���������pΪ���Ķ���������   ���� ��������ȴ���������
//�����󣺸��ڵ�Ϊp�ڵ�����ӣ�ͬʱ��p�ڵ����ӵ��Һ��ӽ���p�ڵ������
//Ȼ��p�ڵ���Ϊ�¸����Һ���
void rightRotate(BiTree* p) {
	BiTree L = (*p)->lchild;
	(*p)->lchild = L->rchild;
	L->rchild = (*p);
	*p = L;
}

//�������ͬ��ֻ�ǽ���pΪ���Ķ�������������������������ȴ���������
//�����ã����ڵ�Ϊp���Һ��ӣ�ͬʱ��p�ڵ���Һ��ӵ����Ӽ���p�ڵ���Һ���
//Ȼ��p�ڵ���Ϊ�µĸ��ڵ������

void leftRotate(BiTree* p) {
	BiTree R = (*p)->rchild;
	(*p)->rchild = R->lchild;
	R->lchild = (*p);
	*p = R;
}

//����LL ��LR �������͵���״  LL����תֻ��Ҫ����һ�� LR���ַ��������
//����LR�͵Ĵ����������ȸ��ݸ��ڵ����������תһ�α�ΪLL��Ȼ��������ת
void LL_LRBalance(BiTree* p) {
	BiTree L = (*p)->lchild;
	BiTree R;
	switch (L->bf) {
	case 1://��Ϊ1,���ʾ�½ڵ�������ӵ��������ϣ�ΪLL��
		(*p)->bf = L->bf = 0;
		rightRotate(p);
		break;
	case -1://��Ϊ-1,���ʾ���뵽���ӵ��������ϣ�ΪLR��
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

//�������pΪ���ڵ�ָ�� keyΪ������Ĺؼ��� chain��ʾ����ڵ���Ƿ��������
//��ʼΪ0 
int insertAVL(BiTree* p, int key, int* chain) {
	//��ʾδ�������ҵ�key��ֱ�������µĽڵ㣬���ڴ洢key
	if ((*p) == NULL) {
		(*p) = (BitNode*)malloc(sizeof(BitNode));
		(*p)->bf = 0;
		(*p)->lchild = (*p)->rchild = NULL;
		(*p)->data = key;
		*chain = 1;
	}
	else {
		//��ʾ��������ͬ�Ĺؼ��֣���ʾ����ʧ��
		if (key == (*p)->data) {
			*chain = 0;
			printf("����ͬ�ؼ��֣�����ʧ�ܣ�\n");
			return 0;
		}
		//��ʾ����ֵС�ڵ�ǰ�Ľ��key����ݹ��ڵ�ǰ��������������
		if (key < (*p)->data) {
			//������벻�ɹ�
			if (!insertAVL(&(*p)->lchild, key, chain)) return 0;

			if (*chain) {		//�˴��ڵݹ�����˳�ʱ���ã���ʾ�½ڵ���p����������
				switch ((*p)->bf) {

					//if p��ƽ������Ϊ0 ��ô�������������룬����Ϊ1
					//���ĸ߶����ӣ������ƽ�����ӵı仯  ���õ���
				case 0:(*p)->bf = 1; *chain = 1; break;

					//if p��ƽ������Ϊ1,��ô�������������룬ƽ�ⱻ�ƻ���
					//��Ҫ���е���������֮�󣬲��ᵼ�����ĸ߶����ӣ������

				case 1: LL_LRBalance(p); *chain = 0;  break;

					//if p��ƽ������Ϊ-1����ô�������Ӳ���ڵ㣬��bf��Ϊ0,
					//����ƽ��û���ƻ�����Ӧ����
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

//�������
void InOrder(BiTree t) {
	if (t != NULL) {
		InOrder(t->lchild);
		printf("%d  ", t->data);
		InOrder(t->rchild);
	}
}

//ǰ�����
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
	printf("�����������������ݣ�");
	while ((scanf("%d", &test)) != EOF) {
		count++;
		insertAVL(&T, test, &chain);
		if (chain)height++;
		printf("��������Ľ����");
		InOrder(T);
		printf("\n����Ϊ%d", height);
		printf("\n�����������������ݣ�");
	}
	printf("ǰ������Ľ����");
	PreOrder(T);
	return 0;
}
