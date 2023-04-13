#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define w			  3		//�ڴ湤���������ɵļ�¼����
#define MAXKEY        (~(0x1 << 31)) //���ؼ��ֱ�־
#define RUNEND_SYMBOL (~(0x1 << 31)) //�鲢�ν�����־
#define N			  10	//�����ļ���Ԥ���¼����
#define MINKEY	      -(~(0x1 << 31))//��С�ؼ��ֱ�־
typedef int KeyType;		//�ؼ�������
typedef struct {
	KeyType key;
}RcdType;					//��¼����
typedef int LoserTree[w];  //����������ȫ�������Ҳ���Ҷ�ӣ��ɲ���˳��洢�ṹ
typedef struct {
	RcdType rec;		//��¼
	KeyType key;		//�Ӽ�¼�г�ȡ�Ĺؼ���
	int rnum;			//�����鲢�εĶκ�
}RcdNode,WorkArea[w];	//�ڴ湤����������Ϊw
int t0 = 0, t1 = 0, t2 = 0, m = 0;//��־����

/*���롢������м��ݴ��ļ�ָ��Ķ���
  f0��f1��f2Ϊ�м��ݴ��ļ�����ų�ʼ�鲢��
  ffΪ��������ļ�
*/
FILE* f0 = fopen("f0", "wb");
FILE* f1 = fopen("f1", "wb");
FILE* f2 = fopen("f2", "wb");
FILE* f3 = fopen("f0", "rb");
FILE* f4 = fopen("f1", "rb");
FILE* f5 = fopen("f2", "rb");
FILE* ff = fopen("ff", "wb");

//��wa[q]�𵽰������ĸ��Ƚ�ѡ��MINIMAX��¼������qָ�������ڵĹ鲢��
void Select_MiniMax(LoserTree& ls, WorkArea wa, int q) {
	int p, s, t;
	for (t = (w + q) / 2, p = ls[t]; t > 0; t /= 2, p = ls[t]) {
		//�κ�С�߻�κ���ͬ�ҹؼ��ָ�С��Ϊʤ��
		if (wa[p].rnum < wa[q].rnum || wa[p].rnum == wa[q].rnum && wa[p].key < wa[q].key) {
			s = q;
			q = ls[t];	//qָ���µ�ʤ��
			ls[t] = s;
		}
	}
	ls[0] = q;  //�ھ�
}

//�ش�Ҷ�ӽ��wa[q]�������ls[0]��·������������
void Adjust(LoserTree& ls, WorkArea wa, int q) {
	int t = (q + w) / 2;						//ls[t]��wa[q]��˫�׽��
	while (t > 0) {
		if (wa[q].key > wa[ls[t]].key) {		
			int swap = q;
			q = ls[t];							//qָʾ�µ�ʤ��
			ls[t] = swap;
		}
		t = t / 2;
	}
	ls[0] = q;
}
int a0[N], a1[N], a2[N], count0 = 0, count1 = 0, count2 = 0;

/*��֪wa[0]��wa[w-1]Ϊ��ȫ������ls��Ҷ�ӽ�����w���ؼ��֣�
  �ش�Ҷ�ӵ�����w��·����ls����Ϊ������
*/
void CreateLoserTree(LoserTree& ls, WorkArea& wa) {
	int i;
	for (i = 0; i < w; i++) {
		ls[i] = w;				//����ls�а��ߵĳ�ֵ
	}
	for (i = w - 1; i >= 0; i--) {
		Adjust(ls, wa, i);		//���δ�wa[w-1],wa[w-2],...,wa[0]������������
	}
}

/*�Ӵ���ų�ʼ�鲢���е������ļ�f0, f1, f2�ж�ȡ��һ����¼�Ĺؼ��֣�
  �������һ���鲢�ν������ȡ���ؼ���MAXKEY*/
