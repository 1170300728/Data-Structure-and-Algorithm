#include <stdio.h>
#include<iostream>
#include<stack>
using namespace std;

void readformfile(FILE *fp, int C[5][5]);
void printscreen(int C[5][5]);
void findshortcut(int C[5][5],int origin, int destination);
int ifconclude(int l[5], int t);
int main() {
	FILE *fp;
	int origin, destination;
	int C[5][5];

	fp = fopen("ex3_Graph1.txt", "r");

	readformfile(fp, C);
	printscreen(C);

	origin = 0;
	for (destination = 1; destination < 5; destination++)
		findshortcut(C, origin, destination);

	getchar();
	return 0;
}

void readformfile(FILE *fp,int C[5][5]) {
	int i = 1,c;
	char cdata;

	if (fp) {
		while (1) {
			cdata = fgetc(fp);
			if (cdata == '\n') {
				break;
			}
		}
		while (1) {
			cdata = fgetc(fp);
			if (cdata == '\n') {
				break;
			}
		}
		while (1) {
			cdata = fgetc(fp);
			if (cdata == '\n') {
				break;
			}
		}
		for (i = 0; i < 5; i++) {
			fscanf(fp, "s%d %d %d %d %d %d", &c, &C[i][0], &C[i][1], &C[i][2], &C[i][3], &C[i][4]);
			fgetc(fp);
		}
		return;
	}
	else {
		printf("open file error!");
		return;
	}
}
void printscreen(int C[5][5]) {
	int i,j;
	for (i= 0; i < 5; i++) {
		printf("s%d", i);
		for (j = 0; j < 5; j++) {
			printf("%5d", C[i][j]);
		}
		printf("\n");
	}
}
void findshortcut(int C[5][5], int origin, int destination) {
	int i, j, temp,c=1000,k,l,sum=0,c0,temp1,i1,j1,c1=1000,c10,length,sum1=0;
	int shortcut[5],shortcut0[5];

	temp = origin;
	shortcut[0] = temp;
	j = 1;
	temp1 = origin;
	shortcut0[0] = temp1;
	j1 = 1;
	while (temp != destination)
	{
		c = 1000;
		if (C[temp][destination] != -1) {
			c0 = destination;
			shortcut[j] = c0;
			j++;
			break;
		}
		for (i = 0; i < 5; i++) {
			if (C[temp][i] != -1 && ifconclude(shortcut, i)) {
				if (C[temp][i] < c) {
					c = C[temp][i];
					c0 = i;
				}
			}
		}
		if (c != 1000) {
			temp = c0;
			shortcut[j] = c0;
			j++;
		}
		else {
			shortcut0[0] = -1;
			break;
		}
	}

	while (temp1 != destination)
	{
		c1 = 1000;
		for (i1 = 0; i1 < 5; i1++) {
			if (C[temp1][i1] != -1 && ifconclude(shortcut0, i1)) {
				if (C[temp1][i1] < c1) {
					c1 = C[temp1][i1];
					c10 = i1;
				}
			}
		}
		if (c1 != 1000) {
			temp1 = c10;
			shortcut0[j1] = c10;
			j1++;
		}
		else {
			shortcut0[0]=-1;
			break;
		}
	}

	if (shortcut[0] == -1) {
		length = j1;
		for (i = 0; i < length;i++) {
			shortcut[i] = shortcut0[i];
		}
	}
	else if (shortcut0[0] != -1) {
		for (i = 0; i < j - 1; i++) {
			sum += C[shortcut[i]][shortcut[i + 1]];
		}
		for (i = 0; i < j1 - 1; i++) {
			sum1 += C[shortcut0[i]][shortcut0[i + 1]];
		}
		if (sum1 < sum) {
			length = j1;
			for (i = 0; i < length; i++) {
				shortcut[i] = shortcut0[i];
			}
		}
		else {
			length = j;
		}
	}
	else {
		length = j;
	}
	
	
	/*for (i = 0; i < length; i++) {
		for (k = i + 1; k < length; k++) {
			if (k - i > 1)
				if (C[shortcut0[i]][shortcut0[k]] != -1) {

					for (j = i + 1, l = k; l < length; j++, l++) {
						shortcut0[j] = shortcut0[l];
					}
					length -= k + i;
				}
		}
	}*/
	for (i = 0; i < length-1; i++) {
		if (C[shortcut[i]][shortcut[i + 1]] == -1) {
			for (j = 0; j < 5; j++) {
				if (C[shortcut[i]][shortcut[j]] != -1 && C[shortcut[j]][shortcut[i + 1]] != -1) {
					for (k = length; k > j; k--) {
						shortcut[k] = shortcut[k-1];
					}
					shortcut[k] = j;
					length++;
				}
			}

		}
	}
	
	sum = 0;

	printf("s%d->s%d  path : ", origin, destination);
	for (i = 0; i < length-1; i++) {
		printf("s%d,", shortcut[i]);
		sum += C[shortcut[i]][shortcut[i + 1]];
	}
	printf("s%d", shortcut[i]);
	printf("   value:%d\n",sum);
	return;
}
int ifconclude(int l[5], int t) {
	int i;
	for (i = 0; i < 5; i++) {
		if (l[i] == t)
			return 0;
	}
	return 1;
}