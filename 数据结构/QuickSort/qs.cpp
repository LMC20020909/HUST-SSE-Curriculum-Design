#include <stdio.h>;
void quicksort(int* arr, int low, int high);
int main(void) {
	int arr[10000],N;
	printf("请输入待排序列的数字个数：");
	scanf_s("%d", &N);		//输入待排序列的数字个数
	printf("请输入待排序列：");
	for(int i=0;i<N;i++)
		scanf_s("%d", &arr[i]);		//输入待排序列，存放在数组arr中
	quicksort(arr, 0, N-1);
	for (int j = 0; j < N; j++)
		printf("%d ", arr[j]);
	return 0;
}

void quicksort(int* arr, int low, int high) {
	if (low >= high)return;		//一趟快排结束的标志
	int pivot = arr[low], i = low, j = high;	//设定基准为第一个元素
	while (i<j)
	{
		while (arr[j]>=pivot && i<j) j--;	//在右子序列找到比基准值小的元素
		arr[i] = arr[j];
		while (arr[i]<=pivot && i<j) i++;	//在左子序列找到比基准值大的元素
		arr[j] = arr[i];
	} 
	arr[i] = pivot;				//将基准值赋给i元素
	quicksort(arr, low, i);		//递归快排左序列
	quicksort(arr, i+1, high);	//递归快排右序列
	return;
}