void input(LoserTree& ls, WorkArea& wa, int i) {
	
	switch (i) {
	case 0:
		if (t0 < count0) {
			fread(&wa[i].key, sizeof(KeyType), 1, f3);
			t0++;
		}
		else wa[i].key = MAXKEY;
		break;
	case 1:
		if (t1 < count1) {
			fread(&wa[i].key, sizeof(KeyType), 1, f4);
			t1++;
		}
		else wa[i].key = MAXKEY;
		break;
	case 2:
		if (t2 < count2) {
			fread(&wa[i].key, sizeof(KeyType), 1, f5);
			t2++;
		}
		else wa[i].key = MAXKEY;
		break;
	default:wa[i].key = MAXKEY;
	}
}

/*���ð�����ls����Ŵ�0��k-1��k������鲢���еļ�¼�鲢������鲢��
  wa[0]��wa[w-1]Ϊ�������ϵ�w��Ҷ�ӽ�㣬
  �ֱ���w������鲢���е�ǰ��¼�Ĺؼ���
*/
void K_Merge(LoserTree& ls, WorkArea& wa) {
	for (int i = 0; i < w; i++) {
		input(ls, wa, i);					//�ֱ��w������鲢�ζ��뵱ǰ�öε�һ����¼�Ĺؼ��ֵ�����
	}
	CreateLoserTree(ls,wa);					//��������ls��ѡ����С�ؼ���Ϊwa[ls[0]].key
	while (wa[ls[0]].key != MAXKEY) {
		fprintf(ff, "%d", wa[ls[0]].key);	//����С��¼�Ĺؼ���д������ļ�
		printf("%d ", wa[ls[0]].key);
		input(ls, wa, ls[0]);				//�ӱ��Ϊls[0]������鲢���ж�����һ����¼�Ĺؼ���
		Adjust(ls, wa, ls[0]);				//������������ѡ���µ���С�ؼ���
	}
	fclose(ff);
}
//����w����¼���ڴ湤����wa�����ð�����ls��ѡ���ؼ�����С�ļ�¼����sָʾ
void Construct_Loser(LoserTree& ls, WorkArea& wa, FILE* fi) {
	int i;
	for (i = 0; i < w; i++)
		wa[i].rnum = wa[i].key = ls[i] = 0;				//��������ʼ��
	for (i = w - 1; i >= 0; i--) {
		fread(&wa[i].rec, sizeof(RcdType), 1, fi);		//����һ����¼
		wa[i].key = wa[i].rec.key;						//��ȡ�ؼ���
		wa[i].rnum = 1;									//��κ�Ϊ"1"
		Select_MiniMax(ls, wa, i);						//��������
	}
}

//���һ����ʼ�鲢�Σ�fiΪ�����ļ�ָ�룬f0Ϊ����ļ�ָ��
void get_run(LoserTree& ls, WorkArea& wa, FILE* fi, FILE* fo, int rc, int* rmax) {
	int q;
	KeyType minimax;
	while (wa[ls[0]].rnum == rc) {						//ѡ�õ�MINIMAX��¼����ǰ��ʱ
		q = ls[0];										//qָʾMINIMAX��¼��wa�е�λ��
		minimax = wa[q].key;
		fwrite(&wa[q].rec, sizeof(RcdType), 1, fo);		//����ѡ�õ�MINIMAX��¼д������ļ�
		//�����ļ������������¼����"rmax+1"�Σ�
		fread(&wa[q].rec, sizeof(RcdType), 1, fi);//�������ļ�������һ��¼
		if (feof(fi)) {
			wa[q].rnum = *rmax + 1;
			wa[q].key = MAXKEY;
		}
		else {											//�����ļ��ǿ�ʱ
			wa[q].key = wa[q].rec.key;					//��ȡ�ؼ���
			if (wa[q].key < minimax) {					//�¶���ļ�¼����һ��
				*rmax = rc + 1;
				wa[q].rnum = *rmax;
			}
			else
				wa[q].rnum = rc;						//�¶���ļ�¼����ǰ��
		}
		Select_MiniMax(ls, wa, q);						//ѡ���µ�MINIMAX��¼
	}
}

