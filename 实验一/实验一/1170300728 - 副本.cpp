#include <stdio.h>
#include <string.h>
#define maxlength 100

struct LIST
{
	int numbers[maxlength];
	int last;
	int ifnull;
};

void Delete(int x, LIST &L) {
	int i,flag,j;
	if (L.ifnull == 1) {
		printf("����Ϊ��\n");
	}
	else {
		for (i = 0; i <= L.last; i++) {
			if (L.numbers[i] == x) {
				flag = i+1;
			}
		}
		if (!flag) {
			printf("Ԫ��%d������\n", x);
		}
		else
		{
			for (j = flag-1; j < L.last; j++) {
				L.numbers[j] = L.numbers[j + 1];
			}
				L.last--;
			if (L.last == 0) {
				L.ifnull = 1;
			}
		}
	}
}
void locate(int x, LIST L) {
	int i, position = -1;
	if (L.ifnull == 1) {
		printf("����Ϊ��\n");
	}
	else {
		for (i = 0; i <= L.last; i++) {
			if (L.numbers[i] == x) {
				position = i;
			}
		}
	}
	if (position == -1) {
		printf("Ԫ��%d������\n", x);
	}
	else
	{
		printf("%d������ĵ�%dλ\n", x, position + 1);
	}
}
void output(LIST L) {
	int i;
	if (L.ifnull == 1) {
		printf("����Ϊ��\n");
	}
	else {
		for (i = 0; i <= L.last; i++) {
			printf("%d ", L.numbers[i]);
		}
		printf("\n");
	}
}
void insert(int x, LIST &L){
	int i, j, flag=0;
	if (L.last >= maxlength - 1) {
		printf("��������\n");
	}
	else if (L.ifnull==1) {
		L.numbers[0] = x;
		flag = 1;
		L.ifnull = 0;
	}
	else
	{
		for (i = 0; i <= L.last; i++) {
			if (L.numbers[i] > x) {
				for (j = L.last + 1; j > i; j--) {
					L.numbers[j] = L.numbers[j - 1];
				}
				L.numbers[i] = x;
				L.last++;
				flag = 1;
				break;
			}
		}
	}
	if (!flag) {
		L.numbers[L.last+1] = x;
		L.last++;
	}
}
void reverse(LIST &L) {
	int i, temp;
	for (i = 0; i <= L.last / 2; i++) {
		temp = L.numbers[i];
		L.numbers[i] = L.numbers[L.last - i];
		L.numbers[L.last - i] = temp;
	}
}

int main() {
	LIST L;
	FILE *fp;
	char c;
	int num, flag = 0, i, n = 0, x, r = 0, sign = 0;

	L.last = 0;
	L.ifnull = 1;
	fp = fopen("test.txt", "r");
	while (1) {
		c = fgetc(fp);
		num = (int)c;
		if (num >= 48 && num <= 57) {
			num -= 48;
			n = n * 10 + num;
		}
		else if (c == EOF) {
			if (sign == 1) {
				n = -n;
			}
			insert(n, L);
			sign = 0;
			n = 0;
			break;
		}
		else if (c == '-') {
			sign = 1;
		}
		else
		{
			if (sign == 1) {
				n = -n;
			}
			insert(n, L);
			n = 0;
			sign = 0;
		}
	}

	fclose(fp);
	flag = 1;
	while (true)
	{
		printf("1������һ��ָ��Ԫ�أ�\n");
		printf("2������һ��ָ��Ԫ�أ�\n");
		printf("3��ɾ��һ��ָ��Ԫ�أ�\n");
		printf("4��ͳ������ĳ��ȣ�\n");
		printf("5�������������\n");
		printf("6��ʵ�ְ������ؽ�����\n");
		printf("0���˳���\n����ָ�");
		scanf("%d", &x);
		switch (x)
		{
		case 1:
			printf("������ָ����Ԫ�أ�");
			scanf("%d", &x);
			locate(x, L);
			break;
		case 2:
			printf("������ָ����Ԫ�أ�");
			scanf("%d", &x);
			if (r) {
				reverse(L);
			}
			insert(x, L);
			if (r) {
				reverse(L);
			}
			output(L);
			break;
		case 3:
			printf("������ָ����Ԫ�أ�");
			scanf("%d", &x);
			if (r) {
				reverse(L);
			}
			Delete(x, L);
			if (r) {
				reverse(L);
			}
			output(L);
			break;
		case 4:
			printf("����Ϊ��%d\n", L.last + 1);
			break;
		case 5:
			output(L);
			break;
		case 6:
			reverse(L);
			output(L);
			r = 1 - r;
			break;
		case 0:
			flag = 0;
			break;
		default:
			printf("��������ȷָ��\n");
			break;
		}
		printf("\n");
		if (flag == 0) {
			break;
		}
	}
	getchar();
	return 0;
}