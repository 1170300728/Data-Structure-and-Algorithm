#include <stdio.h>
#include <iostream>
#include <string.h>
#define maxlength 100

struct LIST
{
	int numbers[maxlength][2];
	int last;
};

void output(LIST L) {
	int i;
	for (i = 0; i <= L.last; i++) {
		printf("[%d %d]", L.numbers[i][0],L.numbers[i][1]);
	}
	printf("\n");
}
void insert(int x, int y,LIST &L) {
	int i, j, flag = 0;
	if (L.last >= maxlength - 1) {
		printf("list is full");
	}
	else if (L.last == 0 && L.numbers[0][0] == -1) {
		L.numbers[0][0] = x;
		L.numbers[0][1] = y;
		flag = 1;
	}
	else
	{
		for (i = 0; i <= L.last; i++) {
			if (L.numbers[i][1] > y) {
				for (j = L.last + 1; j > i; j--) {
					L.numbers[j][0] = L.numbers[j - 1][0];
					L.numbers[j][1] = L.numbers[j - 1][1];
				}
				L.numbers[i][0] = x;
				L.numbers[i][1] = y;
				L.last++;
				flag = 1;
				break;
			}
		}
	}
	if (!flag) {
		L.numbers[L.last + 1][0] = x;
		L.numbers[L.last + 1][1] = y;
		L.last++;
	}
}
LIST list_add(LIST L1, LIST L2) {
	int i = 0, j = 0, k = 0;
	LIST L;

	L.last = 0;
	L.numbers[0][0] = -1;
	while (i <= L1.last && j <= L2.last) {
		if (L1.numbers[i][1] == L2.numbers[j][1]) {
			L.numbers[k][0] = L1.numbers[i][0] + L2.numbers[j][0];
			L.numbers[k][1] = L1.numbers[i][1];
			k++;
			i++;
			j++;
		}
		else if (L1.numbers[i][1] > L2.numbers[j][1]) {
			L.numbers[k][0] = L2.numbers[j][0];
			L.numbers[k][1] = L2.numbers[j][1];
			k++;
			j++;
		}
		else {
			L.numbers[k][0] = L1.numbers[i][0];
			L.numbers[k][1] = L1.numbers[i][1];
			k++;
			i++;
		}
	}
	if (i == L1.last + 1) {
		for (i = j; i <= L2.last; i++) {
			L.numbers[k][0] = L2.numbers[i][0];
			L.numbers[k][1] = L2.numbers[i][1];
			k++;
		}
	}
	else {
		for (j = i; j <= L1.last; j++) {
			L.numbers[k][0] = L1.numbers[j][0];
			L.numbers[k][1] = L1.numbers[j][1];
			k++;
		}
	}
	L.last = k-1;
	return L;
}
int main() {
	int number1, number2, i, line, num, flag, j, r = 0, x, i0, sign1 = 0;
	char c;
	char str[maxlength];
	LIST L1, L2, L;
	int A[maxlength][2];
	int B[maxlength][2];

	printf("输入行数：");
	scanf("%d", &line);
	printf("输入多项式：");
	getchar();
	for (i = 0; i < line; i++) {
		L1.last = 0;
		L1.numbers[0][0] = -1;
		L2.last = 0;
		L2.numbers[0][0] = -1;

		fgets(str, maxlength, stdin);
		j = 0;
		number1 = 0;
		number2 = 0;
		flag = 0;

		while (1) {
			c = str[j];
			j++;
			num = (int)c;
			if (num >= 48 && num <= 57) {
				num -= 48;
				if (flag == 2) {
					if (sign1 == 1) {
						number1 *= -1;
						sign1 = 0;
					}
					insert(number1, number2, L1);
					number1 = num;
					number2 = 0;
					flag = 0;
				}
				else if (flag == 1) {
					number2 = number2 * 10 + num;
				}
				else {
					number1 = number1 * 10 + num;
				}
			}
			else if (c == '\n') {
				if (sign1 == 1) {
					number1 *= -1;
					sign1 = 0;
				}
				insert(number1, number2, L1);
				break;
			}
			else if (c == '-')
			{
				sign1 = 1;
			}
			else {
				flag++;
			}
		}

		fgets(str, maxlength, stdin);
		j = 0;
		number1 = 0;
		number2 = 0;
		flag = 0;

		while (1) {
			c = str[j];
			j++;
			num = (int)c;
			if (num >= 48 && num <= 57) {
				num -= 48;
				if (flag == 2) {
					if (sign1 == 1) {
						number1 *= -1;
						sign1 = 0;
					}
					insert(number1, number2, L2);
					number1 = num;
					number2 = 0;
					flag = 0;
				}
				else if (flag == 1) {
					number2 = number2 * 10 + num;
				}
				else {
					number1 = number1 * 10 + num;
				}
			}
			else if (c == '\n') {
				if (sign1 == 1) {
					number1 *= -1;
					sign1 = 0;
				}
				insert(number1, number2, L2);
				break;
			}
			else if (c == '-') {
				sign1 = 1;
			}
			else
			{
				flag++;
			}
		}
		L = list_add(L1, L2);
		output(L1);
		output(L2);
		output(L);
	}
	getchar();
	return 0;
}