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
	int lowkey; //��ǰ��С�ؼ���
	int i, j, lowindex; //��ǰ��С�ؼ��ֵ��±�
	for (i = 0; i < n-1; i++) { //��A[i��n]��ѡ����С�Ĺؼ��֣���A[i]����
		lowindex = i;
		lowkey = A[i];
		for (j = i + 1; j < n; j++) {
			if (A[j] < lowkey) { //�õ�ǰ��С�ؼ�����ÿ���ؼ��ֱȽ�
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
		count++; /*��ʼ���ѣ������ҷ�Ҷ��㿪ʼ*/
		PushDown(i, n, A); /*����ѣ�����iΪ��������±��ҶΪn*/
	}
	for (i = n; i > 0; i--) {
		swap(A[0], A[i-1]); //�Ѷ��뵱ǰ���е��±�����Ҷ��㽻��
		PushDown(0, i-1, A);
		count++;
		/*����Ѱ���1Ϊ����
		���Ҷ�±�Ϊi-1����ȫ��Ԫ������ɶ�*/
	}
}
void PushDown(int first, int last, int A[10000])
{
	int temp = A[first]; // temp���浱ǰ���ڵ�
	int child = 2 * first + 1; // �Ȼ������

	while (child < last) {
		// ������Һ��ӽ�㣬�����Һ��ӽ���ֵ�������ӽ�㣬��ѡȡ�Һ��ӽ��
		if (child + 1 <last && A[child] < A[child + 1]) {
			child++;
		}
		count++;

		// ���������ֵ�Ѿ����ں��ӽ���ֵ����ֱ�ӽ���
		if (temp >= A[child])
			break;

		// �Ѻ��ӽ���ֵ���������
		swap(A[first], A[child]);

		// ѡȡ���ӽ������ӽ��,��������ɸѡ
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