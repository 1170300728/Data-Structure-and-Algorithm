#include<stdio.h>
#include<iostream>
#include<math.h>

typedef struct celltype {
	int data;
	celltype *lchild;
	celltype *rchild;
};
typedef celltype * BST;
int k1, k2, temp;

void menu();
BST B_Insert(int key, BST &F);
int B_DeleteMin(BST&F);
void B_Delete(int key, BST&F);
void B_Search(int key, BST&F);
int H_Search(int key, int last, int F[]);
void Inorder(BST&root, int fl[1030]);
void Inorder_out(BST& root);
void B_Aver(BST&F);
void H_Aver(int fl[1030]);
void Random_S(int fl[1030], int fll[1030]);

int main() {
	int i, k, fl[1030], choice, fll[1030],f[10];
	BST F = NULL,Fl=NULL,Ft=NULL;

	k1 = 0;
	k2 = 0;

	for (i = 1; i < 2048; i+=2) {
		F = B_Insert(i, F);
	}
	temp = 0;
	Inorder(F, fl);
	Random_S(fl, fll);
	for (i = 0; i < 1024; i ++) {
		Fl = B_Insert(fll[i], Fl);
	}
	for (i = 1; i < 6; i++) {
		Ft = B_Insert(i, Ft);
		f[i - 1] = i;
	}

	while (true) {
		menu();
		scanf("%d", &choice);
		getchar();
		if (choice == 0) {
			break;
		}
		else
			switch (choice)
			{
			case 1:
				printf("�����ֵΪ��");
				scanf("%d", &k);
				B_Insert(k, Ft);
				Inorder_out(Ft);
				printf("\n");
				getchar();
				break;
			case 2:
				printf("ɾ����ֵΪ��");
				scanf("%d", &k);
				B_Delete(k, Ft);
				Inorder_out(Ft);
				printf("\n");
				getchar();
				break;
			case 3:
				printf("˳��");
				H_Aver(fl);
				break;
			case 4:
				printf("˳��");
				B_Aver(F);
				printf("����");
				B_Aver(Fl);
				break;
			default:
				break;
			}
		printf("\n");
	}
	return 0;
}

void menu() {
	printf("1������һ����\n");
	printf("2��ɾ��һ����\n");
	printf("3���۰����ƽ��ֵ\n");
	printf("4��BST����ƽ��ֵ\n");
	printf("0���˳�����\n");
}
BST B_Insert(int key, BST &F) {
	if (F == NULL) {
		F = (BST)malloc(sizeof(celltype));
		F->data = key;
		F->lchild = NULL;
		F->rchild = NULL;
	}
	else if (F->data > key) {
		B_Insert(key, F->lchild);
	}
	else if (F->data < key) {
		B_Insert(key, F->rchild);
	}
	return F;
}
int B_DeleteMin(BST&F) {
	int tmp;
	BST P;
	if (F->lchild == NULL) {
		P = F;
		tmp = F->data;
		F = F->rchild;
		free(P);
	}
	else {
		return (B_DeleteMin(F->lchild));
	}
}
void B_Delete(int key, BST&F) {
	BST P;
	if (F != NULL)
		if (key < F->data)
			B_Delete(key, F->lchild);
		else if (key > F->data)
			B_Delete(key, F->rchild);
		else if (F->lchild == NULL) {
			P = F;
			F = F->rchild;
			free(P);
		}
		else if (F->rchild == NULL) {
			P = F;
			F = F->lchild;
			free(P);
		}
		else
			F->data = B_DeleteMin(F->rchild);
	else
		printf("�ö��������Ϊ��");
}
void B_Search(int key, BST&F) {
	k1++;
	if (F == NULL || key == F->data);
	else if (key < F->data)
		B_Search(key, F->lchild);
	else if (key > F->data)
		B_Search(key, F->rchild);
	return;
}
int H_Search(int key, int last, int F[]) {
	int low, up, mid;
	low = 0;
	up = last;
	while (low<=up)
	{
		k2++;
		mid = (low + up) / 2;
		if (F[mid] == key) {
			return mid;
		}
		else if(F[mid]>key)
		{
			up = mid - 1;
		}
		else {
			low = mid + 1;
		}
	}
	return -1;
}
void Inorder(BST& root,int fl[1030]) {
	if (root == NULL) {
		return;
	}
	else {
		Inorder(root->lchild,fl);
		fl[temp] = root->data;
		temp++;
		//printf("%d", root->data);
		Inorder(root->rchild,fl);
		return;
	}
}
void Inorder_out(BST& root) {
	if (root == NULL) {
		return;
	}
	else {
		Inorder_out(root->lchild);
		printf("%d ", root->data);
		Inorder_out(root->rchild);
		return;
	}
}
void B_Aver(BST&F) {
	int i;
	float sum = 0;

	for (i = 0; i < 1024; i++) {
		k1 = 0;
		B_Search((2 * i + 1), F);
		sum += k1;
	}
	printf("���ҳɹ�ƽ��ֵΪ��%f\n", (sum / 1024));
	sum = 0;
	for (i = 0; i < 1024; i++) {
		k1 = 0;
		B_Search((2 * i), F);
		sum += k1;
	}
	printf("����ʧ��ƽ��ֵΪ��%f\n", (sum / 1024));
}
void H_Aver(int fl[1030]) {
	int i;
	float sum = 0;

	for (i = 0; i < 1024; i++) {
		k2 = 0;
		H_Search((2*i+1), 1023, fl);
		sum += k2;
	}
	printf("���ҳɹ�ƽ��ֵΪ��%f\n", (sum / 1024));
	sum = 0;
	for (i = 0; i < 1024; i++) {
		k2 = 0;
		H_Search((2 * i), 1023, fl);
		sum += k2;
	}
	printf("����ʧ��ƽ��ֵΪ��%f\n", (sum / 1024));
}
void Random_S(int fl[1030], int fll[1030]) {
	int i, j, k, temp;
	for (i = 0; i < 1024; i++)
		fll[i] = fl[i];
	for (i = 0; i < 1024; i++) {
		j = rand() % 1024;
		k = rand() % 1024;
		temp = fll[j];
		fll[j] = fll[k];
		fll[k] = temp;
	}
}