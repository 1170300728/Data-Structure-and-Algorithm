#include <stdio.h>
#include <math.h>
#include <time.h>
#include<iostream>

int count;

void swap(int &x, int &y);
void SelectSort(int n, int A[10000]);
void HeapSort(int n, int A[10000]);
void PushDown(int first, int last, int A[10000]);
void Random_S(int n, int fl[10000], int fll[10000]);

int main() {
	int i, j, A[100][10000], k,Al[100][10000];

	for (i = 0; i < 100; i++) {
		k = (i + 1) * 100;
		printf("%d\n", k);
		for (j = 0; j < k; j++) {
			A[i][j] = j;
		}
		Random_S(k, A[i], Al[i]);
	}
	for (i = 0; i < 100; i++) {
		count = 0;
		HeapSort((i + 1) * 100, A[i]);
		printf("%d\n", count);
	}
	for (i = 0; i < 100; i++) {
		count = 0;
		HeapSort((i + 1) * 100, Al[i]);
		printf("%d\n", count);
	}
	for (i = 0; i < 100; i++) {
		k = (i + 1) * 100;
		for (j = 0; j < k; j++) {
			A[i][j] = j;
		}
	}
	for (i = 0; i < 100; i++) {
		count = 0;
		SelectSort((i + 1) * 100, A[i]);
		printf("%d\n", count);
	}
	getchar();
	return 0;
}
void swap(int &x,int &y)
{
	int w;
	w = x; 
	x = y; 
	y = w;
}
void SelectSort(int n, int A[10000])
{
	int lowkey; //当前最小关键字
	int i, j, lowindex; //当前最小关键字的下标
	for (i = 0; i < n-1; i++) { //在A[i…n]中选择最小的关键字，与A[i]交换
		lowindex = i;
		lowkey = A[i];
		for (j = i + 1; j < n; j++) {
			if (A[j] < lowkey) { //用当前最小关键字与每个关键字比较
				lowkey = A[j];
				lowindex = j;
			}
			count++;
		}
		swap(A[i], A[lowindex]);
	}
}
void HeapSort(int n, int A[10000])
{
	int i;
	for (i = n / 2; i >= 0; i--) {
		count++; /*初始建堆，从最右非叶结点开始*/
		PushDown(i, n, A); /*整理堆，把以i为根，最大下标的叶为n*/
	}
	for (i = n; i > 0; i--) {
		swap(A[0], A[i-1]); //堆顶与当前堆中的下标最大的叶结点交换
		PushDown(0, i-1, A);
		count++;
		/*整理堆把以1为根，
		最大叶下标为i-1的完全二元树整理成堆*/
	}
}
void PushDown(int first, int last, int A[10000])
{
	int temp = A[first]; // temp保存当前父节点
	int child = 2 * first + 1; // 先获得左孩子

	while (child < last) {
		// 如果有右孩子结点，并且右孩子结点的值大于左孩子结点，则选取右孩子结点
		if (child + 1 <last && A[child] < A[child + 1]) {
			child++;
		}
		count++;

		// 如果父结点的值已经大于孩子结点的值，则直接结束
		if (temp >= A[child])
			break;

		// 把孩子结点的值赋给父结点
		swap(A[first], A[child]);

		// 选取孩子结点的左孩子结点,继续向下筛选
		first = child;
		child = 2 * child + 1;
	}

}
void Random_S(int n,int fl[10000], int fll[10000]) {
	int i, j, k, temp;
	for (i = 0; i < n; i++)
		fll[i] = fl[i];
	for (i = 0; i < n; i++) {
		j = rand() % n;
		k = rand() % n;
		temp = fll[j];
		fll[j] = fll[k];
		fll[k] = temp;
	}
}