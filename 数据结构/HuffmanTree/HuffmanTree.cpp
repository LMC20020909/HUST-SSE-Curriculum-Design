#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define  MAX         10000		//����ַ�����
#define  MAXVALUE    20000		//Ȩֵ���ֵ
typedef struct HuffNode {
	char data;					//�������ݣ��ڴ�Ϊ�û�������ַ�
	int weight;					//����Ȩֵ���ڴ�Ϊ�����ַ����ֵĴ���
	int parent, lchild, rchild;	//����˫�׽�㡢���Ӻ��Һ���
}HuffNode, * HuffTree;			//��̬��������洢��������
typedef char** HuffCode;		//��̬��������洢�����������

//ͳ��ÿ����ĸ���ֵĴ���
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
			data[index] = (char)(j + 'a');		//�洢����Ҷ�ӽ�������
			weight[index++] = arr[j];			//�洢����Ҷ�ӽ���Ȩֵ
		}
	}
	return index;		//���ز�ͬ��ĸ�ĸ���
}

//ѡ������û��˫�׽����Ȩֵ��С���������
void select(HuffTree HT, int k, int* p, int* q) {
	int i, j, index=1;
	int min = MAXVALUE, lmin = MAXVALUE;
	for (i = 1; i <= k; i++) {
		if (HT[i].weight < min && !HT[i].parent) {		//ѡ����С��
			min = HT[i].weight;
			*p = i;
		}
	}
	for (j = 1; j <= k; j++) {
		if (HT[j].weight < lmin && j!=*p && !HT[j].parent) {	//ѡ����С��
			lmin = HT[j].weight;
			*q = j;
		}
	}

}

/*��������������������
  nΪҶ�ӽ��ĸ���
  dΪ���Ҷ�ӽ�����ݵ�����
  wΪ���Ҷ�ӽ��Ȩֵ������
*/
void HuffmanCoding(HuffTree& HT, HuffCode& HC, char* d, int* w, int n) {
	if (n <= 1)return;
	int i, s1, s2,f;
	int m = 2 * n - 1;		//���������Ľ�����ΪҶ�ӽ�������2��1
	char* cd;
	HT = (HuffTree)malloc((m + 1) * sizeof(HuffNode));	//Ϊ������������洢�ռ�
	//��ʼ��Ҷ�ӽ��
	for (i = 1; i <= n; i++) {
		HT[i].data = d[i-1];
		HT[i].weight = w[i - 1];
		HT[i].parent = 0;
		HT[i].lchild = 0;
		HT[i].rchild = 0;
	}
	//��ʼ����Ҷ�ӽ��
	for (i; i <= m; i++) {
		HT[i].weight = 0;
		HT[i].parent = 0;
		HT[i].lchild = 0;
		HT[i].rchild = 0;
	}
	//����������
	for (i = n + 1; i <= m; i++) {
		select(HT, i - 1, &s1, &s2);		//ѡ������Ȩֵ��С��û��˫�׽��Ľ�㣬���Ϊs1,s2
		HT[s1].parent = i;
		HT[s2].parent = i;
		HT[i].weight = HT[s1].weight + HT[s2].weight;
		HT[i].lchild = s1;
		HT[i].rchild = s2;
	}
	HC = (HuffCode)malloc((n + 1) * sizeof(char*));
	cd = (char*)malloc(n * sizeof(char));	//cd��ʱ��ŵ�����ĸ�Ļ���������
	cd[n - 1] = '\0';
	for (i = 1; i <= n; i++) {
		int start = n - 1;
		for (int c = i, f = HT[i].parent; f != 0; c = f, f = HT[f].parent) {
			if (HT[f].lchild == c) cd[--start] = '0';		//��Ҷ�ӽ������Ѱ�ҵ�һ����������·��
			else cd[--start] = '1';
		}
		HC[i] = (char*)malloc((n - start) * sizeof(char));
		strcpy(HC[i], &cd[start]);		//��ÿ����ĸ�Ļ��������븴�Ƶ��������
	}
	for (i = 1; i <= n; i++)
		printf("%c:%s\n", HT[i].data, HC[i]);		//���ÿ����ĸ�ı���
}

/*����
  codeΪ�û�����ı���
  letter�������Ľ��
*/
void HuffmanDecoding(HuffTree& HT, int n, char* code, char* letter) {
	int i=0, j=0;
	HuffNode p = HT[2 * n - 1];
	char* q = code;
	while (code[i]) {
		while (p.lchild || p.rchild) {	//�Ӹ���������'0'��'1'Ѱ��Ҷ�ӽ��
			if (code[i] == '0')
				p = HT[p.lchild];
			else if (code[i] == '1')
				p = HT[p.rchild];
			else {
				printf("�������\n");	//δ�ҵ���Ӧ��Ҷ�ӽ��
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
	printf("�������ַ�����");
	gets_s(a);
	char data[MAX] = { 0 };
	int weight[MAX] = { 0 };
	int count = CalWeight(a, data, weight);
	if (count <= 1) {
		printf("��������");
		return -1;
	}
	HuffTree HT;
	HuffCode HC;
	HuffmanCoding(HT, HC, data, weight, count);
	printf("�������ַ����Ļ���������Ϊ��");
	for (int i = 0; a[i]; i++) {		//���û�������ַ�����������
		for (int j = 1; j <= count; j++) {
			if (a[i] == HT[j].data)
				printf("%s", HC[j]);
		}
	}
	printf("\n��������������룺");
	gets_s(b);
	HuffmanDecoding(HT, count, b, letter);
	return 0;
}