#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define  MAX         10000		//最大字符个数
#define  MAXVALUE    20000		//权值最大值
typedef struct HuffNode {
	char data;					//结点的数据，在此为用户输入的字符
	int weight;					//结点的权值，在此为各个字符出现的次数
	int parent, lchild, rchild;	//定义双亲结点、左孩子和右孩子
}HuffNode, * HuffTree;			//动态分配数组存储霍夫曼树
typedef char** HuffCode;		//动态分配数组存储霍夫曼编码表

//统计每个字母出现的次数
int CalWeight(char* str, char* data, int* weight) {
	int i, j, index = 0;
	int arr[26] = { 0 };
	for (i = 0; str[i]; i++) {
		if (str[i] >= 'a' && str[i] <= 'z')
			arr[str[i] - 'a']++;
		else if (str[i] >= 'A' && str[i] <= 'Z')
			arr[str[i] - 'A']++;
	}
	for (j = 0; j < 26; j++) {
		if (arr[j]) {
			data[index] = (char)(j + 'a');		//存储所有叶子结点的数据
			weight[index++] = arr[j];			//存储所有叶子结点的权值
		}
	}
	return index;		//返回不同字母的个数
}

//选出两个没有双亲结点且权值最小的两个结点
void select(HuffTree HT, int k, int* p, int* q) {
	int i, j, index=1;
	int min = MAXVALUE, lmin = MAXVALUE;
	for (i = 1; i <= k; i++) {
		if (HT[i].weight < min && !HT[i].parent) {		//选出最小者
			min = HT[i].weight;
			*p = i;
		}
	}
	for (j = 1; j <= k; j++) {
		if (HT[j].weight < lmin && j!=*p && !HT[j].parent) {	//选出次小者
			lmin = HT[j].weight;
			*q = j;
		}
	}

}

/*建霍夫曼树并求出编码表
  n为叶子结点的个数
  d为存放叶子结点数据的数组
  w为存放叶子结点权值的数组
*/
void HuffmanCoding(HuffTree& HT, HuffCode& HC, char* d, int* w, int n) {
	if (n <= 1)return;
	int i, s1, s2,f;
	int m = 2 * n - 1;		//霍夫曼树的结点个数为叶子结点个数乘2减1
	char* cd;
	HT = (HuffTree)malloc((m + 1) * sizeof(HuffNode));	//为霍夫曼树分配存储空间
	//初始化叶子结点
	for (i = 1; i <= n; i++) {
		HT[i].data = d[i-1];
		HT[i].weight = w[i - 1];
		HT[i].parent = 0;
		HT[i].lchild = 0;
		HT[i].rchild = 0;
	}
	//初始化非叶子结点
	for (i; i <= m; i++) {
		HT[i].weight = 0;
		HT[i].parent = 0;
		HT[i].lchild = 0;
		HT[i].rchild = 0;
	}
	//建霍夫曼树
	for (i = n + 1; i <= m; i++) {
		select(HT, i - 1, &s1, &s2);		//选出两个权值最小且没有双亲结点的结点，序号为s1,s2
		HT[s1].parent = i;
		HT[s2].parent = i;
		HT[i].weight = HT[s1].weight + HT[s2].weight;
		HT[i].lchild = s1;
		HT[i].rchild = s2;
	}
	HC = (HuffCode)malloc((n + 1) * sizeof(char*));
	cd = (char*)malloc(n * sizeof(char));	//cd暂时存放单个字母的霍夫曼编码
	cd[n - 1] = '\0';
	for (i = 1; i <= n; i++) {
		int start = n - 1;
		for (int c = i, f = HT[i].parent; f != 0; c = f, f = HT[f].parent) {
			if (HT[f].lchild == c) cd[--start] = '0';		//从叶子结点向上寻找到一条到根结点的路径
			else cd[--start] = '1';
		}
		HC[i] = (char*)malloc((n - start) * sizeof(char));
		strcpy(HC[i], &cd[start]);		//将每个字母的霍夫曼编码复制到编码表中
	}
	for (i = 1; i <= n; i++)
		printf("%c:%s\n", HT[i].data, HC[i]);		//输出每个字母的编码
}

/*译码
  code为用户输入的编码
  letter存放译码的结果
*/
void HuffmanDecoding(HuffTree& HT, int n, char* code, char* letter) {
	int i=0, j=0;
	HuffNode p = HT[2 * n - 1];
	char* q = code;
	while (code[i]) {
		while (p.lchild || p.rchild) {	//从根结点出发按'0'或'1'寻找叶子结点
			if (code[i] == '0')
				p = HT[p.lchild];
			else if (code[i] == '1')
				p = HT[p.rchild];
			else {
				printf("输入错误！\n");	//未找到对应的叶子结点
				return;
			}
			i++;
		}
		letter[j++] = p.data;
		p = HT[2 * n - 1];
	}
	letter[j] = '\0';
	printf("%s\n", letter);
}
int main(void) {
	char a[MAX],b[MAX],letter[MAX];
	printf("请输入字符串：");
	gets_s(a);
	char data[MAX] = { 0 };
	int weight[MAX] = { 0 };
	int count = CalWeight(a, data, weight);
	if (count <= 1) {
		printf("输入有误！");
		return -1;
	}
	HuffTree HT;
	HuffCode HC;
	HuffmanCoding(HT, HC, data, weight, count);
	printf("所输入字符串的霍夫曼编码为：");
	for (int i = 0; a[i]; i++) {		//将用户输入的字符串编码后输出
		for (int j = 1; j <= count; j++) {
			if (a[i] == HT[j].data)
				printf("%s", HC[j]);
		}
	}
	printf("\n请输入霍夫曼编码：");
	gets_s(b);
	HuffmanDecoding(HT, count, b, letter);
	return 0;
}