/*
�ڰ�����ls���ڴ湤����wa�����û� - ѡ���������ʼ�鲢�Σ�
fiΪ�����ļ���ֻ���ļ���ָ�룬foΪ����ļ���ֻд�ļ���ָ�룬
�����ļ����Ѵ�
*/
void Replace_Selection(LoserTree& ls, WorkArea& wa, FILE* fi, FILE* fo) {
	int rc, rmax;
	RcdType j;
	j.key = RUNEND_SYMBOL;
	Construct_Loser(ls, wa, fi);			  //����������
	rc = rmax = 1;							  //rcָʾ��ǰ���ɵĳ�ʼ�鲢�εĶκţ�rmaxָʾwa�йؼ���������ʼ�鲢�ε����κ�
	while (rc <= rmax) {					  //"rc==rmax+1"��־�����ļ����û�-ѡ�����������
		get_run(ls, wa, fi, fo, rc, &rmax);	  //���һ����ʼ�鲢��
		fwrite(&j, sizeof(RcdType), 1, fo);	  //���ν�����־д������ļ�
		rc = wa[ls[0]].rnum;				  //������һ�εĶκ�
	}
}

void print(RcdType t) {
	printf("%d ", t.key);
}
int main() {
	int i, k, j = 0;
	RcdType a[N] = { 21208,26538,13892,4665,6721,5346,31101,26661,14584,22924 };
	//srand((unsigned int)time(NULL));
	//for (int i = 0; i < 10; i++) {
		//printf("%d,", rand());
	//}
	//printf("\n");
	RcdType b;
	FILE* fi, * fo;						//��������ļ�
	LoserTree ls;						// ������
	WorkArea wa;						// �ڴ湤����
	fo = fopen("ori", "wb");			//׼���� ori �ı��ļ�����д����
	fwrite(a, sizeof(RcdType), N, fo);  //������ a д����ļ�ori
	fclose(fo);							//�ر�ָ�� fo ��ʾ���ļ�
	fi = fopen("ori", "rb");			//׼���� ori �ı��ļ����ж�����
	printf("�ļ��еĴ������¼Ϊ:\n");
	for (i = 1; i <= N; i++) {			// ���ν��ļ�ori�����ݶ��벢��ֵ��b										
		fread(&b, sizeof(RcdType), 1, fi);
		print(b);
	}
	printf("\n");
	rewind(fi);							// ʹfi��ָ�����·��ش��ļ�ori����ʼλ�ã��Ա����¶����ڴ棬������������ļ���
	fo = fopen("out", "wb");			// ���û���ѡ���������ʼ�鲢��
	Replace_Selection(ls, wa, fi, fo);
	fclose(fo);
	fclose(fi);
	fi = fopen("out", "rb");
	printf("��ʼ�鲢�θ�Ϊ:\n");
	do {
		k = fread(&b, sizeof(RcdType), 1, fi); //�� fi ָ��ָ����ļ����������ļ�¼��ֵ�� b�����������ɹ����Ľ����ֵ�� k
		if (k == 1) {
			if (b.key == MAXKEY) {		//����ֵ�������ֵʱ��������ǰ��ʼ�鲢���Ѿ����
				m++;
				printf("\n\n");
				continue;
			}
			print(b);
		}
	} while (k == 1);
	fclose(fi);
	fi = fopen("out", "rb");
	//���û�-ѡ���������õ��ĳ�ʼ�鲢�δ�Ž������ݴ��ļ���
	while (1) {
		fread(&b, sizeof(RcdType), 1, fi);
		if (b.key == MAXKEY)break;
		a0[count0++] = b.key;
	}
	fwrite(a0, sizeof(RcdType), count0, f0);
	fclose(f0);
	while (1) {
		fread(&b, sizeof(RcdType), 1, fi);
		if (b.key == MAXKEY)break;
		a1[count1++] = b.key;
	}
	fwrite(a1, sizeof(RcdType), count1, f1);
	fclose(f1);
	while (1) {
		fread(&b, sizeof(RcdType), 1, fi);
		if (b.key == MAXKEY)break;
		a2[count2++] = b.key;
	}
	fwrite(a2, sizeof(RcdType), count2, f2);
	fclose(f2);
	printf("�����Ľ��Ϊ��\n");
	K_Merge(ls, wa);
	return 0;
}

