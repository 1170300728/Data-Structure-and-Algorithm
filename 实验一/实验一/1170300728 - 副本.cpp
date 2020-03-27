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
		printf("链表为空\n");
	}
	else {
		for (i = 0; i <= L.last; i++) {
			if (L.numbers[i] == x) {
				flag = i+1;
			}
		}
		if (!flag) {
			printf("元素%d不存在\n", x);
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
		printf("链表为空\n");
	}
	else {
		for (i = 0; i <= L.last; i++) {
			if (L.numbers[i] == x) {
				position = i;
			}
		}
	}
	if (position == -1) {
		printf("元素%d不存在\n", x);
	}
	else
	{
		printf("%d在链表的第%d位\n", x, position + 1);
	}
}
void output(LIST L) {
	int i;
	if (L.ifnull == 1) {
		printf("链表为空\n");
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
		printf("链表已满\n");
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
		printf("1、查找一个指定元素；\n");
		printf("2、插入一个指定元素；\n");
		printf("3、删除一个指定元素；\n");
		printf("4、统计链表的长度；\n");
		printf("5、输出线性链表；\n");
		printf("6、实现按逆序重建链表。\n");
		printf("0、退出；\n输入指令：");
		scanf("%d", &x);
		switch (x)
		{
		case 1:
			printf("请输入指定的元素：");
			scanf("%d", &x);
			locate(x, L);
			break;
		case 2:
			printf("请输入指定的元素：");
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
			printf("请输入指定的元素：");
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
			printf("长度为：%d\n", L.last + 1);
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
			printf("请输入正确指令\n");
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