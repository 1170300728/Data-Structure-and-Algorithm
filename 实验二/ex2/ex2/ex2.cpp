#include<iostream>
#include<stack>
#include<queue>
using namespace std;

struct node
{
	node* lchild;
	char data;
	node* rchild;
};
typedef node* tree;
struct treeLIST {
	tree treep;
	char data;
	tree father;
};
typedef treeLIST* treelist;

tree readformfile(FILE* fp, treelist tlist[]);
tree Addtree(char child, tree father, char side);
tree findtree(treelist tlist[], char data);
void Preorder(tree root);
void Inorder(tree root);
void Postorder(tree root);
void NPreorder(tree root);
void NInorder(tree root);
void NPostorder(tree root);
void Forder(tree root);
tree FindFather(treelist tlist[], char data);
tree FindAncestor(char data1, char data2, treelist tlist[]);

int main() {
	FILE *fp;
	tree root,ancestor;
	treelist tlist[20];
	char data1, data2;
	int choice;

	fp = fopen("ex2_tree.txt", "r");

	root = readformfile(fp, tlist);
	while (true)
	{
		printf("1、二叉树的递归先序\n2、递归中序\n3、递归后序\n4、非递归先序\n5、非递归中序\n6、非递归后序\n7、层序遍历\n8、求二叉树中任意两个结点的公共祖先\n0、退出\n请输入操作数：");
		scanf("%d", &choice);
		switch (choice)
		{
		case 1:
			Preorder(root);
			printf("\n");
			break;

		case 2:
			Inorder(root);
			printf("\n");
			break;

		case 3:
			Postorder(root);
			printf("\n");
			break;

		case 4:
			NPreorder(root);
			printf("\n");
			break;

		case 5:
			NInorder(root);
			printf("\n");
			break;

		case 6:
			NPostorder(root);
			printf("\n");
			break;

		case 7:
			Forder(root);
			printf("\n");
			break;

		case 8:
			printf("请输入查询的两个结点：");
			getchar();
			scanf("%c,%c", &data1, &data2);
			ancestor = FindAncestor(data1, data2, tlist);
			printf("共同祖先为：%c\n", ancestor->data);
			break;

		case 0:
			break;

		default:
			printf("请输入正确的操作数！\n");
			break;
		}
		if (choice == 0) {
			break;
		}
		printf("\n");
	}
	return 0;
}

tree readformfile(FILE* fp,treelist tlist[]) {
	tree fathertree,root;
	int i = 1;
	char cdata, cfather, cside, rootdata;

	if (fp) {
		rootdata = fgetc(fp);
		root = new node;
		root->data = rootdata;
		root->lchild = NULL;
		root->rchild = NULL;
		tlist[0] = new treeLIST;
		tlist[0]->data = rootdata;
		tlist[0]->treep = root;
		tlist[0]->father = NULL;
		while (1) {
			cdata = fgetc(fp);
			if (cdata == '\n') {
				break;
			}
		}
		while (3 == fscanf(fp, "%c %c %c", &cdata, &cfather, &cside)) {
			fathertree = findtree(tlist, cfather);
			fathertree = Addtree(cdata, fathertree, cside);
			tlist[i] = new treeLIST;
			if (cside == 'R') {
				tlist[i]->treep = fathertree->rchild;
			}
			else {
				tlist[i]->treep = fathertree->lchild;

			}
			tlist[i]->data = cdata;
			tlist[i]->father = fathertree;
			i++;
			fgetc(fp);
		}
		return root;
	}
	else {
		printf("open file error!");
		return NULL;
	}
}
tree Addtree(char child, tree father, char side) {
	tree childtree;
	childtree = new node;
	childtree->data = child;
	childtree->lchild = NULL;
	childtree->rchild = NULL;
	if (side == 'L') {
		father->lchild = childtree;
	}
	else if (side == 'R') {
		father->rchild = childtree;
	}
	return father;
}
tree findtree(treelist tlist[],char data) {
	int i;
	for (i = 0; i < 20; i++) {
		if (tlist[i]->data == data) {
			return tlist[i]->treep;
		}
	}
	return NULL;
}
void Preorder(tree root) {
	if (root == NULL) {
		return;
	}
	else {
		printf("%c", root->data);
		Preorder(root->lchild);
		Preorder(root->rchild);
		return;
	}
}
void Inorder(tree root) {
	if (root == NULL) {
		return;
	}
	else {
		Inorder(root->lchild);
		printf("%c", root->data);
		Inorder(root->rchild);
		return;
	}
}
void Postorder(tree root) {
	if (root == NULL) {
		return;
	}
	else {
		Postorder(root->lchild);
		Postorder(root->rchild);
		printf("%c", root->data);
		return;
	}
}
void NPreorder(tree root) {
	stack <tree>S;
	tree now = root;

	while (now != NULL||!empty(S)) {
		if (now!=NULL)
		{
			printf("%c", now->data);
			S.push(now);
			now = now->lchild;
		}
		else {
			now = S.top();
			S.pop();
			now = now->rchild;
		}
	}
}
void NInorder(tree root) {
	stack <tree>S;
	tree now = root;

	while (now != NULL || !empty(S)) {
		if (now != NULL)
		{
			S.push(now);
			now = now->lchild;
		}
		else {
			now = S.top();
			printf("%c", now->data);
			S.pop();
			now = now->rchild;
		}
	}
}
void NPostorder(tree root) {
	stack<tree> s;
	tree now;
	tree pre = NULL;
	s.push(root);
	while (!s.empty())
	{
		now = s.top();
		if ((now->lchild == NULL && now->rchild == NULL) ||
			(pre != NULL && (pre == now->lchild || pre == now->rchild)))
		{
			printf("%c",now->data);
			s.pop();
			pre = now;
		}
		else
		{
			if (now->rchild != NULL)
				s.push(now->rchild);
			if (now->lchild != NULL)
				s.push(now->lchild);
		}
	}
}
void Forder(tree root) {
	queue <tree>Q;
	tree now = root;

	Q.push(now);
	while(!Q.empty()){
		now = Q.front();
		printf("%c", now->data);
		if (now->lchild != NULL) {
			Q.push(now->lchild);
		}
		if (now->rchild != NULL) {
			Q.push(now->rchild);
		}
		Q.pop();
	}
}
tree FindFather(treelist tlist[], char data) {
	int i;
	for (i = 0; i < 20; i++) {
		if (tlist[i]->data == data) {
			return tlist[i]->father;
		}
	}
	return NULL;
}
tree FindAncestor(char data1, char data2,treelist tlist[]) {
	tree tree1, tree2, temp;
	char datat1[5], datat2[5];
	int flag = 0, i1 = 1, i2 = 1;

	tree1 = findtree(tlist, data1);
	tree2 = findtree(tlist, data2);
	datat1[0] = data1;
	datat2[0] = data2;
	while (tree1->data != tree2->data) {
		if (flag) {
			temp = tree1;
			tree1 = FindFather(tlist, tree1->data);
			if (tree1 == NULL) {
				tree1 = temp;
			}
			else {
				datat1[i1] = tree1->data;
				i1++;
			}
			flag = 0;
		}
		else{
			temp = tree2;
			tree2 = FindFather(tlist, tree2->data);
			if (tree1 == NULL) {
				tree2 = temp;
			}
			else {
				datat2[i2] = tree2->data;
				i2++;
			}
			flag = 1;
		}
	}
	if (tree1->data == 'a') {
		for(;i1>=0,i2>=0;i1--,i2--){
			if (datat1[i1] != datat2[i2]) {
				return findtree(tlist,datat1[i1+1]);
			}
		}
	}
	return tree1;
}