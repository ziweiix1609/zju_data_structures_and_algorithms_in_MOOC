#include <stdio.h>
#include <stdlib.h>

#define PRE_THREAD 0
#define IN_THREAD 1
#define POST_THREAD 2

typedef struct TBTNode *PtrToTBTNode;
typedef PtrToTBTNode TBTree;
struct TBTNode {
	int data;
	int ltag, rtag;
	TBTree lchild, rchild;
};

TBTree CreatBT(int pre[], int in[], int L1, int R1, int L2, int R2);
void inThread(TBTree p, TBTree *pre);
void preThread(TBTree p, TBTree *pre);
void postThread(TBTree p, TBTree *pre);
void creatThreadBTree(TBTree r, int flag);
void preOrder(TBTree root);
void inOrder(TBTree root);
TBTree First(TBTree p);
TBTree Next(TBTree p);
void visit(TBTree p);

int main()
{
	TBTree root;
	int pre[7] = {3, 2, 1, 6, 5, 4, 7};
	int in[7] = {1, 2, 3, 4, 5, 6, 7};

	root = CreatBT(pre, in, 0, 6, 0, 6);
	creatThreadBTree(root, IN_THREAD);
	inOrder(root);
	return 0;
}

TBTree CreatBT(int pre[], int in[], int L1, int R1, int L2, int R2)
{
	int k;

	if (L1 > R1)
		return NULL;
	else {
		TBTree t = (TBTree) malloc(sizeof(struct TBTNode));
		t->ltag = t->rtag = 0;
		t->lchild = t->rchild = NULL;
		t->data = pre[L1];
		for (k = L2; k <= R2; ++k)
			if (pre[L1] == in[k])
				break;
		t->lchild = CreatBT(pre, in, L1+1, L1+k-L2, L2, k-1);
		t->rchild = CreatBT(pre, in, L1+k-L2+1, R1, k+1, R2);
		return t;
	}
}

void postThread(TBTree p, TBTree *pre)
{
	if (p == NULL)
		return;
	postThread(p->lchild, pre);
	postThread(p->rchild, pre);
	if (p->lchild == NULL) {
		p->lchild = (*pre);
		p->ltag = 1;
	}
	if (*pre != NULL && (*pre)->rchild == NULL) {
		(*pre)->rchild = p;
		(*pre)->rtag = 1;
	}
	(*pre) = p;
}

void creatThreadBTree(TBTree r, int flag)
{
	TBTree p = NULL;
	TBTree *pre = &p;

	if (!r) return;

	switch (flag) {
	case PRE_THREAD:
		preThread(r, pre);
		break;
	case IN_THREAD:
		inThread(r, pre);
		break;
	case POST_THREAD:
		postThread(r, pre);
		break;
	}
	(*pre)->rchild = NULL;
	(*pre)->rtag = 1;
}

void visit(TBTree p)
{
	printf("%d ", p->data);
}

