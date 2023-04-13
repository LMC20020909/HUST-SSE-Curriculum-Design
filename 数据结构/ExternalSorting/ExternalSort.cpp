#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define w			  3		//内存工作区可容纳的记录个数
#define MAXKEY        (~(0x1 << 31)) //最大关键字标志
#define RUNEND_SYMBOL (~(0x1 << 31)) //归并段结束标志
#define N			  10	//输入文件的预设记录个数
#define MINKEY	      -(~(0x1 << 31))//最小关键字标志
typedef int KeyType;		//关键字类型
typedef struct {
	KeyType key;
}RcdType;					//记录类型
typedef int LoserTree[w];  //败者树是完全二叉树且不含叶子，可采用顺序存储结构
typedef struct {
	RcdType rec;		//记录
	KeyType key;		//从记录中抽取的关键字
	int rnum;			//所属归并段的段号
}RcdNode,WorkArea[w];	//内存工作区，容量为w
int t0 = 0, t1 = 0, t2 = 0, m = 0;//标志变量

/*输入、输出、中间暂存文件指针的定义
  f0、f1、f2为中间暂存文件，存放初始归并段
  ff为最终输出文件
*/
FILE* f0 = fopen("f0", "wb");
FILE* f1 = fopen("f1", "wb");
FILE* f2 = fopen("f2", "wb");
FILE* f3 = fopen("f0", "rb");
FILE* f4 = fopen("f1", "rb");
FILE* f5 = fopen("f2", "rb");
FILE* ff = fopen("ff", "wb");

//从wa[q]起到败者树的根比较选择MINIMAX记录，并由q指向它所在的归并段
void Select_MiniMax(LoserTree& ls, WorkArea wa, int q) {
	int p, s, t;
	for (t = (w + q) / 2, p = ls[t]; t > 0; t /= 2, p = ls[t]) {
		//段号小者或段号相同且关键字更小者为胜者
		if (wa[p].rnum < wa[q].rnum || wa[p].rnum == wa[q].rnum && wa[p].key < wa[q].key) {
			s = q;
			q = ls[t];	//q指向新的胜者
			ls[t] = s;
		}
	}
	ls[0] = q;  //冠军
}

//沿从叶子结点wa[q]到根结点ls[0]的路径调整败者树
void Adjust(LoserTree& ls, WorkArea wa, int q) {
	int t = (q + w) / 2;						//ls[t]是wa[q]的双亲结点
	while (t > 0) {
		if (wa[q].key > wa[ls[t]].key) {		
			int swap = q;
			q = ls[t];							//q指示新的胜者
			ls[t] = swap;
		}
		t = t / 2;
	}
	ls[0] = q;
}
int a0[N], a1[N], a2[N], count0 = 0, count1 = 0, count2 = 0;

/*已知wa[0]到wa[w-1]为完全二叉树ls的叶子结点存有w个关键字，
  沿从叶子到根的w条路径将ls调整为败者树
*/
void CreateLoserTree(LoserTree& ls, WorkArea& wa) {
	int i;
	for (i = 0; i < w; i++) {
		ls[i] = w;				//设置ls中败者的初值
	}
	for (i = w - 1; i >= 0; i--) {
		Adjust(ls, wa, i);		//依次从wa[w-1],wa[w-2],...,wa[0]出发调整败者
	}
}

/*从存放着初始归并段中的三个文件f0, f1, f2中读取下一个记录的关键字，
  如果读到一个归并段结束则读取最大关键字MAXKEY*/
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

/*利用败者树ls将编号从0到k-1的k个输入归并段中的记录归并到输出归并段
  wa[0]至wa[w-1]为败者树上的w个叶子结点，
  分别存放w个输入归并段中当前记录的关键字
*/
void K_Merge(LoserTree& ls, WorkArea& wa) {
	for (int i = 0; i < w; i++) {
		input(ls, wa, i);					//分别从w个输入归并段读入当前该段第一个记录的关键字到外结点
	}
	CreateLoserTree(ls,wa);					//建败者树ls，选得最小关键字为wa[ls[0]].key
	while (wa[ls[0]].key != MAXKEY) {
		fprintf(ff, "%d", wa[ls[0]].key);	//将最小记录的关键字写入输出文件
		printf("%d ", wa[ls[0]].key);
		input(ls, wa, ls[0]);				//从编号为ls[0]的输入归并段中读入下一个记录的关键字
		Adjust(ls, wa, ls[0]);				//调整败者树，选择新的最小关键字
	}
	fclose(ff);
}
//输入w个记录到内存工作区wa，建得败者树ls，选出关键字最小的记录并由s指示
void Construct_Loser(LoserTree& ls, WorkArea& wa, FILE* fi) {
	int i;
	for (i = 0; i < w; i++)
		wa[i].rnum = wa[i].key = ls[i] = 0;				//工作区初始化
	for (i = w - 1; i >= 0; i--) {
		fread(&wa[i].rec, sizeof(RcdType), 1, fi);		//输入一个记录
		wa[i].key = wa[i].rec.key;						//提取关键字
		wa[i].rnum = 1;									//其段号为"1"
		Select_MiniMax(ls, wa, i);						//调整败者
	}
}

