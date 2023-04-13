#include <stdio.h>;
void quicksort(int* arr, int low, int high);
int main(void) {
	int arr[10000],N;
	printf("������������е����ָ�����");
	scanf_s("%d", &N);		//����������е����ָ���
	printf("������������У�");
	for(int i=0;i<N;i++)
		scanf_s("%d", &arr[i]);		//����������У����������arr��
	quicksort(arr, 0, N-1);
	for (int j = 0; j < N; j++)
		printf("%d ", arr[j]);
	return 0;
}

void quicksort(int* arr, int low, int high) {
	if (low >= high)return;		//һ�˿��Ž����ı�־
	int pivot = arr[low], i = low, j = high;	//�趨��׼Ϊ��һ��Ԫ��
	while (i<j)
	{
		while (arr[j]>=pivot && i<j) j--;	//�����������ҵ��Ȼ�׼ֵС��Ԫ��
		arr[i] = arr[j];
		while (arr[i]<=pivot && i<j) i++;	//�����������ҵ��Ȼ�׼ֵ���Ԫ��
		arr[j] = arr[i];
	} 
	arr[i] = pivot;				//����׼ֵ����iԪ��
	quicksort(arr, low, i);		//�ݹ����������
	quicksort(arr, i+1, high);	//�ݹ����������
	return;
}
