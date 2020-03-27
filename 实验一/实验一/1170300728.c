#include <stdio.h>
#include <string.h>
#include<malloc.h>
#define maxlength 100

typedef struct LIST
{
	int number;
	struct LIST * next;
};
typedef struct LIST list;
typedef struct LIST * position;

void Delete(position p) {
	position p0 = p->next;
	p->next = p->next->next;
	free(p0);
}
position delete_s(int x,position home) {
	position p = home;
	int flag=1;
	if (p == NULL) {
		return home;
	}
	else if (p->number == x) {
		p = p->next;
		free(home);
		return p;
	}
	else {
		while (p->next != NULL)
		{
			if (p->next->number == x) {
				Delete(p);
				flag = 0;
				break;
			}
			p = p->next;
		}
		if (p->number == x) {
			p = p->next;
			free(p->next);
		}else if (flag) {
			printf("元素%d不存在\n", x);
		}
		return home;
	}
}
void locate(int x, position home) {
	int i = 1, flag = 1;
	position p = home;
	if (p == NULL) {
		printf("链表为空\n");
	}
	else
	{
		while (p->next != NULL)
		{
			if (p->number == x) {
				printf("%d在链表的第%d位\n", x, i);
				flag = 0;
				break;
			}
			p = p->next;
			i++;
		}
		if (flag) {
			printf("元素%d不存在\n", x);
		}
	}
}
void output(position home) {
	position p = home;
	if (p == NULL) {
		printf("链表为空\n");
	}
	else {
		while (p != NULL) {
			printf("%d ", p->number);
			p = p->next;
		}
		printf("\n");
	}
}
void insert(int x, position p) {
	position temp;
	temp = p->next;
	p->next = (position)malloc(sizeof(list));
	p->next->next = temp;
	p->next->number = x;
}
position reverse(position home) {
	position p = home, p0, p1;
	if (home == NULL) {
		return home;
	}
	else {
		p0 = (position)malloc(sizeof(list));
		p0->next = NULL;
		p0->number = p->number;
		p1 = p->next;
		while (p->next!=NULL)
		{
			insert(p0->number,p0);
			p0->number = p->next->number;
			p = p->next;
		}
		return p0;
	}
}
position insert_s(int num, position home) {
	position p0 = home;
	if (p0 == NULL) {
		p0 = (position)malloc(sizeof(list));
		p0->next = NULL;
		p0->number = num;
		return p0;
	}
	else {
		while (1)
		{
			if (p0->next != NULL) {
				if (p0->number > num) {
					insert(p0->number, p0);
					p0->number = num;
					break;
				}
			}
			else {
				if (p0->number > num) {
					insert(p0->number, p0);
					p0->number = num;
					break;
				}
				else
				{
					insert(num, p0);
					break;
				}
			}
			p0 = p0->next;
		}
	    return home;
	}
}
void length(position home) {
	int i=1;
	position p = home;
	if (p == NULL) {
		printf("链表为空\n");
	}
	else
	{
		while (p->next!=NULL)
		{
			p = p->next;
			i++;
		}
		printf("该链表的长度为%d\n", i);
	}
}

int main() {
	FILE *fp;
	char c;
	int num, flag = 0, n = 0, x, r = 0, sign = 0;
	position home;
	
	home = NULL;

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
			home= insert_s(n, home);
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
			home = insert_s(n, home);
			n = 0;
			sign = 0;
		}
	}

	fclose(fp);
	flag = 1;
	while (1)
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
			locate(x, home);
			break;
		case 2:
			printf("请输入指定的元素：");
			scanf("%d", &x);
			if (r) {
				home = reverse(home);
			}
			home=insert_s(x, home);
			if (r) {
				home = reverse(home);
			}
			output(home);
			break;
		case 3:
			printf("请输入指定的元素：");
			scanf("%d", &x);
			if (r) {
				home = reverse(home);
			}
			home = delete_s(x, home);
			if (r) {
				home = reverse(home);
			}
			output(home);
			break;
		case 4:
			length(home);
			break;
		case 5:
			output(home);
			break;
		case 6:
			home = reverse(home);
			output(home);
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