//求得一个初始归并段，fi为输入文件指针，f0为输出文件指针
void get_run(LoserTree& ls, WorkArea& wa, FILE* fi, FILE* fo, int rc, int* rmax) {
	int q;
	KeyType minimax;
	while (wa[ls[0]].rnum == rc) {						//选得的MINIMAX记录属当前段时
		q = ls[0];										//q指示MINIMAX记录在wa中的位置
		minimax = wa[q].key;
		fwrite(&wa[q].rec, sizeof(RcdType), 1, fo);		//将刚选好的MINIMAX记录写入输出文件
		//输入文件结束，虚设记录（属"rmax+1"段）
		fread(&wa[q].rec, sizeof(RcdType), 1, fi);//从输入文件读入下一记录
		if (feof(fi)) {
			wa[q].rnum = *rmax + 1;
			wa[q].key = MAXKEY;
		}
		else {											//输入文件非空时
			wa[q].key = wa[q].rec.key;					//提取关键字
			if (wa[q].key < minimax) {					//新读入的记录属下一段
				*rmax = rc + 1;
				wa[q].rnum = *rmax;
			}
			else
				wa[q].rnum = rc;						//新读入的记录属当前段
		}
		Select_MiniMax(ls, wa, q);						//选择新的MINIMAX记录
	}
}

/*
在败者树ls和内存工作区wa上用置换 - 选择排序求初始归并段，
fi为输入文件（只读文件）指针，fo为输出文件（只写文件）指针，
两个文件均已打开
*/
void Replace_Selection(LoserTree& ls, WorkArea& wa, FILE* fi, FILE* fo) {
	int rc, rmax;
	RcdType j;
	j.key = RUNEND_SYMBOL;
	Construct_Loser(ls, wa, fi);			  //初建败者树
	rc = rmax = 1;							  //rc指示当前生成的初始归并段的段号，rmax指示wa中关键字所属初始归并段的最大段号
	while (rc <= rmax) {					  //"rc==rmax+1"标志输入文件的置换-选择排序已完成
		get_run(ls, wa, fi, fo, rc, &rmax);	  //求得一个初始归并段
		fwrite(&j, sizeof(RcdType), 1, fo);	  //将段结束标志写入输出文件
		rc = wa[ls[0]].rnum;				  //设置下一段的段号
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
	FILE* fi, * fo;						//输入输出文件
	LoserTree ls;						// 败者树
	WorkArea wa;						// 内存工作区
	fo = fopen("ori", "wb");			//准备对 ori 文本文件进行写操作
	fwrite(a, sizeof(RcdType), N, fo);  //将数组 a 写入大文件ori
	fclose(fo);							//关闭指针 fo 表示的文件
	fi = fopen("ori", "rb");			//准备对 ori 文本文件进行读操作
	printf("文件中的待排序记录为:\n");
	for (i = 1; i <= N; i++) {			// 依次将文件ori的数据读入并赋值给b										
		fread(&b, sizeof(RcdType), 1, fi);
		print(b);
	}
	printf("\n");
	rewind(fi);							// 使fi的指针重新返回大文件ori的起始位置，以便重新读入内存，产生有序的子文件。
	fo = fopen("out", "wb");			// 用置换－选择排序求初始归并段
	Replace_Selection(ls, wa, fi, fo);
	fclose(fo);
	fclose(fi);
	fi = fopen("out", "rb");
	printf("初始归并段各为:\n");
	do {
		k = fread(&b, sizeof(RcdType), 1, fi); //读 fi 指针指向的文件，并将读的记录赋值给 b，整个操作成功与否的结果赋值给 k
		if (k == 1) {
			if (b.key == MAXKEY) {		//当其值等于最大值时，表明当前初始归并段已经完成
				m++;
				printf("\n\n");
				continue;
			}
			print(b);
		}
	} while (k == 1);
	fclose(fi);
	fi = fopen("out", "rb");
	//将置换-选择排序所得到的初始归并段存放进三个暂存文件中
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
	printf("排序后的结果为：\n");
	K_Merge(ls, wa);
	return 0;
}

