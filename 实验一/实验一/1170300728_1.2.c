#include <stdio.h>
#include <iostream>
#include <string.h>
#define maxlength 100

typedef struct LIST
{
	int numbers[2];
	position next;
};
typedef struct LIST list;
typedef struct LIST * position;

void output(position home) {
	int i;
	position p = home;
	if (p == NULL) {
		printf("未获得多项式");
	}
	else {
		while (p != NULL) {
			printf("[%d %d]", p->numbers[0], p->numbers[1]);
			p = p->next;
		}
	}
	printf("\n");
}
void insert(int x, int y, position p) {
	position temp;
	temp = p->next;
	p->next = (position)malloc(sizeof(list));
	p->next->next = temp;
	p->next->numbers[0] = x;
	p->next->numbers[1] = y;
}
position insert_s(int x, int y, position home) {
	position p0 = home;

	if (p0 == NULL) {
		p0 = (position)malloc(sizeof(list));
		p0->next = NULL;
		p0->numbers[0] = x;
		p0->numbers[1] = y;
		return p0;
	}
	else {
		while (1)
		{
			if (p0->next != NULL) {
				if (p0->numbers[1] > y) {
					insert(p0->numbers[0], p0->numbers[1], p0);
					p0->numbers[0] = x;
					p0->numbers[1] = y;
					return home;
				}
			}
			else {
				if (p0->numbers[1] > y) {
					insert(p0->numbers[0], p0->numbers[1], p0);
					p0->numbers[0] = x;
					p0->numbers[1] = y;
					return home;
				}
				else
				{
					insert(x, y, p0);
					return home;
				}
			}
			p0 = p0->next;
		}
	}
}
position list_add(position L1_home, position L2_home) {
	int i = 1, j = 1, k = 0;
	position p1 = L1_home, p2 = L2_home, p, home;

	p = NULL;
	home = p;
	while (p1 != NULL && p2 != NULL) {
		if (p1->numbers[1] == p2->numbers[1]) {
			p = (position)malloc(sizeof(list));
			p->numbers[0] = p1->numbers[0] + p2->numbers[0];
			p->numbers[1] = p1->numbers[1];
			p->next = NULL;
			p1 = p1->next;
			p2 = p2->next;
			p = p->next;
		}
		else if (p1->numbers[1] > p2->numbers[1]) {
			p = (position)malloc(sizeof(list));
			p->numbers[0] = p2->numbers[0];
			p->numbers[1] = p2->numbers[1];
			p->next = NULL;
			p2 = p2->next;
			p = p->next;
		}
		else {
			p = (position)malloc(sizeof(list));
			p->numbers[0] = p1->numbers[0];
			p->numbers[1] = p1->numbers[1];
			p->next = NULL;
			p1 = p1->next;
			p = p->next;
		}
	}
	if (p1->next == NULL) {
		while (p2 != NULL) {
			p = (position)malloc(sizeof(list));
			p->numbers[0] = p2->numbers[0];
			p->numbers[1] = p2->numbers[1];
			p->next = NULL;
			p2 = p2->next;
			p = p->next;
		}
	}
	else {
		while (p1 != NULL) {
			p = (position)malloc(sizeof(list));
			p->numbers[0] = p1->numbers[0];
			p->numbers[1] = p1->numbers[1];
			p->next = NULL;
			p1 = p1->next;
			p = p->next;
		}
	}
	return home;
}

int main() {
	int number1, number2, i, line;
	char c;
	position L1_home = NULL, L2_home = NULL, L_home;

	printf("输入行数：");
	scanf("%d", &line);
	printf("输入多项式：");
	for (i = 0; i < line; i++) {
		L1_home = NULL;
		L2_home = NULL;

		while (1) {
			scanf("%d %d", &number1, &number2);
			L1_home = insert_s(number1, number2, L1_home);

			c = getchar();
			if (c == '\n') {
				break;
			}
		}

		while (1) {
			scanf("%d %d", &number1, &number2);
			L2_home = insert_s(number1, number2, L2_home);

			c = getchar();
			if (c == '\n') {
				break;
			}
		}
		L_home = list_add(L1_home, L2_home);
		output(L_home);
	}
	getchar();
	return 0;
}